# Prywatny zwierzak
# Demonstruje zmienne i metody prywatne

class Critter(object):
    """Wirtualny pupil"""
    def __init__(self, name, mood):
        print("Urodził się nowy zwierzak!")
        self.name = name            # atrybut publiczny
        self.__mood = mood          # atrybut prywatny

    def talk(self):
        print("\nJestem", self.name)
        print("W tej chwili czuję się", self.__mood, "\n")

    def __private_method(self):
        print("To jest metoda prywatna.")

    def public_method(self):
        print("To jest metoda publiczna.")
        self.__private_method()

# część główna
crit = Critter(name = "Reksio", mood = "szczęśliwy")
crit.talk()
crit.public_method()

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
