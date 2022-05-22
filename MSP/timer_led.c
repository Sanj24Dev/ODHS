#include "msp.h"


/**
 * main.c
 */
int main(void) {
    /* initialize P2.1 for green LED */
    P2->SEL1 &= ~2;         /* configure P2.1 as simple I/O */
    P2->SEL0 &= ~2;
    P2->DIR |= 2;           /* P2.1 set as output */

    TIMER_A1->CTL = 0x01D1;     /* ACLK, ID = /8, up mode, TA clear */
    TIMER_A1->CCR[0] = 5120 - 1; /* for 10 sec */ //put 512-1 for 1 sec
    TIMER_A1->EX0 = 7;          /* IDEX = /8 */
    while (1) {
            while((TIMER_A1->CCTL[0] & 1) == 0); /* wait until the CCIFG flag is set */
            TIMER_A1->CCTL[0] &= ~1;            /* clear interrupt flag */
            P2->OUT ^= 2;                       /* toggle green LED */
        }
    }
