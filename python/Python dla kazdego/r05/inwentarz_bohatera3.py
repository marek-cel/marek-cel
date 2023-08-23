# Inwentarz bohatera 3.0
# Demonstruje listy

# utwórz listę zawierającą pewne elementy i wyświetl jej zawartość
# za pomocą pętli for
inventory = ["miecz", "zbroja", "tarcza", "napój uzdrawiający"]
print("Elementy Twojego inwentarza:")
for item in inventory:
    print(item)

input("\nAby kontynuować grę, naciśnij klawisz Enter.")

# wyświetl długość listy
print("Twój dobytek zawiera", len(inventory), "elementy(-ów).")

input("\nAby kontynuować grę, naciśnij klawisz Enter.")

# sprawdź, czy element należy do listy, za pomocą operatora in
if "napój uzdrawiający" in inventory:
    print("Dożyjesz dnia, w którym stoczysz walkę.")

# wyświetl jeden element wskazany przez indeks
index = int(input("\nWprowadź indeks elementu inwentarza: "))
print("Pod indeksem", index, "znajduje się", inventory[index])

# wyświetl wycinek
start = int(input("\nWprowadź indeks wyznaczający początek wycinka: "))
finish = int(input("Wprowadź indeks wyznaczający koniec wycinka: "))
print("inventory[", start, ":", finish, "] to", end=" ")
print(inventory[start:finish])

input("\nAby kontynuować grę, naciśnij klawisz Enter.")

# dokonaj konkatenacji dwóch list
chest = ["złoto", "klejnoty"]
print("Znajdujesz skrzynię, która zawiera:")
print(chest)
print("Dodajesz zawartość skrzyni do swojego inwentarza.")
inventory += chest
print("Twój aktualny inwentarz to:")
print(inventory)

input("\nAby kontynuować grę, naciśnij klawisz Enter.")

# przypisz poprzez indeks
print("Wymieniasz swój miecz na kuszę.")
inventory[0] = "kusza"
print("Twój aktualny inwentarz to:")
print(inventory)

input("\nAby kontynuować grę, naciśnij klawisz Enter.")

# przypisz poprzez wycinek
print("Zużywasz swoje złoto i klejnoty na zakup kuli do wróżenia.")
inventory[4:6] = ["kula do wróżenia"]
print("Twój aktualny inwentarz to:")
print(inventory)

input("\nAby kontynuować grę, naciśnij klawisz Enter.")

# usuń element
print("W wielkiej bitwie Twoja tarcza zostaje zniszczona.")
del inventory[2]
print("Twój aktualny inwentarz to:")
print(inventory)

input("\nAby kontynuować grę, naciśnij klawisz Enter.")

# usuń wycinek
print("Tawoja kusza i zbroja zostały skradzione przez złodziei.")
del inventory[:2]
print("Twój aktualny inwentarz to:")
print(inventory)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
