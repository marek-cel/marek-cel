#!/usr/bin/env python3

################################################################################

class Base(object):
    """klasa bazowa"""

    def __init__(self, name):
        self.__name = name

    def __str__(self):
        return self.__name

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        self.__name = name

################################################################################


class Derivative(Base):
    """klasa pochodna"""

    def __init__(self, name):
        super(Derivative, self).__init__(name)
        self.__hidden = True

    def __str__(self):
        if not self.__hidden:
            return super(Derivative, self).__str__()
        else:
            return "<hidden>"

    def reveal(self):
        self.__hidden = False

################################################################################

deriv1 = Derivative("NAME_1")

print(deriv1)

deriv1.reveal()

print(deriv1)

################################################################################
