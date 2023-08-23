# Obraz tła
# Demonstruje ustawienie obrazu tła ekranu graficznego

from livewires import games

games.init(screen_width = 640, screen_height = 480, fps = 50)

wall_image = games.load_image("sciana.jpg", transparent = False)
games.screen.background = wall_image

games.screen.mainloop()
