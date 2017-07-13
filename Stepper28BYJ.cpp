#include "Stepper28BYJ.h"

#define VERBOSE 1

#if (VERBOSE == 1)
#define SERIALOUT(x) Serial.print(x);
#else
#define SERIALOUT(x) ""
#endif

Stepper28BYJ::Stepper28BYJ( Stepper28BYJ::STEPMODE mode, int pin_in1, int pin_in2, int pin_in3, int pin_in4) {
   _mode = mode ;
   _pin_in1 = pin_in1;
   _pin_in2 = pin_in2;
   _pin_in3 = pin_in3;
   _pin_in4 = pin_in4;

   pinMode( _pin_in1, OUTPUT);
   pinMode( _pin_in2, OUTPUT);
   pinMode( _pin_in3, OUTPUT);
   pinMode( _pin_in4, OUTPUT);

   // ensure motor is disengaged
   // reset sequence number
   setOutput(9);
   _sequenceNumber = 0;
}

void Stepper28BYJ::step( int count ) {
   SERIALOUT(F("Entry count ="));
   SERIALOUT(count);
   SERIALOUT(F("Entry sequenceNumber ="));
   SERIALOUT(_sequenceNumber);

   if ( count > 0 ) {
      for ( int i=0; i < 8 ; i++ )
      {
         setOutput(_sequenceNumber);
         if ( _sequenceNumber == 0) {
            _sequenceNumber = 7 ;
         }
         _sequenceNumber--;
      }
      count--;
   }
   else if ( count < 0 ) {
      for ( int i=8; i > 0 ; i-- )
      {
         setOutput(_sequenceNumber);
         if ( _sequenceNumber == 7) {
            _sequenceNumber = 0 ;
         }
         _sequenceNumber++;
      }
      count++;
   }
   SERIALOUT(F("Exit count ="));
   SERIALOUT(count);
   SERIALOUT(F("Exit sequenceNumber ="));
   SERIALOUT(_sequenceNumber);
}

void Stepper28BYJ::setOutput( int stepNumber ) {
   digitalWrite( _pin_in1, bitRead(_stepping[stepNumber], 0));
   digitalWrite( _pin_in2, bitRead(_stepping[stepNumber], 1));
   digitalWrite( _pin_in3, bitRead(_stepping[stepNumber], 2));
   digitalWrite( _pin_in4, bitRead(_stepping[stepNumber], 3));
}

void Stepper28BYJ::setSpeed( int speed ) {
   _motorSpeed = speed;
}

void Stepper28BYJ::disengage( ) {
   setOutput(9);
   _sequenceNumber = 0;
}
