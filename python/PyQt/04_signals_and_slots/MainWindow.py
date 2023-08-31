from PyQt5.QtWidgets import *

from Ui_MainWindow import Ui_MainWindow

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, *args, obj=None, **kwargs):
        super(MainWindow, self).__init__(*args, **kwargs)
        self.setupUi(self)
        self.setWindowTitle("My First Qt App")
        # self -> object -> signal -> connect -> slot
        self.pushButton_2.clicked.connect(self.changeLabelTextButton2Clicked)
    

    def on_pushButton_1_clicked(self):
        self.label.setText("Button 1 clicked")
    

    def changeLabelTextButton2Clicked(self):
        self.label.setText("Button 2 clicked")