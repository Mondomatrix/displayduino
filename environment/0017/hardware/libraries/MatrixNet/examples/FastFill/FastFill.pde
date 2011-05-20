#include <MatrixNet.h>

MatrixNet myMatrix;

unsigned char i = 0;
unsigned char RedBrightness[64];
unsigned char BlueBrightness[64];
unsigned char GreenBrightness[64];

void setup()
{
  myMatrix.begin();
}

void loop()
{
  //Fills all the LEDs on board 0 with red
  //Uses board 0
  
  for(i=0;i<64;i++) {
    RedBrightness[i] = 255;
    GreenBrightness[i] = 0;
    BlueBrightness[i] = 0;
  }

  myMatrix.changeLEDBoard(0, RedBrightness, GreenBrightness, BlueBrightness);
  delay(2000);

  //Now fills all the LEDs with green too
  for(i=0;i<64;i++) {
    RedBrightness[i] = 255;
    GreenBrightness[i] = 255;
    BlueBrightness[i] = 0;
  }

  myMatrix.changeLEDBoard(0, RedBrightness, GreenBrightness, BlueBrightness);
  delay(2000);

  //Now fills all the LEDs with blue too
  for(i=0;i<64;i++) {
    RedBrightness[i] = 255;
    GreenBrightness[i] = 255;
    BlueBrightness[i] = 255;
  }

  myMatrix.changeLEDBoard(0, RedBrightness, GreenBrightness, BlueBrightness);
  delay(2000);
  
  //Now turns off all the LEDs
  for(i=0;i<64;i++) {
    RedBrightness[i] = 0;
    GreenBrightness[i] = 0;
    BlueBrightness[i] = 0;
  }

  myMatrix.changeLEDBoard(0, RedBrightness, GreenBrightness, BlueBrightness);
  delay(2000);
}
