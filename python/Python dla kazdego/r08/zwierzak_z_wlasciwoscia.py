# Zwierzak z właściwością
# Demonstruje właściwości

class Critter(object):
    """Wirtualny pupil"""
    def __init__(self, name):
        print("Urodził się nowy zwierzak!")
        self.__name = name

    @property
    def name(self):
        return self.__name
    
    @name.setter
    def name(self, new_name):
        if new_name == "":
            print("Pusty łańcuch znaków nie może być imieniem zwierzaka.")
        else:
            self.__name = new_name
            print("Zmiana imienia się powiodła.")

    def talk(self):
        print("\nCześć! Jestem", self.name)

# część główna
crit = Critter("Reksio")
crit.talk()

print("\nImię mojego zwierzaka to:", end= " ")
print(crit.name)

print("\nPróbuję zmienić imię mojego zwierzaka na Pucek...")
crit.name = "Pucek"
print("Imię mojego zwierzaka to:", end= " ")
print(crit.name)

print("\nPróbuję zmienić imię mojego zwierzaka na pusty łańcuch znaków...")
crit.name = ""
print("Imię mojego zwierzaka to:", end= " ")
print(crit.name)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
