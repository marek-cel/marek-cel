import sys

from PySide2.QtWidgets import QApplication
from .mainwindow import MainWindow


def main():
    app = QApplication([])
    win = MainWindow()
    win.show()
    sys.exit(app.exec_())
