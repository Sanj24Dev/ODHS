#include "msp.h"

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;// Stop watchdog timer
    P2DIR = 0X02;   // Declare PIN Direction OF PORT 2 AS OUTPUT //p2.1 is green led
    unsigned int i;   // add delay variable
    while(1)
    {
        P2OUT=0X02;   //make bit0 HIGH
            for(i=0;i< 100000;i++){   //    delay till you make LED HIGH
            }
            P2OUT=0X00;   //make bit0 LOW

             for(i=0;i< 100000;i++){   // delay till you make LED LOW
              }

 }
}
