# Zamarynuj to
# Demonstruje marynowanie i odkładanie danych na półkę

import pickle, shelve

print("Marynowanie list.")
variety = ["łagodny", "pikantny", "kwaszony"]
shape = ["cały", "krojony wzdłuż", "w plasterkach"]
brand = ["Dawtona", "Klimex", "Vortumnus"]
f = open("pikle1.dat", "wb")
pickle.dump(variety, f)
pickle.dump(shape, f)
pickle.dump(brand, f)
f.close()

print("\nOdmarynowanie list.")
f = open("pikle1.dat", "rb")
variety = pickle.load(f)
shape = pickle.load(f)
brand = pickle.load(f)
print(variety)
print(shape)
print(brand)
f.close()

print("\nOdkładanie list na półkę.")
s = shelve.open("pikle2.dat")
s["odmiana"] = ["łagodny", "pikantny", "kwaszony"]
s["kształt"] = ["cały", "krojony wzdłuż", "w plasterkach"]
s["marka"] = ["Dawtona", "Klimex", "Vortumnus"]
s.sync()    # upewnij się, że dane zostały zapisane

print("\nPobieranie list z pliku półki:")
print("marka -", s["marka"])
print("kształt -", s["kształt"])
print("odmiana -", s["odmiana"])
s.close()

input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
