# Analizator komunikatów
# Demonstruje funkcję len() i operator in 

message = input("Wprowadź komunikat: ")

print("\nDługość Twojego komunikatu wynosi:", len(message))

print("\nNajczęściej używana litera w języku polskim, 'a',")
if "a" in message:
    print("wystąpiła w Twoim komunikacie.")
else:
    print("nie wystąpiła w Twoim komunikacie.")

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")

