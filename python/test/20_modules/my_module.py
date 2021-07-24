#!/usr/bin/env python3

################################################################################

def func():
    print("func()")

################################################################################


class InModuleClass(object):
    """Dokumentacja klasy"""

    def __init__(self, name):
        self.__name = name

    def __str__(self):
        return "name: " + self.__name

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        self.__name = name

################################################################################


if __name__ == "__main__":
    print("This is module file use it by import.")

################################################################################
