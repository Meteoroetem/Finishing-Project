#include <legacy.h>
#include <NoiascaLiquidCrystal.h>

#include<Wire.h>
#include<ezButton.h>
#include<lcd_wire.h>
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
LiquidCrystal_Wire lcd(0x28,16,2);

Vector2 stickPos;

uint32_t colors[] = {neoPixel.Color(239, 71, 111), neoPixel.Color(75, 163, 195), neoPixel.Color(89, 60, 143), neoPixel.Color(249, 219, 189)};

void setup()
{
    lcd.print("שלום עולם");
	neoPixel.begin();
    neoPixel.clear();
    for(int pixel = 0; pixel < 16; pixel++){
        neoPixel.setPixelColor(pixel, neoPixel.ColorHSV(pixel*4096,255,255-pixel));
        neoPixel.show();
        delay(50);
    }
    for (int pixel = 0; pixel < 16; pixel++)
    {
        neoPixel.setPixelColor(pixel,0,0,0);
        neoPixel.show();
        delay(50);
    }
    neoPixel.setBrightness(30);
    Serial.begin(9600);
}

void loop()
{
    stickPos.x = analogRead(STCK_X_PIN)-512;
    stickPos.y = analogRead(STCK_Y_PIN)-511;
    int uAngle = stickPos.GetUnsignedAngle();
    double magnitude = stickPos.GetMagnitude();
    int pixels = (uAngle*180/M_PI)/(360/4) - floor((uAngle*180/M_PI)/(360/4))>= 0.5 ? floor((uAngle*180/M_PI)/(360/4)) + 1 : floor((uAngle*180/M_PI)/(360/4));

    neoPixel.clear();
    if(stickPos.GetMagnitude() > 5){
        neoPixel.setPixelColor(4, pixels, colors[pixels]);
    }
    neoPixel.show();

    #pragma region Debug Printing
    String debugString = "Stick X: " + String(stickPos.x, DEC)
         + " Stick Y: " + String(stickPos.y, DEC) + " Stick Angle: " + String(stickPos.GetSignedAngle()*180/M_PI, DEC)
         + " Stick Unisgned Angle: " + String(uAngle*180/M_PI, DEC) + 
         " Magnitude: " + String(magnitude, DEC) + 
         " Pixels: " + String(pixels, DEC);// + "Stick Y: " + stickY;
    Serial.println(debugString);
    #pragma endregion

}

