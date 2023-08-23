# Inwentarz bohatera
# Demonstruje tworzenie krotek

# utwórz pustą krotkę
inventory = ()

# potraktuj krotkę jako warunek
if not inventory:
    print("Masz puste ręce.")

input("\nAby kontynuować misję, naciśnij klawisz Enter.")

# utwórz krotkę zawierającą pewne elementy
inventory = ("miecz",
             "zbroja",
             "tarcza",
             "napój uzdrawiający")

# wyświetl krotkę
print("\nWykaz zawartości krotki:")
print(inventory)

# wyświetl każdy element krotki
print("\nElementy Twojego wyposażenia:")
for item in inventory:
    print(item)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
