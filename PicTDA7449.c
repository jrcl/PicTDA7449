#include <16F628A.h>

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES PUT                      //Power Up Timer
#use delay(internal=4000000)

#use i2c(Master,Fast=100000, sda=PIN_A2, scl=PIN_A3, force_sw)

#include <libTDA7449.c>

#BYTE TRISB=0X86
#BYTE PORTB=0X06

void main()
{

   TRISB = 0x00;
   PORTB = menuTDA;

   char control, step;

   while(TRUE) {

      control = (input(PIN_A0)) | (input(PIN_A6)<<1) | (input(PIN_A7)<<2);
      step = 0x00;

      switch(control){
         case 0x01: // Buttom Menu
            changeMenuTDA();
            PORTB = menuTDA;
            break;
         case 0x02: //Buttom Down
            step = '-';
            break;
         case 0x04: //Buttom Up
            step = '+';
            break;
      }

      if (step != 0x00){
      delay_ms(200);
      switch(menuTDA){
         case inputSelect:
            changeChannel();
            break;
         case inputGain:
            changeDBInput(step);
            break;
         case volume:
            changeVolume(step);
            break;
         case bass:
            changeBass(step);
            break;
         case treble:
            changeTreble(step);
            break;
         case spkrAttR:
            changeSpkrAttR(step);
            break;
         case spkrAttL:         
            changeSpkrAttL(step);
            break;
         }
      }
   }

}
