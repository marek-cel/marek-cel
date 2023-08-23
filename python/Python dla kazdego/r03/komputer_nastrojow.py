# Komputer nastrojów
# Demonstruje klauzulę elif

import random

print("Wyczuwam Twoją energię. Twoje prawdziwe emocje znajdują odbicie na moim ekranie.")
print("Jesteś...")

mood = random.randint(1, 3)

if mood == 1:
    # szczęśliwy
    print( \
    """
       -----------
       |         |
       | O    O  |
       |   <     |
       |         |
       | .     . |
       |  `...`  |
       -----------
                   """)
elif mood == 2:
    # obojętny  
    print( \
    """
       -----------
       |         |
       | O    O  |
       |   <     |
       |         |
       | ------  |
       |         |
       -----------
                   """)
elif mood == 3:
    # smutny
    print( \
    """
       -----------
       |         |
       | O    O  |
       |   <     |
       |         |
       |  .'.    |
       | '   '   |
       -----------
                   """)
else:
    print("Nieprawidłowa wartość nastroju! (Musisz być naprawdę w złym humorze).")

print("...dzisiaj.")

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")






