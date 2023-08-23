# Metkownica
# Demonstruje etykietę

from tkinter import *

# utwórz okno główne
root = Tk()
root.title("Metkownica")
root.geometry("200x50")

# utwórz w oknie ramkę jako pojemnik na inne widżety
app = Frame(root)
app.grid()

# utwórz w ramce etykietę 
lbl = Label(app, text = "Jestem etykietą!")
lbl.grid()

# uruchom pętlę zdarzeń okna
root.mainloop()
