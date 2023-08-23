# Odczytaj klawisz
# Demonstruje odczytywanie klawiatury

from livewires import games

games.init(screen_width = 640, screen_height = 480, fps = 50)

class Ship(games.Sprite):
    """ Poruszający się statek kosmiczny. """
    def update(self):
        """ Kieruj ruchem statku na podstawie wciśniętych klawiszy. """
        if games.keyboard.is_pressed(games.K_w):
            self.y -= 1           
        if games.keyboard.is_pressed(games.K_s):
            self.y += 1
        if games.keyboard.is_pressed(games.K_a):
            self.x -= 1
        if games.keyboard.is_pressed(games.K_d):
            self.x += 1
 
def main():  
    nebula_image = games.load_image("mglawica.jpg", transparent = False)
    games.screen.background = nebula_image

    ship_image = games.load_image("statek.bmp")
    the_ship = Ship(image = ship_image,
                    x = games.screen.width/2,
                    y = games.screen.height/2)
    games.screen.add(the_ship)

    games.screen.mainloop()

main()
