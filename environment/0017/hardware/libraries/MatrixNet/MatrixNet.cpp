#include "wiring.h"
#include "MatrixNet.h"

#if defined(__AVR_ATmega324P__) || defined(__AVR_ATmega644P__)

void MatrixNet::begin()
{
       pinMode(DirControlPin, OUTPUT);
       digitalWrite(DirControlPin, OUTPUT);

       UCSR1A = ((0 << TXC1) | (1 << U2X1) | (0 << MPCM1));
       UCSR1B = ((0 << RXCIE1) | (0 << TXCIE1) | (0 << UDRIE1) | (1 << RXEN1) | (1 << TXEN1) | (1 << UCSZ12) | (0 << RXB81) | (0 << TXB81));
       UCSR1C = ((0 << UMSEL11) | (0 << UMSEL10) | (0 << UPM11) | (0 << UPM10) | (0 << USBS1) | (1 << UCSZ11) | (1 << UCSZ10) | (0 << UCPOL1));
       UBRR1H = 0;
       UBRR1L = 21;
}

void MatrixNet::sendDataArray(unsigned char NumBytes, unsigned char* DataBuffer)
{
       unsigned char i = 0;

       //clear the 9th bit
       UCSR1B &= ~(1 << TXB81);

       UDR1 = DataBuffer[0];
       UCSR1A |= _BV(TXC1);
       while(!(UCSR1A & (1 << UDRE1)));

       for(i = 1; i< NumBytes; i++)
       {
               UDR1 = DataBuffer[i];

               //wait for empty transmit buffer
               while(!(UCSR1A & (1 << UDRE1)));
       }
}

void MatrixNet::sendAddressArray(unsigned char NumBytes, unsigned char* DataBuffer)
{
       unsigned char i = 0;

       //set the 9th bit
       UCSR1B |= (1 << TXB81);

       UDR1 = DataBuffer[0];
       UCSR1A |= _BV(TXC1);
       while(!(UCSR1A & (1 << UDRE1)));

       for(i = 1; i< NumBytes; i++)
       {
               UDR1 = DataBuffer[i];

               //wait for empty transmit buffer
               while(!(UCSR1A & (1 << UDRE1)));
       }
}

void MatrixNet::setTransmit()
{
       //wait for empty transmit buffer
       while(!(UCSR1A & (1 << UDRE1)));

       digitalWrite(DirControlPin, 1);
       asm("nop");
       asm("nop");
       asm("nop");
       asm("nop");
       asm("nop");
}

void MatrixNet::setReceive()
{
       while(!(UCSR1A & (1 << TXC1)));
       asm("nop");
       asm("nop");
       asm("nop");
       asm("nop");
       asm("nop");
       digitalWrite(DirControlPin, 0);
}

void MatrixNet::sendAddressByte(unsigned char DataByte)
{
       //wait for empty transmit buffer
       while(!(UCSR1A & (1 << UDRE1)));

       //set the 9th bit
       UCSR1B |= (1 << TXB81);

       UDR1 = DataByte;
       UCSR1A |= _BV(TXC1);
       while(!(UCSR1A & (1 << UDRE1)));
}

void MatrixNet::sendDataByte(unsigned char DataByte)
{
       //wait for empty transmit buffer
       while(!(UCSR1A & (1 << UDRE1)));

       //clear the 9th bit
       UCSR1B &= ~(1 << TXB81);

       UDR1 = DataByte;
       UCSR1A |= _BV(TXC1);
       while(!(UCSR1A & (1 << UDRE1)));
}

void MatrixNet::changeLED(unsigned char BoardNumber, unsigned char LEDNumber, unsigned char Red, unsigned char Green, unsigned char Blue)
{
       this->setTransmit();
       this->sendAddressByte(BoardNumber);
       this->sendDataByte(2);
       this->sendDataByte(LEDNumber);
       this->sendDataByte(Red);
       this->sendDataByte(Green);
       this->sendDataByte(Blue);
       this->setReceive();
}

void MatrixNet::changeServo(unsigned char BoardNumber, unsigned char ServoNumber, unsigned char Position)
{
       this->setTransmit();
       this->sendAddressByte(BoardNumber);
       this->sendDataByte(2);
       this->sendDataByte(ServoNumber);
       this->sendDataByte(Position);
       this->setReceive();
}

void MatrixNet::changeLEDBoard(unsigned char BoardNumber, unsigned char *RedArray, unsigned char *GreenArray, unsigned char *BlueArray)
{
       unsigned char i;

       this->setTransmit();
       this->sendAddressByte(BoardNumber);
       this->sendDataByte(1);

       for(i=0;i<64;i++)
       {
               this->sendDataByte(RedArray[i]);
               this->sendDataByte(GreenArray[i]);
               this->sendDataByte(BlueArray[i]);
       }
       this->setReceive();
}

void MatrixNet::changeServoBoard(unsigned char BoardNumber, unsigned char *PositionArray)
{
       this->setTransmit();
       this->sendAddressByte(BoardNumber);
       this->sendDataByte(1);
       this->sendDataArray(64, PositionArray);
       this->setReceive();
}


#endif
