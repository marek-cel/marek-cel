# Uczestnik funduszu powierniczego - poprawna wersja
# Demonstruje konwersję typów

print(
"""
            Uczestnik funduszu powierniczego

Sumuje Twoje miesięczne wydatki, żeby Twój fundusz powierniczy się nie wyczerpał
(bo wtedy byłbyś zmuszony do podjęcia prawdziwej pracy).

Wprowadź swoje wymagane miesięczne koszty.  Ponieważ jesteś bogaty, zignoruj
grosze i swoje kwoty podaj w pełnych złotych.

"""
)

car =  input("Serwis Mercedesa: ")
car = int(car)

rent = int(input("Apartament w Śródmieściu: "))
jet = int(input("Wynajem prywatnego samolotu: "))
gifts = int(input("Podarunki: "))
food = int(input("Obiady w restauracjach: "))
staff = int(input("Personel (służba domowa, kucharz, kierowca, asystent): "))
guru = int(input("Osobisty guru i coach: "))
games = int(input("Gry komputerowe: "))

total = car + rent + jet + gifts + food + staff + guru + games

print("\nOgółem:", total)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")

