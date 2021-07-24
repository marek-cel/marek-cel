#!/usr/bin/env python3

################################################################################

class Klasa(object):
    """opis klasy"""

    count = 0   # skladnik statyczny

    @staticmethod
    def print_cout():
        print("Count", Klasa.count)

    def __init__(self, name):
        self.name = name
        self.__secret = 777
        print("I am a constructor")
        Klasa.count += 1

    def __str__(self):
        return "name : " + self.name

    def talk(self):
        """opis metody"""
        print("Hi. My name is", self.name)

    def publiczna(self):
        print("Jestem metoda publiczna")
        self.__prywatna()

    def __prywatna(self):
        print("Jestem metoda prywatna")

    @property
    def secret(self):
        return self.__secret

    @secret.setter
    def secret(self, value):
        if value >= 0:
            self.__secret = value

################################################################################


Klasa.print_cout()

klasa1 = Klasa("KLASA_1")
klasa2 = Klasa("KLASA_2")

klasa1.talk()
klasa2.talk()

print(klasa1)
print(klasa2)

print(Klasa.count)

Klasa.print_cout()

#print(klasa1.__secret) # error
print("klasa1._Klasa__secret", klasa1._Klasa__secret)

# klasa1.__prywatna() # error
klasa1._Klasa__prywatna()

klasa1.publiczna()

print(klasa1.secret)
klasa1.secret = -111
print(klasa1.secret)
klasa1.secret = 222
print(klasa1.secret)

################################################################################
