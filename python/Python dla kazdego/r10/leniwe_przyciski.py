# Leniwe przyciski
# Demonstruje tworzenie przycisków

from tkinter import *

# utwórz okno główne
root = Tk()
root.title("Leniwe przyciski")
root.geometry("200x85")

# utwórz w oknie ramkę do pomieszczenia innych widżetów
app = Frame(root)
app.grid()

# utwórz w ramce przycisk
bttn1 = Button(app, text = "Nic nie robię!")
bttn1.grid()

# utwórz w ramce drugi przycisk
bttn2 = Button(app)
bttn2.grid()
bttn2.configure(text = "Ja również!")

# utwórz w ramce trzeci przycisk
bttn3 = Button(app)
bttn3.grid()
bttn3["text"]= "To samo mnie dotyczy!"

# uruchom pętlę zdarzeń okna głównego
root.mainloop()
