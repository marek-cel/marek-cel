#!/usr/bin/env python3

################################################################################

class MyClass(object):
    """opis klasy"""

    count = 0   # skladnik statyczny

    @staticmethod
    def print_cout():
        print("Count", MyClass.count)

    def __init__(self, name):
        self.name = name    # skladnik publiczny
        self.__secret = 777 # skladnik prywatny
        print("I am a constructor")
        MyClass.count += 1

    def __str__(self):
        return "name : " + self.name

    def talk(self):
        """opis metody"""
        print("My name is", self.name)

    def publicfun(self):
        print("I am public method")
        self.__privatefun()

    def __privatefun(self):
        print("I am private method")

    @property
    def secret(self):
        return self.__secret

    @secret.setter
    def secret(self, value):
        if value >= 0:
            self.__secret = value

################################################################################


MyClass.print_cout()

mc1 = MyClass("MyClass 1")
mc2 = MyClass("MyClass 2")

mc1.talk()
mc2.talk()

print(mc1)
print(mc2)

print(MyClass.count)

MyClass.print_cout()

#print(mc1.__secret) # error
print("mc1._MyClass__secret", mc1._MyClass__secret)

# mc1.__privatefun() # error
mc1._MyClass__privatefun()

mc1.publicfun()

print(mc1.secret)
mc1.secret = -111
print(mc1.secret)
mc1.secret = 222
print(mc1.secret)

################################################################################
