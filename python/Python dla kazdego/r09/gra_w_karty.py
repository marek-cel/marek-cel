# Gra w karty
# Demonstruje tworzenie kombinacji obiektów

class Card(object):
    """ Karta do gry. """
    RANKS = ["A", "2", "3", "4", "5", "6", "7",
             "8", "9", "10", "J", "Q", "K"]
    SUITS = ["c", "d", "h", "s"]
    
    def __init__(self, rank, suit):
        self.rank = rank 
        self.suit = suit

    def __str__(self):
        rep = self.rank + self.suit
        return rep


class Hand(object):
    """ Ręka - karty do gry w ręku gracza. """
    def __init__(self):
        self.cards = []

    def __str__(self):
        if self.cards:
           rep = ""
           for card in self.cards:
               rep += str(card) + "  "
        else:
            rep = "<pusta>"
        return rep

    def clear(self):
        self.cards = []

    def add(self, card):
        self.cards.append(card)

    def give(self, card, other_hand):
        self.cards.remove(card)
        other_hand.add(card)


# część główna
card1 = Card(rank = "A", suit = "c")
print("Wyświetlam obiekt karty (klasy Card):")
print(card1)

card2 = Card(rank = "2", suit = "c")
card3 = Card(rank = "3", suit = "c")
card4 = Card(rank = "4", suit = "c")
card5 = Card(rank = "5", suit = "c")
print("\nWyświetlam resztę obiektów po jednym na raz:")
print(card2)
print(card3)
print(card4)
print(card5)

my_hand = Hand()
print("\nWyświetlam zawartość mojej ręki przed dodaniem jakichkolwiek kart:")
print(my_hand)

my_hand.add(card1)
my_hand.add(card2)
my_hand.add(card3)
my_hand.add(card4)
my_hand.add(card5)
print("\nWyświetlam zawartość mojej ręki po dodaniu 5 kart:")
print(my_hand)

your_hand = Hand()
my_hand.give(card1, your_hand)
my_hand.give(card2, your_hand)
print("\nPrzekazuję pierwsze dwie karty z mojej ręki do Twojej.")
print("Twoja ręka:")
print(your_hand)
print("Moja ręka:")
print(my_hand)

my_hand.clear()
print("\nMoja ręka po usunięciu z niej kart:")
print(my_hand)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")

