# Astrocrash05
# Ograniczenie tempa wystrzeliwania pocisków

import math, random
from livewires import games

games.init(screen_width = 640, screen_height = 480, fps = 50)


class Asteroid(games.Sprite):
    """ Asteroida przelatująca przez ekran. """
    SMALL = 1
    MEDIUM = 2
    LARGE = 3
    images = {SMALL  : games.load_image("asteroida_mala.bmp"),
              MEDIUM : games.load_image("asteroida_sred.bmp"),
              LARGE  : games.load_image("asteroida_duza.bmp") }

    SPEED = 2
      
    def __init__(self, x, y, size):
        """ Inicjalizuj duszka asteroidy. """
        super(Asteroid, self).__init__(
            image = Asteroid.images[size],
            x = x, y = y,
            dx = random.choice([1, -1]) * Asteroid.SPEED * random.random()/size, 
            dy = random.choice([1, -1]) * Asteroid.SPEED * random.random()/size)
       
        self.size = size

    def update(self):
        """ Przenieś asteroidę na przeciwległy brzeg ekranu. """    
        if self.top > games.screen.height:
            self.bottom = 0
 
        if self.bottom < 0:
            self.top = games.screen.height

        if self.left > games.screen.width:
            self.right = 0

        if self.right < 0:
            self.left = games.screen.width


class Ship(games.Sprite):
    """ Statek kosmiczny gracza. """
    image = games.load_image("statek.bmp")
    sound = games.load_sound("przyspieszenie.wav")
    ROTATION_STEP = 3
    VELOCITY_STEP = .03
    MISSILE_DELAY = 25

    def __init__(self, x, y):
        """ Inicjalizuj duszka statku. """
        super(Ship, self).__init__(image = Ship.image, x = x, y = y)
        self.missile_wait = 0

    def update(self):
        """ Obracaj i przyśpieszaj statek w zależności od naciśniętych klawiszy. """
        # obróć statek zależnie od naciśniętych klawiszy strzałek (w prawo lub w lewo)
        if games.keyboard.is_pressed(games.K_LEFT):
            self.angle -= Ship.ROTATION_STEP        
        if games.keyboard.is_pressed(games.K_RIGHT):
            self.angle += Ship.ROTATION_STEP

        # zastosuj siłę ciągu przy naciśniętym klawiszu strzałki w górę
        if games.keyboard.is_pressed(games.K_UP):
            Ship.sound.play()
            
            # zmień składowe prędkości w zależności od kąta położenia statku
            angle = self.angle * math.pi / 180  # zamień na radiany
            self.dx += Ship.VELOCITY_STEP * math.sin(angle)
            self.dy += Ship.VELOCITY_STEP * -math.cos(angle)

        # przenieś statek na przeciwległy brzeg ekranu    
        if self.top > games.screen.height:
            self.bottom = 0
 
        if self.bottom < 0:
            self.top = games.screen.height

        if self.left > games.screen.width:
            self.right = 0

        if self.right < 0:
            self.left = games.screen.width

        # jeśli czekasz, aż statek będzie mógł wystrzelić następny pocisk,
        # zmniejsz czas oczekiwania
        if self.missile_wait > 0:
            self.missile_wait -= 1
            
        # wystrzel pocisk, jeśli klawisz spacji jest naciśnięty i skończył się
        # czas oczekiwania
        if games.keyboard.is_pressed(games.K_SPACE) and self.missile_wait == 0:
            new_missile = Missile(self.x, self.y, self.angle)
            games.screen.add(new_missile)
            self.missile_wait = Ship.MISSILE_DELAY


class Missile(games.Sprite):
    """ Pocisk wystrzelony przez statek gracza. """
    image = games.load_image("pocisk.bmp")
    sound = games.load_sound("pocisk.wav")
    BUFFER = 40
    VELOCITY_FACTOR = 7
    LIFETIME = 40

    def __init__(self, ship_x, ship_y, ship_angle):
        """ Inicjalizuj duszka pocisku. """
        Missile.sound.play()

        # zamień na radiany
        angle = ship_angle * math.pi / 180  

        # oblicz pozycję początkową pocisku 
        buffer_x = Missile.BUFFER * math.sin(angle)
        buffer_y = Missile.BUFFER * -math.cos(angle)
        x = ship_x + buffer_x
        y = ship_y + buffer_y

        # oblicz składowe prędkości pocisku
        dx = Missile.VELOCITY_FACTOR * math.sin(angle)
        dy = Missile.VELOCITY_FACTOR * -math.cos(angle)

        # utwórz pocisk
        super(Missile, self).__init__(image = Missile.image,
                                      x = x, y = y,
                                      dx = dx, dy = dy)
        self.lifetime = Missile.LIFETIME

    def update(self):
        """ Obsługuj ruch pocisku. """
        # zniszcz pocisk, jeśli wyczerpał się jego czas życia
        self.lifetime -= 1
        if self.lifetime == 0:
            self.destroy()

        # przenieś pocisk na przeciwległy brzeg ekranu    
        if self.top > games.screen.height:
            self.bottom = 0
 
        if self.bottom < 0:
            self.top = games.screen.height

        if self.left > games.screen.width:
            self.right = 0

        if self.right < 0:
            self.left = games.screen.width


def main():
    # ustal tło
    nebula_image = games.load_image("mglawica.jpg")
    games.screen.background = nebula_image

    # utwórz 8 asteroid
    for i in range(4):
        x = random.randrange(games.screen.width)
        y = random.randrange(games.screen.height)
        size = random.choice([Asteroid.SMALL, Asteroid.MEDIUM, Asteroid.LARGE])
        new_asteroid = Asteroid(x = x, y = y, size = size)
        games.screen.add(new_asteroid)

    # utwórz statek
    the_ship = Ship(x = games.screen.width/2, y = games.screen.height/2)
    games.screen.add(the_ship)
        
    games.screen.mainloop()

# wystartuj!
main()

