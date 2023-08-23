# Nieistotne fakty
#
# Uzyskuje dane osobiste od użytkownika, a potem
# wypisuje prawdziwe, lecz bezużyteczne informacje o nim

name = input("Cześć! Jak masz na imię? ")

age = input("Ile masz lat? ")
age = int(age)

weight = int(input("Dobrze, ostatnie pytanie. Ile kilogramów ważysz? "))

print("\nJeśli poeta ee cummings wysłałby do Ciebie wiadomość e-mail,\nzwróciłby się do Ciebie",
      name.lower())
print("Ale jeśli byłby wściekły, nazwałby Cię", name.upper())

called = name * 5
print("\nJeśli małe dziecko próbowałoby zwrócić na siebie Twoją uwagę,",)
print("Twoje imię przybrałoby formę:")
print(called)

seconds = age * 365 * 24 * 60 * 60
print("\nŻyjesz już ponad", seconds, "sekund.")

moon_weight = weight / 6
print("\nCzy wiesz, że na Księżycu Twoja waga wynosiłaby",
      moon_weight, "kg?")

sun_weight = weight * 27.1
print("Na Słońcu ważyłbyś (ważyłabyś)", sun_weight, "kg (ale niestety niedługo).")

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
