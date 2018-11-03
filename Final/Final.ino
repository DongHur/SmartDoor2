#include <Servo.h>
#include <Wire.h>
#include "Adafruit_MPR121.h"

Servo myservo1;
Servo myservo2;


#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();


uint16_t lasttouched = 0;
uint16_t currtouched = 0;

bool val0_1 = false; bool val0_2 = false;
bool val1_1 = false; bool val1_2 = false;
bool val2_1 = false; bool val2_2 = false;
bool val3_1 = false; bool val3_2 = false;
bool val4_1 = false; bool val4_2 = false;


int RealPassword[] = {1,2,3,4,3};
int Password[] = {0,0,0,0,0};

int a = 0;

void setup() 
{
  Serial.begin(9600);

  while (!Serial) {delay(10);}
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  
  if (!cap.begin(0x5A)) 
  {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  
}

void loop() 
{
   currtouched = cap.touched(); // Get the currently touched pads

    delay(100);   
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if ((currtouched & _BV(0)) && !(lasttouched & _BV(0)) ) 
      {
        val0_1 = true;
      }
  
    if (!(currtouched & _BV(0)) && (lasttouched & _BV(0)) ) 
      {
       val0_2 = true;
      }
  
    if(val0_1 == true && val0_2 == true)
      {
        Serial.println( "0 Pressed");
        val0_1 = false;
        val0_2 = false;

    for (int j=0;j<5;j++)
      { 
        Password[j] = 0;
        }

        a = 0;  

        Serial.print(Password[0]);Serial.print(Password[1]);Serial.print(Password[2]);Serial.print(Password[3]);Serial.print(Password[4]); //allows you to see the password
        Serial.println();
        
      }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

    if ((currtouched & _BV(1)) && !(lasttouched & _BV(1)) ) 
      {
        val1_1 = true;
      }
  
    if (!(currtouched & _BV(1)) && (lasttouched & _BV(1)) ) 
      {
       val1_2 = true;
      }
  
    if(val1_1 == true && val1_2 == true)
      {
        Serial.println( "1 Pressed");
        val1_1 = false;
        val1_2 = false;
        
        Password[a] = 1; 

        a = a+1;  

        Serial.print(Password[0]);Serial.print(Password[1]);Serial.print(Password[2]);Serial.print(Password[3]);Serial.print(Password[4]); //allows you to see the password
        Serial.println();
      }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


     if ((currtouched & _BV(2)) && !(lasttouched & _BV(2)) ) 
      {
        val2_1 = true;
      }
  
    if (!(currtouched & _BV(2)) && (lasttouched & _BV(2)) ) 
      {
       val2_2 = true;
      }
  
    if(val2_1 == true && val2_2 == true)
      {
        Serial.println( "2 Pressed");
        val2_1 = false;
        val2_2 = false;

        Password[a] = 2; 

        a = a+1;  

        Serial.print(Password[0]);Serial.print(Password[1]);Serial.print(Password[2]);Serial.print(Password[3]);Serial.print(Password[4]); //allows you to see the password
        Serial.println();
        
      }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

    if ((currtouched & _BV(3)) && !(lasttouched & _BV(3)) ) 
      {
        val3_1 = true;
      }
  
    if (!(currtouched & _BV(3)) && (lasttouched & _BV(3)) ) 
      {
       val3_2 = true;
      }
  
    if(val3_1 == true && val3_2 == true)
      {
        Serial.println( "3 Pressed");
        val3_1 = false;
        val3_2 = false;
        
        Password[a] = 3; 

        a = a+1;  

        Serial.print(Password[0]);Serial.print(Password[1]);Serial.print(Password[2]);Serial.print(Password[3]);Serial.print(Password[4]); //allows you to see the password
        Serial.println();
      }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  

    if ((currtouched & _BV(4)) && !(lasttouched & _BV(4)) ) 
      {
        val4_1 = true;
      }
  
    if (!(currtouched & _BV(4)) && (lasttouched & _BV(4)) ) 
      {
       val4_2 = true;
      }
  
    if(val4_1 == true && val4_2 == true)
      {
        Serial.println( "4 Pressed");
        val4_1 = false;
        val4_2 = false;
        
        Password[a] = 4; 

        a = a+1;  

        Serial.print(Password[0]);Serial.print(Password[1]);Serial.print(Password[2]);Serial.print(Password[3]);Serial.print(Password[4]); //allows you to see the password
        Serial.println();
      }

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  





    if (array_cmp(RealPassword, Password) == true){
      Serial.print("Got em");
      
      myservo1.attach(6);
      myservo2.attach(5);
      
      myservo1.write(0);
      myservo2.write(0);
      
      delay(7000
      );
      
      myservo1.detach();
      myservo2.detach();
      
      Serial.println();
      for (int j=0;j<5;j++)
      { 
        Password[j] = 0;
        }
      Serial.print(Password[0]);Serial.print(Password[1]);Serial.print(Password[2]);Serial.print(Password[3]);Serial.print(Password[4]); //allows you to see the password
        Serial.println();  
      
     }

     // 

  
  lasttouched = currtouched; // reset our state


  return;
}

boolean array_cmp(int *a, int *b){
     int n;

     // test each element to be the same. if not, return false
     for (n=0;n<5;n++) if (a[n]!=b[n]) return false;

     //ok, if we have not returned yet, they are equal :)
     return true;
}

/*
 * for (uint8_t i=0; i<12; i++) 
  {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) 
    {
    //  Serial.print(i); Serial.println(" touched");
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) 
    {
    //  Serial.print(i); Serial.println(" released");
    }

  }
 */
