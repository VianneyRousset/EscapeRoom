#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import QQmlApplicationEngine
from PyQt5.QtCore import QObject, pyqtSignal, pyqtSlot

class Serial:
    def __init__(self):
        #super().__init__

    led1 = pyqtSignal(bool, arguments=['led1'])

    @pyqtSlot(bool)
    def sum(self, state)
        print(f'led1->{state}')
        # Send to server
        self.led1.emit(state)


if __name__ == '__main__':
    # Create an instance of the application
    app = QGuiApplication(sys.argv)
    # Create QML engine
    engine = QQmlApplicationEngine()
    # Create a calculator object
    serial = Serial()
    # And register it in the context of QML
    engine.rootContext().setContextProperty('serial', serial);
    # Load the qml file into the engine
    engine.load('new.qml')
 
    engine.quit.connect(app.quit)
    sys.exit(app.exec_())
