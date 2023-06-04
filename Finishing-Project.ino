#include<Wire.h>
#include<ezButton.h>
#include<LiquidCrystal_I2C.h>
#include "NeoPixel.h"
#include "Vector2.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

#define BTN_PIN 2
#define STCK_X_PIN A0
#define STCK_Y_PIN A1

ezButton butt(BTN_PIN);
NeoPixel neoPixel(16,4,NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x28,16,2);

Vector2 stickPos;


void setup()
{
	neoPixel.begin();
    neoPixel.clear();
    for(int pixel = 0; pixel < 16; pixel++){
        neoPixel.setPixelColor(pixel, neoPixel.ColorHSV(pixel*5461,255,255-pixel));
        neoPixel.show();
        delay(50);
    }
    for (int pixel = 0; pixel < 16; pixel++)
    {
        neoPixel.setPixelColor(pixel,0,0,0);
        neoPixel.show();
        delay(50);
    }
    Serial.begin(9600);
}

void loop()
{
    stickPos.x = analogRead(STCK_X_PIN)-512;
    stickPos.y = analogRead(STCK_Y_PIN)-511;

    int pixels = (stickPos.GetUnsignedAngle()*180/M_PI)/45;

    neoPixel.clear();
    if(stickPos.GetMagnitude() >= 5){
        neoPixel.setPixelColor(8, pixels, 255, 255, 255);
    }
    neoPixel.show();

    #pragma region Debug Printing
    String debugString = "Stick X: " + String(stickPos.x, DEC)
         + " Stick Y: " + String(stickPos.y, DEC) + " Stick Angle: " + String(stickPos.GetSignedAngle()*180/M_PI, DEC)
         + " Stick Unisgned Angle: " + String(stickPos.GetUnsignedAngle()*180/M_PI, DEC)
         + " Pixel: " + String(pixels, DEC);// + "Stick Y: " + stickY;
    Serial.println(debugString);
    #pragma endregion
}

