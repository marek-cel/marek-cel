# Pogromca Obcych
# Demonstruje współdziałanie obiektów

class Player(object):
    """ Gracz w grze strzelance. """
    def blast(self, enemy):
        print("Gracz razi wroga.\n")
        enemy.die()

class Alien(object):
    """ Obcy w grze strzelance. """
    def die(self):
        print("Obcy z trudem łapie oddech, 'To już koniec.  Ale wielki koniec... \n" \
              "Tak, już robi się ciemno. Powiedz moim dwóm milionom larw, że je kochałem... \n" \
              "Żegnaj, okrutny Wszechświecie.'")

# main
print("\t\tŚmierć Obcego\n")

hero = Player()
invader = Alien()
hero.blast(invader)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
