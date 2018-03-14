#include "FastLED.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

#define NUM_LEDS 1
#define DATA_PIN 3

#define FSR1_PIN 0
#define FSR2_PIN 1
#define FSR3_PIN 2

CRGB leds[NUM_LEDS];

int red = 0;
int green = 0;
int blue = 0;
int freq = 0;

const unsigned long deltaTime = 1000UL;
static unsigned long lastSampleTime = 0;

void setup()
{
  pinMode(FSR1_PIN, INPUT);
  pinMode(FSR2_PIN, INPUT);
  pinMode(FSR3_PIN, INPUT);
  Serial.begin(9600);
  mySerial.begin(38400);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  lastSampleTime = millis();
}

void loop()
{
  unsigned long now = millis();
  if (now - lastSampleTime >= deltaTime)
  {
    int var1 = analogRead(FSR1_PIN);
    int var2 = analogRead(FSR2_PIN);
    int var3 = analogRead(FSR3_PIN);
    
    var1 = map(var1,0,1023,0,255);
    var2 = map(var2,0,1023,0,255);
    var3 = map(var3,0,1023,0,255);
    
    leds[0].red = var1;
    leds[0].green = var2;
    leds[0].blue = var3;
    FastLED.show();
     
    mySerial.print(var1);
    mySerial.print(";");
    mySerial.print(var2);
    mySerial.print(";");
    mySerial.println(var3);
    lastSampleTime = millis();
  }

  if (mySerial.available()){
    red = mySerial.parseInt();
    green = mySerial.parseInt();
    blue = mySerial.parseInt();
    freq = mySerial.parseInt();
    for(int i=0;i<10;i++){
      leds[0].red = red;
      leds[0].green = green;
      leds[0].blue = blue;
      FastLED.show();
      delay(freq);
      leds[0].red = 0;
      leds[0].green = 0;
      leds[0].blue = 0;
      FastLED.show();
      delay(freq);
    }
  }
}
