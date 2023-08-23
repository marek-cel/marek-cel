# Astrocrash07
# Dodanie eksplozji

import math, random
from livewires import games

games.init(screen_width = 640, screen_height = 480, fps = 50)


class Wrapper(games.Sprite):
    """ Duszek, którego tor lotu owija się wokół ekranu. """
    def update(self):
        """ Przenieś duszka na przeciwległy brzeg ekranu. """    
        if self.top > games.screen.height:
            self.bottom = 0

        if self.bottom < 0:
            self.top = games.screen.height

        if self.left > games.screen.width:
            self.right = 0

        if self.right < 0:
            self.left = games.screen.width

    def die(self):
        """ Zniszcz się. """
        self.destroy()


class Collider(Wrapper):
    """ Obiekt klasy Wrapper, który może zderzyć się z innym obiektem. """
    def update(self):
        """ Sprawdź, czy duszki nie zachodzą na siebie. """
        super(Collider, self).update()
        
        if self.overlapping_sprites:
            for sprite in self.overlapping_sprites:
                sprite.die()
            self.die()               

    def die(self):
        """ Zniszcz się i pozostaw po sobie eksplozję. """
        new_explosion = Explosion(x = self.x, y = self.y)
        games.screen.add(new_explosion)
        self.destroy()


class Asteroid(Wrapper):
    """ Asteroida przelatująca przez ekran. """
    SMALL = 1
    MEDIUM = 2
    LARGE = 3
    images = {SMALL  : games.load_image("asteroida_mala.bmp"),
              MEDIUM : games.load_image("asteroida_sred.bmp"),
              LARGE  : games.load_image("asteroida_duza.bmp") }

    SPEED = 2
    SPAWN = 2
      
    def __init__(self, x, y, size):
        """ Inicjalizuj duszka asteroidy. """
        super(Asteroid, self).__init__(
            image = Asteroid.images[size],
            x = x, y = y,
            dx = random.choice([1, -1]) * Asteroid.SPEED * random.random()/size, 
            dy = random.choice([1, -1]) * Asteroid.SPEED * random.random()/size)
        
        self.size = size

    def die(self):
        """ Zniszcz asteroidę. """
        # jeśli nie jest to mała asteroida, zastąp ją dwoma mniejszymi
        if self.size != Asteroid.SMALL:
            for i in range(Asteroid.SPAWN):
                new_asteroid = Asteroid(x = self.x,
                                        y = self.y,
                                        size = self.size - 1)
                games.screen.add(new_asteroid)
                
        super(Asteroid, self).die()


class Ship(Collider):
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
        """ Obracaj statek, przyśpieszaj i wystrzeliwuj pociski, zależnie od naciśniętych klawiszy. """
        super(Ship, self).update()
        
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


class Missile(Collider):
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
        super(Missile, self).update()
        
        # zniszcz pocisk, jeśli wyczerpał się jego czas życia   
        self.lifetime -= 1
        if self.lifetime == 0:
            self.destroy()


class Explosion(games.Animation):
    """ Animacja eksplozji. """
    sound = games.load_sound("eksplozja.wav")
    images = ["eksplozja1.bmp",
              "eksplozja2.bmp",
              "eksplozja3.bmp",
              "eksplozja4.bmp",
              "eksplozja5.bmp",
              "eksplozja6.bmp",
              "eksplozja7.bmp",
              "eksplozja8.bmp",
              "eksplozja9.bmp"]

    def __init__(self, x, y):
        super(Explosion, self).__init__(images = Explosion.images,
                                        x = x, y = y,
                                        repeat_interval = 4, n_repeats = 1,
                                        is_collideable = False)
        Explosion.sound.play()


def main():
    # ustaw tło
    nebula_image = games.load_image("mglawica.jpg")
    games.screen.background = nebula_image

    # utwórz 8 asteroid
    for i in range(8):
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
