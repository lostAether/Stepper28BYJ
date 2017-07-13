/* Header file for Step Moter 28BYJ-48 5V DC */

#ifndef STEP_MOTOR_28BYJ_48
#define STEP_MOTOR_28BYJ_48

#ifndef Arduino_h
#include "Arduino.h"
#endif


class Stepper28BYJ {
   public:
      enum STEPMODE { HALFSTEP=4, FULLSTEP=8 };

      Stepper28BYJ( Stepper28BYJ::STEPMODE mode, int pin_in1, int pin_in2, int pin_in3, int pin_in4);
      void step(int steps);
      void setSpeed(int speed);
      void disengage();

   private:
      void setOutput(int stepNumber);

       // steps 0-7 are the half steps for the motor
       // step 9 is the disengaging of the motor
      int _stepping[9] = {B1000, B1100, B0100, B0110, B0010, B0011, B00001, B1001, B0000};
      int _motorSpeed = 0;
      int _countPerRevolution = 512;
      STEPMODE _mode = STEPMODE::HALFSTEP;
      int _pin_in1 = 2;
      int _pin_in2 = 3;
      int _pin_in3 = 4;
      int _pin_in4 = 5;
      int _sequenceNumber = 0;
};


#endif
