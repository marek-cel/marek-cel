# Dźwięk i muzyka
# Demonstruje odtwarzanie plików dźwiękowych i muzycznych

from livewires import games

games.init(screen_width = 640, screen_height = 480, fps = 50)

# załaduj plik dźwiękowy
missile_sound = games.load_sound("pocisk.wav")

# załaduj plik muzyczny
games.music.load("temat.mid")

choice = None
while choice != "0":

    print(
    """
    Dźwięk i muzyka
    
    0 - zakończ
    1 - odtwórz dźwięk pocisku
    2 - odtwarzaj cyklicznie dźwięk pocisku
    3 - zatrzymaj odtwarzanie dźwięku pocisku
    4 - odtwórz temat muzyczny
    5 - odtwarzaj cyklicznie temat muzyczny
    6 - zatrzymaj odtwarzanie tematu muzycznego
    """
    )
    
    choice = input("Wybieram: ")
    print()

    # wyjdź
    if choice == "0":
        print("Żegnaj!")

    # odtwórz dźwięk pocisku
    elif choice == "1":
        missile_sound.play()
        print("Odtworzenie dźwięku pocisku.")

    # odtwarzaj cyklicznie dźwięk pocisku
    elif choice == "2":
        loop = int(input("Ile razy powtórzyć odtwarzanie? (-1 = bez końca): "))
        missile_sound.play(loop)
        print("Cykliczne odtwarzanie dźwięku pocisku.")

    # zatrzymaj odtwarzanie dźwięku pocisku
    elif choice == "3":
        missile_sound.stop()
        print("Zatrzymanie odtwarzania dźwięku pocisku.")

    # odtwórz temat muzyczny
    elif choice == "4":
        games.music.play()
        print("Odtworzenie tematu muzycznego.")

    # odtwarzaj cyklicznie temat muzyczny
    elif choice == "5":
        loop = int(input("Ile razy powtórzyć odtwarzanie? (-1 = bez końca): "))
        games.music.play(loop)
        print("Cykliczne odtwarzanie tematu muzycznego.")

    # zatrzymaj odtwarzanie tematu muzycznego
    elif choice == "6":
        games.music.stop()
        print("Zatrzymanie odtwarzania tematu muzycznego.")
                 
    # nieprzewidziany wybór
    else:
        print("\nNiestety,", choice, "nie jest prawidłowym wyborem.")
  
input("\n\nAby zakończyć program, naciśnij klawisz Enter.")
