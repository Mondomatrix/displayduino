#ifndef MatrixNetHeader
#define MatrixNetHeader

#if defined(__AVR_ATmega324P__) || defined(__AVR_ATmega644P__)

#define DirControlPin 22

class MatrixNet {

public:
       void begin();

       void sendAddressArray(unsigned char NumBytes, unsigned char* DataBuffer);
       void sendDataArray(unsigned char NumBytes, unsigned char* DataBuffer);
       void sendDataByte(unsigned char DataByte);
       void sendAddressByte(unsigned char DataByte);

       void setReceive();
       void setTransmit();

       void changeLED(unsigned char BoardNumber, unsigned char LEDNumber, unsigned char Red, unsigned char Green, unsigned char Blue);
       void changeLEDBoard(unsigned char BoardNumber, unsigned char *RedArray, unsigned char *GreenArray, unsigned char *BlueArray);

       void changeServo(unsigned char BoardNumber, unsigned char ServoNumber, unsigned char Position);
       void changeServoBoard(unsigned char BoardNumber, unsigned char *PositionArray);
};
#endif

#endif