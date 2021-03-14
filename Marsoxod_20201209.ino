/*
  Angular positioner
  break time
  both direcrions
  

*/

// #define BREAKRATIO 8



unsigned int OldAB;
unsigned int IntTimer, BreakTimer = 1;

byte GrayCode[] = {255, 56, 40, 55, 24, 255, 39, 52, 8, 57, 255, 255, 23, 255, 36, 13, 120, 255, 41, 54, 255, 255, 255, 53, 7, 255, 255, 255, 20, 19, 125, 18, 104, 105, 255, 255, 25, 106, 38, 255, 255, 58, 255, 255, 255, 255, 37, 14, 119, 118, 255, 255, 255, 107, 255, 255, 4, 255, 3, 255, 109, 108, 2, 1, 88, 255, 89, 255, 255, 255, 255, 51, 9, 10, 90, 255, 22, 11, 255, 12, 255, 255, 42, 43, 255, 255, 255, 255, 255, 255, 255, 255, 21, 255, 126, 127, 103, 255, 102, 255, 255, 255, 255, 255, 255, 255, 91, 255, 255, 255, 255, 255, 116, 117, 255, 255, 115, 255, 255, 255, 93, 94, 92, 255, 114, 95, 113, 0, 72, 71, 255, 68, 73, 255, 255, 29, 255, 70, 255, 69, 255, 255, 35, 34, 121, 255, 122, 255, 74, 255, 255, 30, 6, 255, 123, 255, 255, 255, 124, 17, 255, 255, 255, 67, 26, 255, 27, 28, 255, 59, 255, 255, 255, 255, 255, 15, 255, 255, 255, 255, 255, 255, 255, 255, 5, 255, 255, 255, 110, 255, 111, 16, 87, 84, 255, 45, 86, 85, 255, 50, 255, 255, 255, 46, 255, 255, 255, 33, 255, 83, 255, 44, 75, 255, 255, 31, 255, 255, 255, 255, 255, 255, 255, 32, 100, 61, 101, 66, 255, 62, 255, 49, 99, 60, 255, 47, 255, 255, 255, 48, 77, 82, 78, 65, 76, 63, 255, 64, 98, 81, 79, 80, 97, 96, 112, 255};
int A_Max = 1000, A_Min = 150, A_Set[6] [4] = {170, 575, 1000, 575}, A_Sigma[] = {10,10,10,10,10,10}, A_7;
byte Quadrant[6],iFoot,AInput[]={21,20,19,18,17,20};
byte AnalogPinz[]={5,5,6,9,10,9},DigiPinz[]={7,4,7,8,12,7};
 
byte Ciel[6]={1,1,1,1,1,1}, State, Speed = 255, BreakTime = 20, LoopTact = 3, Reverse, BreakRatio = 8;
// the setup routine runs once when you press reset:
void setup() {

  pinMode (A0, INPUT_PULLUP);
  pinMode (A1, INPUT_PULLUP);
  pinMode (A2, INPUT_PULLUP);
  pinMode (A3, INPUT_PULLUP);
  pinMode (A4, INPUT_PULLUP);
  pinMode (A5, INPUT_PULLUP);
  pinMode (12, INPUT_PULLUP);
  pinMode (11, INPUT_PULLUP);

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);





  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);

  Serial.print("AnglePositioner14");


  Ciel[iFoot] = 1;
}

