#!/usr/bin/env python

from os.path import abspath, join, pardir, isdir, isfile, dirname, basename
from os import listdir
import ast

HEADER_TEXT = '''\
{0} This file has been autogenerated by configure.py please modify 'config'
{0} files and run configure.py instead of modifying this file.'''

CONFIG_FILENAME = 'config'

class Container(dict):

    def __init__(self, system, contenttype, path, counter):
        self.system,self.path,self.contenttype = system,path,contenttype
        self.counter = system.counters[counter].__iter__()
        self.codes = dict()

    def add(self, a):
        a.code = next(self.counter)
        self.update({a.name:a})
        self.codes.update({a.code:a.name})

    def get(self, k, d=None):
        if isinstance(k, str): return super().get(k, d)
        return super().get(self.codes.get(k, None), d)

    def __getitem__(self, k):
        if isinstance(k, str): return super().__getitem__(k)
        return super()[self.codes[k]]

    def save(self):
        return {'codes': self.codes, 'content': {k:v.save() for k,v in super().items()}}

    def loadFolder(self, relativepath='.'):
        absp = lambda x: join(self.path, relativepath, x)
        cond = lambda x: isdir(absp(x)) and isfile(join(absp(x), CONFIG_FILENAME))
        for p in filter(cond, listdir(absp('.'))):
            self.add(self.contenttype(self.system, absp(p), code=None))

    def loadConfigFile(self, relativepath='.'):
        self.parseConfig(Config(join(self.path, relativepath, CONFIG_FILENAME)))

    def fetch(self, elementtype):
        return set().union(*[v.fetch(elementtype) for v in self.values()])

    def parseConfig(self, cfg):
        ''' should be overwritten '''
        pass

    def write_define(self, f):
        for i in self.values():
            i.write_define(f)


class LibraryContainer(Container):

    def __init__(self, system, path):
        super().__init__(system, Library, path, 'library')
        self.loadFolder()


class RoomContainer(Container):

    def __init__(self, system, path):
        super().__init__(system, Room, path, 'room')
        self.loadFolder()


class DeviceContainer(Container):

    def __init__(self, system, path):
        super().__init__(system, Device, path, 'device')
        self.loadFolder()


class LogmsgContainer(Container):

    def __init__(self, system, path, module):
        super().__init__(system, Logmsg, path, 'logmsg')
        self.module = module
        self.loadConfigFile()

    def parseConfig(self, cfg):
        logmsg = cfg.get('logmsg', dict())
        for level in ['error', 'warn', 'info', 'debug']:
            for n,x in logmsg.get(level, dict()).items():
                name = f'{level}_{n}'
                description = x if isinstance(x, str) else x[0]
                description_params = [] if isinstance(x, str) else x[1]
                self.add(Logmsg(self.system, name, None, level, self.module,
                    description, description_params))


class CommandContainer(Container):

    def __init__(self, system, path):
        super().__init__(system, Command, path, 'command')
        self.loadConfigFile()

    def parseConfig(self, cfg):
        commands = cfg.get('commands', dict())
        for n in commands:
            self.add(Command(self.system, name=n, code=None))


class ComponentContainer(Container):

    def __init__(self, system, path):
        super().__init__(system, Component, path, 'component')
        self.loadConfigFile()

    def parseConfig(self, cfg):
        components = cfg.get('components', dict())
        for n,v in components.items():
            self.add(Component(self.system, name=n, code=None, value=v))


class Element:

    def __init__(self, system, name, code=None):
        self.system,self.name,self.code = system,name,code

    def save(self):
        ''' should be overwritten '''
        pass

    def write_define(self, f):
        ''' should be overwritten '''
        pass

    def fetch(self, elementtype):
        ''' should be overwritten '''
        pass

    def write_define(self, f):
        f.write('#define {:40s} 0x{:x}\n'.format(self.name.upper(), self.code))

# An element is a folder containing a config file
class FolderElement(Element):

    def __init__(self, system, path, code=None):
        self.path = path
        self.cfg = Config(join(path, CONFIG_FILENAME))
        super().__init__(system=system, name=basename(path), code=code)


