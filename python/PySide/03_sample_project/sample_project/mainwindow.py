from PySide2.QtWidgets import QMainWindow
from PySide2.QtCore import Slot
from .ui_mainwindow import Ui_MainWindow


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

    @Slot()
    def on_actionExit_triggered(self):
        self.close()

    @Slot()
    def on_pushButton_clicked(self):
        self.ui.label.setText("Push button clicked")
