#include<Adafruit_NeoPixel.h>
class NeoPixel : public Adafruit_NeoPixel
{
    public:
        using Adafruit_NeoPixel::Adafruit_NeoPixel;
        using Adafruit_NeoPixel::setPixelColor;
        void setPixelColor(int segmentCnt, int n, uint8_t r, uint8_t g, uint8_t b);
        void setPixelColor(int segmentCnt, int segmentNum, uint32_t c);
};