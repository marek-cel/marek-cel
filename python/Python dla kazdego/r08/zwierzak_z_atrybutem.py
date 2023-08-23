# Zwierzak z atrybutem
# Demonstruje tworzenie atrybutów obiektu i uzyskiwanie do nich dostępu

class Critter(object):
    """Wirtualny pupil"""
    def __init__(self, name):
        print("Urodził się nowy zwierzak!")
        self.name = name

    def __str__(self):
        rep = "Obiekt klasy Critter\n"
        rep += "name: " + self.name + "\n"
        return rep  

    def talk(self):
        print("Cześć! Jestem", self.name, "\n")

# część główna
crit1 = Critter("Reksio")
crit1.talk()

crit2 = Critter("Pucek")
crit2.talk()

print("Wyświetlenie obiektu crit1:")
print(crit1)

print("Bezpośrednie wyświetlenie wartości atrybutu crit1.name:")
print(crit1.name)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
