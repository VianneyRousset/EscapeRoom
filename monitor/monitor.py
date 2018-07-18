#!/usr/bin/python3
# -*- coding: utf-8 -*-

"""
ZetCode PyQt5 tutorial 

This program centers a window 
on the screen. 

Author: Jan Bodnar
Website: zetcode.com 
Last edited: August 2017
"""

import sys
from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import QQmlApplicationEngine
from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot

class Serial:
    def __init__(self):
        #super().__init__

        result = pyqtSignal(int, arguments=['sum'])

    @pyqtSlot(int,int)
    def sum(self, arg1, arg2):
        print(f'sum {arg1}+{arg2}')
        self.result.emit(arg1+arg2)


if __name__ == '__main__':
    # Create an instance of the application
    app = QGuiApplication(sys.argv)
    # Create QML engine
    engine = QQmlApplicationEngine()
    # Create a calculator object
    serial = Serial()
    # And register it in the context of QML
    engine.rootContext().setContextProperty("serial", serial);
    # Load the qml file into the engine
    engine.load("main.qml")
 
    engine.quit.connect(app.quit)
    sys.exit(app.exec_())
