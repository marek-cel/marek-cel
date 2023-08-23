# Najlepsze wyniki
# Demonstruje metody listy

scores = []

choice = None
while choice != "0":

    print(
    """
    Najlepsze wyniki
    
    0 - zakończ
    1 - pokaż wyniki
    2 - dodaj wynik
    3 - usuń wynik 
    4 - posortuj wyniki
    """
    )
    
    choice = input("Wybierasz: ")
    print()

    # zakończ program
    if choice == "0":
        print("Do widzenia.")

    # wypisz tabelę najlepszych wyników
    elif choice == "1":
         print("Najlepsze wyniki")
         for score in scores:
            print(score)

    # dodaj wynik
    elif choice == "2":
        score = int(input("Jaki wynik uzyskałeś?: "))
        scores.append(score)

    # usuń wynik
    elif choice == "3":
        score = int(input("Który wynik usunąć?: "))
        if score in scores:
            scores.remove(score)
        else:
            print(score, "nie ma na liście wyników.")

    # posortuj wyniki
    elif choice == "4":
        scores.sort(reverse=True)

    # nieznana opcja
    else:
        print("Niestety,", choice, "nie jest prawidłowym wyborem.")
  
input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
