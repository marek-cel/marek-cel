# Wygrałeś
# Demonstruje wyświetlanie komunikatu

from livewires import games, color

games.init(screen_width = 640, screen_height = 480, fps = 50)

wall_image = games.load_image("sciana.jpg", transparent = False)
games.screen.background = wall_image

won_message = games.Message(value = "Wygrałeś!",
                            size = 100,
                            color = color.red,
                            x = games.screen.width/2,
                            y = games.screen.height/2,
                            lifetime = 250,
                            after_death = games.screen.quit)
games.screen.add(won_message)

games.screen.mainloop()
