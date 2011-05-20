#include <MatrixNet.h>

MatrixNet myMatrix;

unsigned char dataByte;
unsigned char i = 0;

#define STATE_WAITING 0
#define STATE_ADDRESS 1
#define STATE_ADDRESS_LENGTH 2
#define STATE_DATA 3
#define STATE_DATA_LENGTH 4

unsigned char CurrentState = STATE_WAITING;

unsigned char AddressLength = 0;
unsigned char DataLength = 0;
unsigned char AddressBuffer[256];
unsigned char DataBuffer[256];

void setup()
{
  Serial.begin(115200);
  myMatrix.begin();
}

void loop()
{
  while(1) {
    if(Serial.available())
    {
      if(CurrentState == STATE_WAITING)
      {
        dataByte = Serial.read();
        if(dataByte == 'A')
        {
          CurrentState = STATE_ADDRESS;
        } 
        else if(dataByte == 'D') {
          CurrentState = STATE_DATA;
        }
      } 
      else if(CurrentState == STATE_ADDRESS) {
        AddressLength = Serial.read();
        i = 0;
        CurrentState = STATE_ADDRESS_LENGTH;
      } 
      else if(CurrentState == STATE_ADDRESS_LENGTH) {
        AddressBuffer[i] = Serial.read();
        i++;
        if(i==AddressLength)
        { 
          //send the address
          myMatrix.sendAddressArray(AddressLength, AddressBuffer);

          CurrentState = STATE_WAITING;
          AddressLength = 0;
          Serial.print('A');
        }
      } 
      else if(CurrentState == STATE_DATA) {
        DataLength = Serial.read();
        i = 0;
        CurrentState = STATE_DATA_LENGTH;
      } 
      else if(CurrentState == STATE_DATA_LENGTH) {
        DataBuffer[i] = Serial.read();
        i++;
        if(i==DataLength)
        {
          //send the data
          myMatrix.sendDataArray(DataLength, DataBuffer);

          CurrentState = STATE_WAITING;
          DataLength = 0;
          Serial.print('D');
        }
      }
    }

  }
}