// the loop routine runs over and over again forever:
void loop() {



  
  A_7 = analogRead(AInput[iFoot]);
  if (Ciel[iFoot] != 0)
    switch (Ciel[iFoot])
    {



      case 1:  // [1]
           if(0)
            {
              Serial.print("case 1 ");
             
            Serial.print(A_7);
            Serial.print("  ");
            Serial.println(A_Set[iFoot][1]);

    }
            
        if (Quadrant[iFoot] == 1  || Quadrant[iFoot] == 0 )
        {

          if (A_7 < A_Set[iFoot][1] - A_Sigma[iFoot])
          {
            analogWrite(AnalogPinz[iFoot], Speed);
            digitalWrite(DigiPinz[iFoot], LOW);
            BreakTimer = 0;
          }

          else
          {
            //IntTimer,BreakTimer

            if ((BreakTimer == 0) && (BreakRatio < 255 ))
            {

              BreakTimer = IntTimer;

              analogWrite(AnalogPinz[iFoot], 255 - Speed);
              digitalWrite(DigiPinz[iFoot], HIGH);



              //  Serial.print("If");
              // Serial.print (IntTimer);
            }
            else if ((IntTimer - BreakTimer >   (Speed / BreakRatio)      ) || (BreakRatio == 255 ))
            {
              //    Serial.print (" more ");
            //  Serial.print (Speed / BreakRatio);
             // Serial.print (" ");
             // Serial.println (IntTimer - BreakTimer);
              analogWrite(AnalogPinz[iFoot], 0);
              digitalWrite(DigiPinz[iFoot], LOW);

              Ciel[iFoot] = 0;
              Quadrant[iFoot] = 1;


            }
          }


        }

        else // case Quadrant[iFoot] == 2,3
        {
          if (A_7 > A_Set[iFoot][0] + A_Sigma[iFoot])
          {
            analogWrite(AnalogPinz[iFoot], Speed);
            digitalWrite(DigiPinz[iFoot], LOW);
          }
          else
          {
            analogWrite(AnalogPinz[iFoot], 0);
            digitalWrite(DigiPinz[iFoot], LOW);

            Quadrant[iFoot] = 0;
          }

        }

        break;



      case 2:
        if (A_7 < A_Set[iFoot][2] - A_Sigma[iFoot])
        {
          analogWrite(AnalogPinz[iFoot], Speed);
          digitalWrite(DigiPinz[iFoot], LOW);
          BreakTimer = 0;
        }
        else
        {
          if ((BreakTimer == 0) && (BreakRatio < 255 ))
          {
            BreakTimer = IntTimer;
            analogWrite(AnalogPinz[iFoot], 255 - Speed);
            digitalWrite(DigiPinz[iFoot], HIGH);
          }
          else if ((IntTimer - BreakTimer >   (Speed / BreakRatio)      ) || (BreakRatio == 255 ))
          {
            analogWrite(AnalogPinz[iFoot], 0);
            digitalWrite(DigiPinz[iFoot], LOW);
            Ciel[iFoot] = 0;
            Quadrant[iFoot] = 2;
          }
        }

        break;



      case 3:

        if (Quadrant[iFoot] == 2  || Quadrant[iFoot] == 3 )
        {
          if (A_7 > A_Set[iFoot][1] + A_Sigma[iFoot])
          {
            analogWrite(AnalogPinz[iFoot], Speed);
            digitalWrite(DigiPinz[iFoot], LOW);
            BreakTimer = 0;
          }
          else
          {
            if ((BreakTimer == 0) && (BreakRatio < 255 ))
            {
              BreakTimer = IntTimer;
              analogWrite(AnalogPinz[iFoot], 255 - Speed);
              digitalWrite(DigiPinz[iFoot], HIGH);
            }
            else if ((IntTimer - BreakTimer >   (Speed / BreakRatio)      ) || (BreakRatio == 255 ))
            {
              analogWrite(AnalogPinz[iFoot], 0);
              digitalWrite(DigiPinz[iFoot], LOW);
              Ciel[iFoot] = 0;
              Quadrant[iFoot] = 3;
            }
          }

        }

        else // case Quadrant[iFoot] == 0,1
        {
          if (A_7 < A_Set[iFoot][2] - A_Sigma[iFoot])
          {
            analogWrite(AnalogPinz[iFoot], Speed);
            digitalWrite(DigiPinz[iFoot], LOW);
          }
          else
          {
            analogWrite(AnalogPinz[iFoot], 0);
            digitalWrite(DigiPinz[iFoot], LOW);

            Quadrant[iFoot] = 2;
          }

        }

        break;



      case 4:
        if (A_7 > A_Set[iFoot][0] + A_Sigma[iFoot])
        {
          analogWrite(AnalogPinz[iFoot], Speed);
          digitalWrite(DigiPinz[iFoot], LOW);
          BreakTimer=0;
        }
        else
           {
            if ((BreakTimer == 0) && (BreakRatio < 255 ))
            {
              BreakTimer = IntTimer;
              analogWrite(AnalogPinz[iFoot], 255 - Speed);
              digitalWrite(DigiPinz[iFoot], HIGH);
            }
            else if ((IntTimer - BreakTimer >   (Speed / BreakRatio)      ) || (BreakRatio == 255 ))
            {
              analogWrite(AnalogPinz[iFoot], 0);
              digitalWrite(DigiPinz[iFoot], LOW);
              Ciel[iFoot] = 0;
              Quadrant[iFoot] = 0;
            }
          }
        break;


//ccw

    case 5:  // [1]

        if (Quadrant[iFoot] == 1  || Quadrant[iFoot] == 2 )
        {

          if (A_7 > A_Set[iFoot][1] + A_Sigma[iFoot])
          {
            analogWrite(AnalogPinz[iFoot], 255 - Speed);
            digitalWrite(DigiPinz[iFoot], HIGH);
            BreakTimer = 0;
          }

          else
          {
            //IntTimer,BreakTimer

            if ((BreakTimer == 0) && (BreakRatio < 255 ))
            {

              BreakTimer = IntTimer;

              analogWrite(AnalogPinz[iFoot],  Speed);
              digitalWrite(DigiPinz[iFoot], LOW);



              //  Serial.print("If");
              // Serial.print (IntTimer);
            }
            else if ((IntTimer - BreakTimer >   (Speed / BreakRatio)      ) || (BreakRatio == 255 ))
            {
              //    Serial.print (" more ");
           //   Serial.print (Speed / BreakRatio);
            //  Serial.print (" ");
            //  Serial.println (IntTimer - BreakTimer);
          analogWrite(AnalogPinz[iFoot], 0);
              digitalWrite(DigiPinz[iFoot], LOW);

              Ciel[iFoot] = 0;
              Quadrant[iFoot] = 1;


            }
          }


        }

        else // case Quadrant[iFoot] == 0,3
        {
          if (A_7 < A_Set[iFoot][2] - A_Sigma[iFoot])
          {
            analogWrite(AnalogPinz[iFoot], 255-Speed);
            digitalWrite(DigiPinz[iFoot], HIGH);
          }
          else
          {
            analogWrite(AnalogPinz[iFoot], 0);
            digitalWrite(DigiPinz[iFoot], LOW);

            Quadrant[iFoot] = 2;
          }

        }

        break;



      case 6:
        if (A_7 < A_Set[iFoot][2] - A_Sigma[iFoot])
        {
          analogWrite(AnalogPinz[iFoot], 255-Speed);
          digitalWrite(DigiPinz[iFoot], HIGH);
          BreakTimer = 0;
        }
        else
        {
          if ((BreakTimer == 0) && (BreakRatio < 255 ))
          {
            BreakTimer = IntTimer;
            analogWrite(AnalogPinz[iFoot],  Speed);
            digitalWrite(DigiPinz[iFoot], LOW);
          }
          else if ((IntTimer - BreakTimer >   (Speed / BreakRatio)      ) || (BreakRatio == 255 ))
          {
            analogWrite(AnalogPinz[iFoot], 0);
            digitalWrite(DigiPinz[iFoot], LOW);
            Ciel[iFoot] = 0;
            Quadrant[iFoot] = 2;
          }
        }

        break;



      case 7:

        if (Quadrant[iFoot] == 0  || Quadrant[iFoot] == 3 )
        {
          if (A_7 < A_Set[iFoot][3] + A_Sigma[iFoot])
          {
            analogWrite(AnalogPinz[iFoot], 255-Speed);
            digitalWrite(DigiPinz[iFoot], HIGH);
            BreakTimer = 0;
          }
          else
          {
            if ((BreakTimer == 0) && (BreakRatio < 255 ))
            {
              BreakTimer = IntTimer;
              analogWrite(AnalogPinz[iFoot],  Speed);
              digitalWrite(DigiPinz[iFoot], LOW);
            }
            else if ((IntTimer - BreakTimer >   (Speed / BreakRatio)      ) || (BreakRatio == 255 ))
            {
              analogWrite(AnalogPinz[iFoot], 0);
              digitalWrite(DigiPinz[iFoot], LOW);
              Ciel[iFoot] = 0;
              Quadrant[iFoot] = 3;
            }
          }

        }

        else // case Quadrant[iFoot] == 2,1
        {
          if (A_7 > A_Set[iFoot][0] + A_Sigma[iFoot])
          {
            analogWrite(AnalogPinz[iFoot], 255-Speed);
            digitalWrite(DigiPinz[iFoot], HIGH);
          }
          else
          {
            analogWrite(AnalogPinz[iFoot], 0);
            digitalWrite(DigiPinz[iFoot], LOW);

            Quadrant[iFoot] = 0;
          }

        }

        break;



      case 8:
        if (A_7 > A_Set[iFoot][0] + A_Sigma[iFoot])
        {
          analogWrite(AnalogPinz[iFoot], 255-Speed);
          digitalWrite(DigiPinz[iFoot], HIGH);
          BreakTimer=0;
       //   Serial.print(" if 0\t");
        }
        else
           {
            if ((BreakTimer == 0) && (BreakRatio < 255 ))
            {
              BreakTimer = IntTimer;
              analogWrite(AnalogPinz[iFoot],  Speed);
              digitalWrite(DigiPinz[iFoot], LOW);
            //  Serial.print(" if 1\t");
            }
            else if ((IntTimer - BreakTimer >   (Speed / BreakRatio)      ) || (BreakRatio == 255 ))
            {
              analogWrite(AnalogPinz[iFoot], 0);
              digitalWrite(DigiPinz[iFoot], LOW);
             // Serial.print(" if 2\t");
              Ciel[iFoot] = 0;
              Quadrant[iFoot] = 0;
            }
          }
        break;







      default:

        
        break;









    }

/*
    // here we swithc the foots
  if( ++iFoot>5)
  iFoot=0;

 */
  // Encoder 
  byte Ainp = PINC & 0x3F; // +(PINB&0x30)<<2;
  byte Binp = (PINB & 0x18) << 3;

  //  Serial.print(Binp);
  //  Serial.print("            ");
  //  Serial.println(Ainp);

  // if(Ainp+Binp  !=  OldAB)
  {

    if (0)
    {
      Serial.print("Qd=");
      Serial.print(Quadrant[iFoot]);

      Serial.print(" Sp=");
      Serial.print(Speed);
      Serial.print (" ");
    }
    if (1) {
      Serial.print(Ciel[iFoot]);
      Serial.print("\t");
      Serial.print(A_7);
      Serial.print(" \t   ");

      Serial.println(GrayCode [Ainp + Binp]);
    }
    // delay(5);        // delay in between reads for stability
  }
  // OldAB=Ainp+Binp;

  delay(LoopTact);
  IntTimer += LoopTact;

}




