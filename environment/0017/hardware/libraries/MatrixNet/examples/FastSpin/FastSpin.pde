#include <MatrixNet.h>

MatrixNet myMatrix;

unsigned char i = 0;
unsigned char PosArray[64];

void setup()
{
  myMatrix.begin();
}

void loop()
{
  //Rotates all servos to one near-extreme
  //Uses board 0
  for(i=0;i<64;i++) {
    PosArray[i] = 200;
  }

  myMatrix.changeServoBoard(0, PosArray);
  delay(1000);
  
  //Now Rotates all servos to the other near-extreme
  for(i=0;i<64;i++) {
    PosArray[i] = 20;
  }
  
  myMatrix.changeServoBoard(0, PosArray);
  delay(1000);
}
