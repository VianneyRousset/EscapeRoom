from PyQt5.QtWidgets import QApplication
from PyQt5.QtQuick import QQuickView
from PyQt5.QtCore import QUrl

app = QApplication([])
view = QQuickView()
url = QUrl("main.qml")

view.setSource(url)
view.show()
app.exec_()