class System(FolderElement):

    ROOMS_DIR  = 'rooms'
    LIBS_DIR   = 'libs'

    def __init__(self, path):
        super().__init__(self, path)
        self.protocol = self.cfg.get('protocol')
        self.ptypes = self.protocol['ptypes']
        self.psizes = self.getpsizes()
        self.delimiters = self.getdelimiters()
        self.counters = self.createcounters()

        self.commands = CommandContainer(self, self.path)
        self.libraries = LibraryContainer(self, join(self.path, 'libs'))
        self.counters['logmsg'].push()
        self.rooms = RoomContainer(self, join(self.path, 'rooms'))

    def getdelimiters(self):
        c = self.protocol['packet_delimiters']
        if isinstance(c, str): c = c.encode('ascii')
        return [*c]

    def getpsizes(self):
        sizes = {'uint8':1, 'uint16':2, 'uint32':4, 'uint64':8}
        return {k:sizes[self.ptypes[k]] for k in ['command', 'device', 'logmsg', 'component']}

    def createcounters(self):
        counters = dict()
        counters['library']   = countExcluding(exclude=self.delimiters)
        counters['room']      = countExcluding(exclude=self.delimiters)
        counters['command']   = countExcluding(exclude=self.delimiters,
                end=1<<8*self.psizes['command'])
        counters['device']    = countExcluding(exclude=self.delimiters,
                end=1<<8*self.psizes['device'])
        counters['logmsg']    = countExcluding(exclude=self.delimiters,
                end=1<<8*self.psizes['logmsg'])
        counters['component'] = countExcluding(exclude=self.delimiters,
                end=1<<8*self.psizes['component'])
        return counters

    def save(self):
        libraries = {l.name: l.save() for l in self.libraries.values()}
        rooms = {r.name: r.save() for r in self.rooms.values()}
        return {'commands': self.commands.save(), 'libraries': self.libraries.save(),
                'rooms': self.rooms.save(), 'protocol': self.protocol}

    def fetch(self, elementtype):
        if elementtype == 'system': return {self}
        containers = [self.commands, self.libraries, self.rooms]
        return set().union(*[v.fetch(elementtype) for v in containers])



class Library(FolderElement):

    def __init__(self, system, path, code):
        super().__init__(system, path)
        self.logmsg = LogmsgContainer(self.system, self.path, self.name)
        system.counters['logmsg'].push()

    def save(self):
        return {'logmsg': self.logmsg.save()}

    def fetch(self, elementtype):
        if elementtype == 'library': return {self}
        return self.logmsg.fetch(elementtype)


class Room(FolderElement):

    def __init__(self, system, path, code):
        super().__init__(system, path)
        self.description = self.cfg.get('description', None)
        self.devices = DeviceContainer(self.system, join(self.path, 'devices'))

    def save(self):
        return {'description': self.description, 'devices': self.devices.save()}

    def fetch(self, elementtype):
        if elementtype == 'room': return {self}
        return self.devices.fetch(elementtype)


class Device(FolderElement):

    #TODO extend to have room cmd
    def __init__(self, system, path, code):
        super().__init__(system, path)
        self.components = ComponentContainer(self.system, self.path) 
        self.logmsg = LogmsgContainer(self.system, self.path, self.name)
        self.code = code
    
    def save(self):
        return {'components': self.components.save(), 'logmsg': self.logmsg.save()}

    def write_define(self, f, name=None):
        if name == None: name = 'DEV_'+self.name
        s = '#define {:40s} 0x{:0' + str(2*self.system.psizes['device']) + 'x}\n'
        f.write(s.format(name.upper(), self.code))

    def fetch(self, elementtype):
        if elementtype == 'device': return {self}
        return set().union(*[v.fetch(elementtype) for v in [self.components, self.logmsg]])


