#include <MatrixNet.h>

MatrixNet myMatrix;

unsigned char i = 0;

void setup()
{
  myMatrix.begin();
}

void loop()
{
  //Slowly rotates all servos to one near-extreme
  //Uses board 0
  for(i=0;i<64;i++) {
    myMatrix.changeServo(0, i, 200);
    delay(500);
  }
  
  //Now slowly rotates all servos to the other near-extreme
  for(i=0;i<64;i++) {
    myMatrix.changeServo(0, i, 25);
    delay(500);
  }
}
