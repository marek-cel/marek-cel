# Inwentarz bohatera 2.0
# Demonstruje krotki

# utwórz krotkę zawierającą pewne elementy i wyświetl jej zawartość
# za pomocą pętli for
inventory = ("miecz",
             "zbroja",
             "tarcza",
             "napój uzdrawiający")
print("Elementy Twojego inwentarza:")
for item in inventory:
    print(item)

input("\nAby kontynuować grę, naciśnij klawisz Enter.")

# wyświetl długość krotki
print("Twój dobytek zawiera", len(inventory), "elementy(-ów).")

input("\nAby kontynuować grę, naciśnij klawisz Enter.")

# sprawdź, czy element należy do krotki, za pomocą operatora in
if "napój uzdrawiający" in inventory:
    print("Dożyjesz dnia, w którym stoczysz walkę.")

# wyświetl jeden element wskazany przez indeks
index = int(input("\nWprowadź indeks elementu inwentarza: "))
print("Pod indeksem", index, "znajduje się", inventory[index])

# wyświetl wycinek
start = int(input("\nWprowadź indeks wyznaczający początek wycinka: "))
finish = int(input("\nWprowadź indeks wyznaczający koniec wycinka: "))
print("inventory[", start, ":", finish, "] to", end=" ")
print(inventory[start:finish])

input("\nAby kontynuować grę, naciśnij klawisz Enter.")

# dokonaj konkatenacji dwóch krotek
chest = ("złoto", "klejnoty")
print("Znajdujesz skrzynię, która zawiera:")
print(chest)
print("Dodajesz zawartość skrzyni do swojego inwentarza.")
inventory += chest
print("Twój aktualny inwentarz to:")
print(inventory)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