class Logmsg(Element):

    def __init__(self, system, name, code, level, module, description, description_params):
        super().__init__(system, name, code)
        self.level = level 
        self.description = description
        self.description_params = description_params
        self.module = module

    def save(self):
        return {'code': self.code, 'name': self.name, 'module': self.module,
                'description': self.description, 'description_params': self.description_params}

    def write_define(self, f, name=None):
        if name == None: name = self.name
        s =  '#define {:40s} 0x{:0' + str(2*self.system.psizes['logmsg']) + 'x}\n'
        f.write(s.format(name.upper(), self.code))

    def fetch(self, elementtype):
        if elementtype == 'logmsg': return {self}
        return set()


class Command(Element):

    def __init__(self, system, name, code):
        super().__init__(system, name, code)

    def save(self):
        return {'name': self.name, 'code': self.code}

    def write_define(self, f, name=None):
        if name == None: name = 'CMD_'+self.name
        s =  '#define {:40s} 0x{:0' + str(2*self.system.psizes['command']) + 'x}\n'
        f.write(s.format(name.upper(), self.code))

    def fetch(self, elementtype):
        if elementtype == 'command': return {self}
        return set()


class Component(Element):

    def __init__(self, system, name, code, value):
        super().__init__(system, name, code)
        self.value = value

    def save(self):
        return {'name': self.name, 'code': self.code, 'value': self.value}

    def write_define(self, f, name=None):
        if name == None: name = 'COMP_'+self.name
        s =  '#define {:40s} 0x{:0' + str(2*self.system.psizes['component']) + 'x}\n'
        f.write(s.format(name.upper(), self.code))

    def fetch(self, elementtype):
        if elementtype == 'component': return {self}
        return set()


def writeHeader(f, mode, end='\n\n'):
    f.write(HEADER_TEXT.format({'C': '//', 'python': '#'}[mode]))
    if end: f.write(end)

def writeFooter(f, mode, end='\n'):
    f.write({'C': '#endif', 'python': ''}[mode] + '\n')
    if end: f.write(end)

def writePragmaOnce(f, filename, end='\n'):
    m = filename.replace('.', '_').upper() + '_'
    f.write(f'#ifndef {m}\n')
    f.write(f'#define {m}\n')
    if end: f.write(end)

def write_define(f, name, value, end='\n'):
    f.write('#define {:56s} {}'.format(name.upper(), value))
    if end: f.write(end)

def write_defineInt(f, name, value, ndigits=None, base=16, end='\n'):
    prefix = {2:'0b', 10:'', 16:'0x'}[base]
    base = {2:'b', 10:'d', 16:'x'}[base]
    n = '' if ndigits == None else f'0{ndigits}'
    value = (prefix + '{:' + n + base + '}').format(value)
    write_define(f, name=name, value=value, end=end)

def write_defineChar(f, name, c):
    if isinstance(c, bytes): c = repr(c.decode('ascii'))
    elif isinstance(c, str): c = repr(c)
    elif isinstance(c, int): c = repr(bytes([c]).decode('ascii'))
    write_define(f, name, c)

def write_typedef(f, name, t, end='\n'):
    if 'int' in t: t += '_t'
    f.write(f'typedef {t} {name.capitalize()}_t;')
    if end: f.write(end)

def write_comment(f, s):
    comment = pformat(f'// {s}')
    if '\n' in comment:
        comment = pformat(f'/* {s} */')
    f.write(comment)

class Config(dict):

    def __init__(self, path):
        with open(path) as f:
            d = ast.literal_eval('{'+f.read()+'}') #TODO use safer config (but json hasn't hex nb) 
            super().__init__(d)


class countExcluding:

    def __init__(self, start=0x01, exclude={}, end=None):
        self.start = start
        self.next = start
        self.imax = start
        self.exclude = exclude
        self.end = end

    def __iter__(self):
        self.next = self.start
        return self

    def __next__(self):
        while self.next in self.exclude:
            self.next += 1
        i = self.next
        if self.end != None and i > self.end:
            raise ValueError(f'Iterator passed end limit: {i}/{self.end}')
        self.imax = max(self.imax, i)
        self.next += 1
        return i
    
    def push(self):
        self.start,self.imax = self.imax+1,self.imax
        
