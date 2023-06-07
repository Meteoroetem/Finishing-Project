#include "NeoPixel.h"

void NeoPixel::setPixelColor(int segmentCnt, int segmentNum, uint8_t r, uint8_t g, uint8_t b){
    int segmentSize = numPixels()/segmentCnt;
    for (int pixel = segmentSize * segmentNum; pixel < segmentSize * (segmentNum+1); pixel++)
    {
        Adafruit_NeoPixel::setPixelColor(pixel, r, g, b);
    }
}
void NeoPixel::setPixelColor(int segmentCnt, int segmentNum, uint32_t c){
    int segmentSize = numPixels()/segmentCnt;
    for (int pixel = segmentSize * segmentNum; pixel < segmentSize * (segmentNum+1); pixel++)
    {
        Adafruit_NeoPixel::setPixelColor(pixel, c);
    }
}