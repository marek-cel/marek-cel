# Opiekun zwierzaka
# Wirtualny pupil, którym należy się opiekować

class Critter(object):
    """Wirtualny pupil"""
    def __init__(self, name, hunger = 0, boredom = 0):
        self.name = name
        self.hunger = hunger
        self.boredom = boredom

    def __pass_time(self):
        self.hunger += 1
        self.boredom += 1

    @property
    def mood(self):
        unhappiness = self.hunger + self.boredom
        if unhappiness < 5:
            m = "szczęśliwy"
        elif 5 <= unhappiness <= 10:
            m = "zadowolony"
        elif 11 <= unhappiness <= 15:
            m = "podenerwowany"
        else:
            m = "wściekły"
        return m
    
    def talk(self):
        print("Nazywam się", self.name, "i jestem", self.mood, "teraz.\n")
        self.__pass_time()
    
    def eat(self, food = 4):
        print("Mniam, mniam.  Dziękuję.")
        self.hunger -= food
        if self.hunger < 0:
            self.hunger = 0
        self.__pass_time()

    def play(self, fun = 4):
        print("Hura!")
        self.boredom -= fun
        if self.boredom < 0:
            self.boredom = 0
        self.__pass_time()


def main():
    crit_name = input("Jak chcesz nazwać swojego zwierzaka?: ")
    crit = Critter(crit_name)

    choice = None  
    while choice != "0":
        print \
        ("""
        Opiekun zwierzaka
    
        0 - zakończ
        1 - słuchaj swojego zwierzaka
        2 - nakarm swojego zwierzaka
        3 - pobaw się ze swoim zwierzakiem
        """)
    
        choice = input("Wybierasz: ")
        print()

        # wyjdź z pętli 
        if choice == "0":
            print("Do widzenia.")

        # słuchaj swojego zwierzaka
        elif choice == "1":
            crit.talk()
        
        # nakarm swojego zwierzaka
        elif choice == "2":
            crit.eat()
         
        # pobaw się ze swoim zwierzakiem
        elif choice == "3":
            crit.play()

        # nieznany wybór 
        else:
            print("\nNiestety,", choice, "nie jest prawidłowym wyborem.")

main()
input("\n\nAby zakończyć program, naciśnij klawisz Enter.") 
