# Rzut kośćmi
# Demonstruje generowanie liczb losowych

import random

# generuj liczby losowe z zakresu 1 - 6
die1 = random.randint(1, 6) 
die2 = random.randrange(6) + 1

total = die1 + die2

print("Wyrzuciłeś", die1, "oraz", die2, "i uzyskałeś sumę", total)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
