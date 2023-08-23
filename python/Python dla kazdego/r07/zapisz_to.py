# Zapisz to
# Demonstruje zapisywanie danych do pliku tekstowego

print("Utworzenie pliku tekstowego za pomocą metody write().")
text_file = open("zapisz_to.txt", "w")
text_file.write("Wiersz 1\n")
text_file.write("To jest wiersz 2\n")
text_file.write("Ten tekst tworzy wiersz 3\n")
text_file.close()

print("\nOdczytanie zawartości nowo utworzonego pliku.")
text_file = open("zapisz_to.txt", "r")
print(text_file.read())
text_file.close()

print("\nUtworzenie pliku tekstowego za pomocą metody writelines().")
text_file = open("zapisz_to.txt", "w")
lines = ["Wiersz 1\n",
         "To jest wiersz 2\n",
         "Ten tekst tworzy wiersz 3\n"]
text_file.writelines(lines)
text_file.close()

print("\nOdczytanie zawartości nowo utworzonego pliku.")
text_file = open("zapisz_to.txt", "r")
print(text_file.read())
text_file.close()

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
