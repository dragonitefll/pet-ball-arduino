#ifndef DCMotor_h
#define DCMotor_h

#include "Arduino.h"

class DCMotor {
  public:
    void attach(char forward, char reverse, char power);
    char forwardPin;
    char reversePin;
    char powerPin;
    boolean start(int power);
    void stop();
};

#endif
