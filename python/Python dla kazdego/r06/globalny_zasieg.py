# Globalny zasięg
# Demonstruje zmienne globalne

def read_global():
    print("Wartość zmiennej value odczytana wewnątrz zakresu lokalnego",
          "\nfunkcji read_global() wynosi:", value)

def shadow_global():
    value = -10
    print("Wartość zmiennej value odczytana wewnątrz zakresu lokalnego",
          "\nfunkcji shadow_global() wynosi:", value)
  
def change_global():
    global value
    value = -10
    print("Wartość zmiennej value odczytana wewnątrz zakresu lokalnego",
          "\nfunkcji change_global() wynosi:", value)

# główna część programu
# value jest zmienną globalną, ponieważ jesteśmy teraz w zakresie globalnym
value = 10
print("W zakresie globalnym wartość zmiennej value została ustawiona na:", value, "\n")

read_global()
print("Po powrocie do zakresu globalnego wartość zmiennej value nadal wynosi:", value,
      "\n")

shadow_global()
print("Po powrocie do zakresu globalnego wartość zmiennej value nadal wynosi:", value,
      "\n")

change_global()
print("Po powrocie do zakresu globalnego okazuje się, że wartość zmiennej value",
      "\nzmieniła się na:", value)

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")










