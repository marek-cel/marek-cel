# Nieuchwytna pizza
# Demonstruje wykrywanie kolizji duszków

from livewires import games
import random

games.init(screen_width = 640, screen_height = 480, fps = 50)


class Pan(games.Sprite):
    """" Patelnia sterowana za pomocą myszy. """
    def update(self):
        """ Przesuń do pozycji myszy. """
        self.x = games.mouse.x
        self.y = games.mouse.y
        self.check_collide()
 
    def check_collide(self):
        """ Sprawdź, czy nie doszło do kolizji z pizzą. """
        for pizza in self.overlapping_sprites:
            pizza.handle_collide()


class Pizza(games.Sprite):
    """" Nieuchwytna pizza. """
    def handle_collide(self):
        """ Przemieść się w przypadkowe miejsce ekranu. """
        self.x = random.randrange(games.screen.width)
        self.y = random.randrange(games.screen.height)


def main():
    wall_image = games.load_image("sciana.jpg", transparent = False)
    games.screen.background = wall_image

    pizza_image = games.load_image("pizza.bmp")
    pizza_x = random.randrange(games.screen.width)
    pizza_y = random.randrange(games.screen.height)
    the_pizza = Pizza(image = pizza_image, x = pizza_x, y = pizza_y)
    games.screen.add(the_pizza)

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
