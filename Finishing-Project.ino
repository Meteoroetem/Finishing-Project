#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include "NeoPixel.h"
#include "Vector2.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

#define BTN_PIN 2
#define STCK_X_PIN A0
#define STCK_Y_PIN A1

NeoPixel neoPixel(16,4,NEO_GRB + NEO_KHZ800);
LiquidCrystal_I2C lcd(0x27,16,2);
Vector2 stickPos;

uint32_t colors[] = {neoPixel.Color(239, 71, 111), neoPixel.Color(75, 163, 195), neoPixel.Color(89, 60, 143), neoPixel.Color(249, 219, 189)};
String sentences[] = {"The Electronics Megama was established", "Vered joined the school", "The school was established", "Sisko became CEO"};


int selection;
bool blinkOn = true;
bool buttonDown = false;
bool buttonWasDown = false;
byte passInput[4];
byte currentDigit = 0;

void setup()
{
    pinMode(2, INPUT_PULLUP);
    lcd.init();
    ////lcd.begin(16,2);
    lcd.backlight();
    ////lcd.autoscroll();
    ////lcd.scrollDisplayLeft();

	neoPixel.begin();
    neoPixel.clear();
    neoPixel.setBrightness(10);

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
    for(int pixel = 0; pixel < 16; pixel++){
        neoPixel.setPixelColor(pixel, colors[pixel/4]);
        neoPixel.show();
        delay(50);
    }
    lcd.setCursor(1,0);
    lcd.print(sentences[0]);

    Serial.begin(9600);
}

void loop()
{
    if(currentDigit != 4){
        MainLoop();
    }
    else{
        if(passInput == new byte[4]{2, 1, 3, 0}){
            lcd.clear();
            lcd.home();
            lcd.print("Congrats!!");
            while(true){digitalWrite(13,HIGH);}
        }
        else{
            lcd.clear();
            lcd.home();
            lcd.print("Incorrect!!");
            currentDigit = 0;
            delay(1000);
            lcd.print(sentences[selection]);
        }
    }
}

void MainLoop()
{
    stickPos.x = analogRead(STCK_X_PIN)-512;
    stickPos.y = analogRead(STCK_Y_PIN)-511;
    int uAngle = stickPos.GetUnsignedAngle();
    double magnitude = stickPos.GetMagnitude();
    int pixels = (uAngle*180/M_PI)/(360/4) - floor((uAngle*180/M_PI)/(360/4))>= 0.5 ? floor((uAngle*180/M_PI)/(360/4)) + 1 : floor((uAngle*180/M_PI)/(360/4));

    buttonDown = digitalRead(BTN_PIN) == LOW;

    if(magnitude > 100){
        neoPixel.setPixelColor(4, selection, colors[selection]);
        selection = pixels;
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print(sentences[selection]);
        
    }

    neoPixel.setPixelColor(4, selection, blinkOn ? colors[selection] : 0);
    blinkOn = !blinkOn;

    lcd.scrollDisplayLeft();

    neoPixel.show();

    if(!buttonWasDown && buttonDown){
        Serial.println("Button pressed");
        passInput[currentDigit] = selection;
        currentDigit++;
    }

    buttonWasDown = digitalRead(BTN_PIN) == LOW;

    #pragma region Debug Printing
    String debugString = "Stick X: " + String(stickPos.x, DEC)
         + " Stick Y: " + String(stickPos.y, DEC) + " Stick Angle: " + String(stickPos.GetSignedAngle()*180/M_PI, DEC)
         + " Stick Unisgned Angle: " + String(uAngle*180/M_PI, DEC) + 
         " Magnitude: " + String(magnitude, DEC) + 
         " Pixels: " + String(pixels, DEC);// + "Stick Y: " + stickY;
    Serial.println(debugString);
    #pragma endregion

    delay(250);
}