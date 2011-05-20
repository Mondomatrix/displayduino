#include <MatrixNet.h>

MatrixNet myMatrix;

unsigned char i = 0;

void setup()
{
  myMatrix.begin();
}

void loop()
{
  //Slowly fills all the LEDs on board 0 with red
  //Uses board 128 as there is still a bug in the LEDMatrix firmware
  
  for(i=0;i<64;i++) {
    myMatrix.changeLED(128, i, 255, 0, 0);
    delay(500);
  }
  
  //Now slowly fills all the LEDs with green too
  for(i=0;i<64;i++) {
    myMatrix.changeLED(128, i, 255, 255, 0);
    delay(500);
  }

  //Now slowly fills all the LEDs with blue too
  for(i=0;i<64;i++) {
    myMatrix.changeLED(128, i, 255, 255, 255);
    delay(500);
  }  
  
  //Now slowly turns off all the LEDs
  for(i=0;i<64;i++) {
    myMatrix.changeLED(128, i, 0,0,0);
    delay(500);
  }  
}
