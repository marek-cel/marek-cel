# Pizza w ruchu
# Demonstruje określanie parametrów prędkości ruchu duszka

from livewires import games

games.init(screen_width = 640, screen_height = 480, fps = 50) 

wall_image = games.load_image("sciana.jpg", transparent = False)
games.screen.background = wall_image

pizza_image = games.load_image("pizza.bmp")
the_pizza = games.Sprite(image = pizza_image,
                         x = games.screen.width/2,
                         y = games.screen.height/2,
                         dx = 1,
                         dy = 1)
games.screen.add(the_pizza)

games.screen.mainloop()

