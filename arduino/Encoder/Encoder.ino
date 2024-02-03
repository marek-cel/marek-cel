#include <Encoder.h>

#include <typedefs.h>
#include <pins.h>
#include <pins_mega.h>
#include <pins_std.h>
#include <defines.h>
#include <Common.h>

#include <LiquidCrystal.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

////////////////////////////////////////////////////////////////////////////////

#define BUILT_IN_LED_PIN LED_BUILTIN

#define BUTTON_PIN 4

#define ENCODER_PIN_A 6
#define ENCODER_PIN_B 7

#define LED_PIN_A 14
#define LED_PIN_B 15

////////////////////////////////////////////////////////////////////////////////

uint8_t _led = 0;

uint8_t _pins2_new = 0b0;
uint8_t _pins2_old = 0b0;

int8_t _test_val = 0;

Encoder _encoder( ENCODER_PIN_A, ENCODER_PIN_B );

// initialize the library with the numbers of the interface pins
LiquidCrystal _lcd( 2, 3, 8, 9, 10, 11 );

////////////////////////////////////////////////////////////////////////////////

inline void initButton();
inline void initEncoder();
inline void initLEDs();

void eventButton();
void eventEncoder();

void setLED( uint8_t led );
void setLED_A( uint8_t led );
void setLED_B( uint8_t led );

////////////////////////////////////////////////////////////////////////////////

ISR( PCINT2_vect )
{
    _pins2_old = _pins2_new;
    _pins2_new = *getDigitalPinPIN( BUTTON_PIN );

    uint8_t diff = _pins2_new ^ _pins2_old;

    if ( diff & getDigitalPinMask( BUTTON_PIN ) )
    {
        eventButton();
    }

    if ( ( diff & getDigitalPinMask( ENCODER_PIN_A ) )
      || ( diff & getDigitalPinMask( ENCODER_PIN_B ) ) )
    {
        eventEncoder();
    }
}

////////////////////////////////////////////////////////////////////////////////

ISR( BADISR_vect ) {}

////////////////////////////////////////////////////////////////////////////////

void setup()
{
    // set up the LCD's number of columns and rows:
    _lcd.begin( 16, 2 );
    // Print a message to the LCD.
    _lcd.print("Encoder Test");
    //_lcd.setCursor(0, 1);
    //_lcd.print( _test_val );

    initBoard();
    initButton();
    initEncoder();
    initLEDs();

    _pins2_new = *getDigitalPinPIN( BUTTON_PIN );

    sei();
}

////////////////////////////////////////////////////////////////////////////////

void loop()
{
    //setLED_A( digitalRead( ENCODER_PIN_A ) == HIGH );
    //setLED_B( digitalRead( ENCODER_PIN_B ) == HIGH );
    
    setLED_A( _test_val & 0b01 );
    setLED_B( _test_val & 0b10 );
    
    _lcd.setCursor(0, 1);
    //_lcd.print( _test_val );
    _lcd.print( millis()/1000 );
}

////////////////////////////////////////////////////////////////////////////////

void initButton()
{
    pinMode( BUTTON_PIN, INPUT_PULLUP );
    enablePCINT( BUTTON_PIN );
}

////////////////////////////////////////////////////////////////////////////////

void initEncoder()
{
    pinMode( ENCODER_PIN_A, INPUT_PULLUP );
    pinMode( ENCODER_PIN_B, INPUT_PULLUP );

    enablePCINT( ENCODER_PIN_A );
    enablePCINT( ENCODER_PIN_B );
}

////////////////////////////////////////////////////////////////////////////////

void initLEDs()
{
    pinMode( BUILT_IN_LED_PIN, OUTPUT );
    
    pinMode( LED_PIN_A, OUTPUT );
    pinMode( LED_PIN_B, OUTPUT );
}

////////////////////////////////////////////////////////////////////////////////

void eventButton()
{
    if( !getDigitalPinState( BUTTON_PIN ) )
    {
        _led = !_led;
        setLED( _led );
    }
}

////////////////////////////////////////////////////////////////////////////////

void eventEncoder()
{
    switch( _encoder.read() )
    {
        case -1: _led = 0; _test_val -= 1; break;
        case  1: _led = 1; _test_val += 1; break;
    }
    
    setLED( _led );
}

////////////////////////////////////////////////////////////////////////////////

void setLED( uint8_t led )
{
    if ( led )
        digitalWrite( BUILT_IN_LED_PIN, HIGH );
    else
        digitalWrite( BUILT_IN_LED_PIN, LOW );
}

////////////////////////////////////////////////////////////////////////////////

void setLED_A( uint8_t led )
{
    if ( led )
        digitalWrite( LED_PIN_A, HIGH );
    else
        digitalWrite( LED_PIN_A, LOW );
}

////////////////////////////////////////////////////////////////////////////////

void setLED_B( uint8_t led )
{
    if ( led )
        digitalWrite( LED_PIN_B, HIGH );
    else
        digitalWrite( LED_PIN_B, LOW );
}


