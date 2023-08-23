# Ekskluzywna sieć
# Demonstruje operatory logiczne i warunki złożone

print("\tEkskluzywna Sieć Komputerowa")
print("\t    Tylko dla członków!\n")

security = 0

username = ""
while not username:
    username = input("Użytkownik: ")

password = ""
while not password:
    password = input("Hasło: ")

if username == "M.Dawson" and password == "sekret":
    print("Cześć, Mike!")
    security = 5
elif username == "S.Meier" and password == "cywilizacja":
    print("Hej, Sid!")
    security = 3
elif username == "S.Miyamoto" and password == "mariobros":
    print("Co u Ciebie, Shigeru?")
    security = 3
elif username == "W.Wright" and password == "simsowie":
    print("Jak leci, Will?")
    security = 3
elif username == "gość" or password == "gość":
    print("Witaj, Gościu!")
    security = 1
else:
    print("Nieudana próba logowania. Nie jesteś taki wyjątkowy.\n")

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
