# Mad Lib
# Tworzy opowiadanie oparte na szczegółach wprowadzonych przez użytkownika

from tkinter import *

class Application(Frame):
    """
    Aplikacja z GUI, która tworzy opowiadanie oparte na danych
    wprowadzonych przez użytkownika.
    """
    def __init__(self, master):
        """ Inicjalizuj ramkę. """
        super(Application, self).__init__(master)  
        self.grid()
        self.create_widgets()

    def create_widgets(self):
        """
        Utwórz widżety potrzebne do pobrania informacji podanych przez
        użytkownika i wyświetlenia opowiadania.
        """
        # utwórz etykietę z instrukcją
        Label(self,
              text = "Wprowadź informacje do nowego opowiadania"
              ).grid(row = 0, column = 0, columnspan = 2, sticky = W)

        # utwórz etykietę i pole znakowe służące do wpisania imienia osoby
        Label(self,
              text = "Osoba: "
              ).grid(row = 1, column = 0, sticky = W)
        self.person_ent = Entry(self)
        self.person_ent.grid(row = 1, column = 1, sticky = W)

        # utwórz etykietę i pole znakowe do wpisania rzeczownika w liczbie mnogiej
        Label(self,
              text = "Rzeczownik w liczbie mnogiej:"
              ).grid(row = 2, column = 0, sticky = W)
        self.noun_ent = Entry(self)
        self.noun_ent.grid(row = 2, column = 1, sticky = W)

        # utwórz etykietę i pole znakowe służące do wpisania czasownika
        Label(self,
              text = "Czasownik:"
              ).grid(row = 3, column = 0, sticky = W)
        self.verb_ent = Entry(self)
        self.verb_ent.grid(row = 3, column = 1, sticky = W)
     
        # utwórz etykietę do pól wyboru przymiotników
        Label(self,
              text = "Przymiotnik(i):"
              ).grid(row = 4, column = 0, sticky = W)

        # utwórz pole wyboru przymiotnika 'naglące'
        self.is_itchy = BooleanVar()
        Checkbutton(self,
                    text = "naglące",
                    variable = self.is_itchy
                    ).grid(row = 4, column = 1, sticky = W)

        # utwórz pole wyboru przymiotnika 'radosne'
        self.is_joyous = BooleanVar()
        Checkbutton(self,
                    text = "radosne",
                    variable = self.is_joyous
                    ).grid(row = 4, column = 2, sticky = W)

        # utwórz pole wyboru przymiotnika 'elektryzujące'
        self.is_electric = BooleanVar()
        Checkbutton(self,
                    text = "elektryzujące",
                    variable = self.is_electric
                    ).grid(row = 4, column = 3, sticky = W)

        # utwórz etykietę do przycisków opcji odnoszących się do części ciała
        Label(self,
              text = "Część ciała:"
              ).grid(row = 5, column = 0, sticky = W)

        # utwórz zmienną na pojedynczą część ciała
        self.body_part = StringVar()
        self.body_part.set(None)
  
        # utwórz przyciski opcji odnoszące się do części ciała
        body_parts = ["pępek", "duży palec u nogi", "rdzeń przedłużony"]
        column = 1
        for part in body_parts:
            Radiobutton(self,
                        text = part,
                        variable = self.body_part,
                        value = part
                        ).grid(row = 5, column = column, sticky = W)
            column += 1

        # utwórz przycisk akceptacji danych
        Button(self,
               text = "Kliknij, aby wyświetlić opowiadanie",
               command = self.tell_story
               ).grid(row = 6, column = 0, sticky = W)

        self.story_txt = Text(self, width = 75, height = 10, wrap = WORD)
        self.story_txt.grid(row = 7, column = 0, columnspan = 4)

    def tell_story(self):
        """ Wpisz w pole tekstowe nowe opowiadanie oparte na danych użytkownika. """
        # pobierz wartości z interfejsu GUI
        person = self.person_ent.get()
        noun = self.noun_ent.get()
        verb = self.verb_ent.get()
        adjectives = ""
        if self.is_itchy.get():
            adjectives += "naglące, "
        if self.is_joyous.get():
            adjectives += "radosne, "
        if self.is_electric.get():
            adjectives += "elektryzujące, "
        body_part = self.body_part.get()

        # create the story
        story = "Sławny badacz i odkrywca "
        story += person
        story += " o mało co nie zrezygnował z życiowej misji poszukiwania "
        story += "zaginionego miasta, które zamieszkiwały "
        story += noun
        story += ", gdy pewnego dnia "
        story += noun
        story += " znalazły "
        story += person + "a. "
        story += "Silne, "
        story += adjectives
        story += "osobliwe uczucie owładnęło badaczem. "
        story += "Po tak długim czasie poszukiwanie wreszcie się zakończyło. W oku "
        story += person + "a pojawiła się łza, która spadła na jego "
        story += body_part + ". "
        story += "A wtedy "
        story += noun
        story += " szybko pożarły "
        story += person + "a. "
        story += "Jaki morał płynie z tego opowiadania? Pomyśl, zanim zaczniesz coś "
        story += verb
        story += "."
        
        # wyświetl opowiadanie                                
        self.story_txt.delete(0.0, END)
        self.story_txt.insert(0.0, story)

# część główna
root = Tk()
root.title("Mad Lib")
app = Application(root)
root.mainloop()
