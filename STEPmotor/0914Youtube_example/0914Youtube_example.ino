#include <SoftwareSerial.h>
#include <DMXSerial.h>


#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 200

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, A0, A1, A2, A3);

int DMXAddress = 0;

char sAddr[] = "00000000";

void setup() {
  // put your setup code here, to run once:
  DMXSerial.init(DMXProbe);

  DMXSerial.maxChannel(256); 

  //get address

/*
Serial.begin(9600);
while( 1 )
{
sprintf( sAddr, "00000000" );
*/
pinMode(5,INPUT_PULLUP);
pinMode(6,INPUT_PULLUP);
pinMode(7,INPUT_PULLUP);
pinMode(8,INPUT_PULLUP);
pinMode(9,INPUT_PULLUP);
pinMode(10,INPUT_PULLUP);
pinMode(11,INPUT_PULLUP);
pinMode(12,INPUT_PULLUP);

delay(100);

    for( int i = 0; i < 8; i++ )
      if( digitalRead(5+i) == LOW )
        sAddr[i] = '1'; 
        
pinMode(5,INPUT);
pinMode(6,INPUT);
pinMode(7,INPUT);
pinMode(8,INPUT);
pinMode(9,INPUT);
pinMode(10,INPUT);
pinMode(11,INPUT);
pinMode(12,INPUT);

 DMXAddress = strtol(sAddr, NULL, 2);
/*

Serial.println( sAddr );
 

Serial.println( DMXAddress );

}
*/

   stepper.setSpeed(10);
   
}

int i = 0;
int MotorSpeed = 0;


void loop() {
  // put your main code here, to run repeatedly:

  if ( DMXSerial.receive() ) 
  {
      if( MotorSpeed > 0 )
          stepper.step( MotorSpeed >> 1 );
      else if( MotorSpeed < 0 )
          stepper.step( 0 - ( abs(MotorSpeed) >> 1 ) );
  
      i = DMXSerial.read( DMXAddress );
      if( i != 0 ) // 0 is considered "null"
      {
        if( i < 100 )
          MotorSpeed = 100 - i;
        else if( i > 99 && i < 156 )
          MotorSpeed = 0;
        else if( i > 155 )
          MotorSpeed = ( 156 - i );

        if(MotorSpeed != 0 )
          stepper.setSpeed( abs(MotorSpeed) * 1.2 );
       else
        {
          digitalWrite(A0,LOW);
          digitalWrite(A1,LOW);
          digitalWrite(A2,LOW);
          digitalWrite(A3,LOW);
        }
      }

      
        if( MotorSpeed > 0 )
          stepper.step( MotorSpeed >> 1 );
        
        if( MotorSpeed < 0 )
          stepper.step( 0 - ( abs(MotorSpeed) >> 1 ) );

    }
   else
   {
      
        if( MotorSpeed > 0 )
          stepper.step( MotorSpeed );
        
        if( MotorSpeed < 0 )
          stepper.step( MotorSpeed );

  
  }

  
}