# Szubienica
#
# Klasyczna gra w szubienicę.  Komputer losowo wybiera słowo,
# a gracz próbuje odgadnąć jego poszczególne litery.  Jeśli gracz
# nie odgadnie w porę całego słowa, mały ludzik zostaje powieszony.

# import modułów
import random

# stałe
HANGMAN = (
"""
 ------
 |    |
 |
 |
 |
 |
 |
 |
 |
----------
""",
"""
 ------
 |    |
 |    O
 |
 |
 |
 |
 |
 |
----------
""",
"""
 ------
 |    |
 |    O
 |   -+-
 | 
 |   
 |   
 |   
 |   
----------
""",
"""
 ------
 |    |
 |    O
 |  /-+-
 |   
 |   
 |   
 |   
 |   
----------
""",
"""
 ------
 |    |
 |    O
 |  /-+-/
 |   
 |   
 |   
 |   
 |   
----------
""",
"""
 ------
 |    |
 |    O
 |  /-+-/
 |    |
 |   
 |   
 |   
 |   
----------
""",
"""
 ------
 |    |
 |    O
 |  /-+-/
 |    |
 |    |
 |   | 
 |   | 
 |   
----------
""",
"""
 ------
 |    |
 |    O
 |  /-+-/
 |    |
 |    |
 |   | |
 |   | |
 |  
----------
""")

MAX_WRONG = len(HANGMAN) - 1
WORDS = ("NADUŻYWANY", "MAŁŻ", "GUAM", "TAFTA", "PYTHON")

# inicjalizacja zmiennych
word = random.choice(WORDS)   # słowo do odgadnięcia
so_far = "-" * len(word)      # kreska zastępuje nieodgadniętą literę
wrong = 0                     # liczba nietrafionych liter
used = []                     # litery już użyte w zgadywaniu


print("Witaj w grze 'Szubienica'.  Powodzenia!")

while wrong < MAX_WRONG and so_far != word:
    print(HANGMAN[wrong])
    print("\nWykorzystałeś już następujące litery:\n", used)
    print("\nNa razie zagadkowe słowo wygląda tak:\n", so_far)

    guess = input("\n\nWprowadź literę: ")
    guess = guess.upper()
    
    while guess in used:
        print("Już wykorzystałeś literę", guess)
        guess = input("Wprowadź literę: ")
        guess = guess.upper()

    used.append(guess)

    if guess in word:
        print("\nTak!", guess, "znajduje się w zagadkowym słowie!")

        # utwórz nową wersję zmiennej so_far, aby zawierała odgadniętą literę
        new = ""
        for i in range(len(word)):
            if guess == word[i]:
                new += guess
            else:
                new += so_far[i]              
        so_far = new

    else:
        print("\nNiestety,", guess, "nie występuje w zagadkowym słowie.")
        wrong += 1

if wrong == MAX_WRONG:
    print(HANGMAN[wrong])
    print("\nZostałeś powieszony!")
else:
    print("\nOdgadłeś!")
    
print("\nZagadkowe słowo to", word)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
