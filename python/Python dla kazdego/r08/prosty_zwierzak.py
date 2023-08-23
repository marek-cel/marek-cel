# Prosty zwierzak
# Demonstruje podstawową klasę i obiekt

class Critter(object):
    """Wirtualny pupil"""
    def talk(self):
        print("Cześć!  Jestem egzemplarzem klasy Critter.")

# część główna
crit = Critter()
crit.talk()

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
