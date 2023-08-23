# Pobierz i zwróć
# Demonstruje parametry i wartości zwrotne

def display(message):
    print(message)

def give_me_five():
    five = 5
    return five

def ask_yes_no(question):
    """Zadaj pytanie, na które można odpowiedzieć tak lub nie."""
    response = None
    while response not in ("t", "n"):
        response = input(question).lower()
    return response

# main
display("To wiadomość dla Ciebie.\n")

number = give_me_five()
print("Oto co otrzymałem z funkcji give_me_five():", number)

answer = ask_yes_no("\nProszę wprowadzić 't' lub 'n': ")
print("Dziękuję za wprowadzenie:", answer)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
