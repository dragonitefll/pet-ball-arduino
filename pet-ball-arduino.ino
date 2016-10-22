#include <Servo.h>

#include "FastLED.h"
#include "dcmotor.h"

#define NUM_LEDS 10
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

DCMotor leftWheel;
DCMotor rightWheel;

int inputPin = 2; // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  leftWheel.attach(2, 3, 9);
  rightWheel.attach(4, 5, 10);

  pinMode(DATA_PIN, OUTPUT); // declare LED as output
  pinMode(inputPin, INPUT); // declare sensor as input

  Serial.begin(9600);

}

void loop() {
  //Serial.println("Enter loop");
  // put your main code here, to run repeatedly:
  val = digitalRead(inputPin); // read input value

  if (val == HIGH) { // check if the input is HIGH
    //Serial.println("HIGH");
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      for (int dot = 0; dot < NUM_LEDS; dot++) {
        leds[dot] = CRGB(255, 0, 255);
        FastLED.show();
        // clear this led for the next time around the loop
        leds[dot] = CRGB::Black;
        delay(20);
      }
      pirState = HIGH;
    }
  } else {
      //Serial.println("LOW");
      if (pirState == HIGH){
      Serial.println("Motion ended!");
      pirState = LOW;
      }
    }
    //Serial.println("exit loop");
} 