void serialEvent() {
  if (Serial.available())
  {
    byte CmndS = Serial.read();
    switch(CmndS)
    {

case 'q':
for(byte  iSE =0;iSE<6;iSE++)
Ciel[iSE]=2;
break;

case 'w':
for(byte  iSE =0;iSE<6;iSE++)
Ciel[iSE]=3;
break;

case 's':
for(byte  iSE =0;iSE<6;iSE++)
Ciel[iSE]=4;
break;

case 'a':
for(byte  iSE =0;iSE<6;iSE++)
Ciel[iSE]=1;
break;



//

case 'e':
for(byte  iSE =0;iSE<6;iSE++)
Ciel[iSE]=6;
break;

case 'r':
for(byte  iSE =0;iSE<6;iSE++)
Ciel[iSE]=7;
break;

case 'f':
for(byte  iSE =0;iSE<6;iSE++)
Ciel[iSE]=8;
break;

case 'd':
for(byte  iSE =0;iSE<6;iSE++)
Ciel[iSE]=5;
break;
default:
if (CmndS > 47  && CmndS < 57)
        {
          Speed = (CmndS - 47) * 28;
          CmndS = 0;
        }
        else if (CmndS == 57)
        {
          Speed = 255;
         // CmndS = 0;
        }
      
   
break;

  }

}
}

