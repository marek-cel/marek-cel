# Patelnia w ruchu
# Demonstruje obsługę danych wejściowych z myszy

from livewires import games

games.init(screen_width = 640, screen_height = 480, fps = 50)

class Pan(games.Sprite):
    """" Patelnia sterowana myszą. """
    def update(self):
        """ Przejdź do współrzędnych myszy. """
        self.x = games.mouse.x
        self.y = games.mouse.y

def main():
    wall_image = games.load_image("sciana.jpg", transparent = False)
    games.screen.background = wall_image

    pan_image = games.load_image("patelnia.bmp")
    the_pan = Pan(image = pan_image,
                  x = games.mouse.x,
                  y = games.mouse.y)
    games.screen.add(the_pan)

    games.mouse.is_visible = False

    games.screen.event_grab = True

    games.screen.mainloop()

# wystartuj!
main()
