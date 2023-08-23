# Leniwe przyciski 2
# Demonstruje użycie klasy w programie wykorzystującym Tkinter

from tkinter import *

class Application(Frame):
    """ Aplikacja oparta na GUI z trzema przyciskami. """ 
    def __init__(self, master):
        """ Inicjalizuj ramkę. """
        super(Application, self).__init__(master)    
        self.grid()
        self.create_widgets()

    def create_widgets(self):
        """ Utwórz trzy przyciski, które nic nie robią. """
        # utwórz pierwszy przycisk
        self.bttn1 = Button(self, text = "Nic nie robię!")
        self.bttn1.grid()

        # utwórz drugi przycisk
        self.bttn2 = Button(self)
        self.bttn2.grid()	
        self.bttn2.configure(text = "Ja również!")

        # utwórz trzeci przycisk
        self.bttn3 = Button(self)
        self.bttn3.grid()
        self.bttn3["text"] = "To samo mnie dotyczy!"

# część główna
root = Tk()
root.title("Leniwe przyciski 2")
root.geometry("210x85")
app = Application(root)
root.mainloop()
