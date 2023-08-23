# Zwierzak z klasą
# Demonstruje atrybuty klasy i metody statyczne

class Critter(object):
    """Wirtualny pupil"""
    total = 0

    @staticmethod   
    def status():
        print("\nOgólna liczba zwierzaków wynosi", Critter.total)
        
    def __init__(self, name):
        print("Urodził się zwierzak!")
        self.name = name
        Critter.total += 1

#część główna
print("Uzyskanie dostępu do atrybutu klasy Critter.total:", end=" ")
print(Critter.total)

print("\nTworzenie zwierzaków.")
crit1 = Critter("zwierzak 1")
crit2 = Critter("zwierzak 2")
crit3 = Critter("zwierzak 3")

Critter.status()

print("\nUzyskanie dostępu do atrybutu klasy poprzez obiekt:", end= " ")
print(crit1.total)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
