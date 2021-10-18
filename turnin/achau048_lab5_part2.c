/*  Author: Abdullah Chaudhry   
 *  Partner(s) Name: 
 *  Lab Section: 021
 *  Assignment: Lab #5  Exercise #1
 *  Exercise Description: [optional - include for your own benefit]
 *
 *  I acknowledge all content contained herein, excluding template or example
 *  code, is my own original work.
 */
#include <avr/io.h>
#ifdef SIMULATE
#include "simAVRHeader.h"
#endif

enum States {Start, wait, waitRelease, inc, dec, reset} State; 
unsigned char tmpA;
unsigned char tmpB;

void TickFct(){
    switch(State){
        case Start:
            State = wait; 
            break;

        case wait:
            if((tmpA & 0x03) == 0x03){
                State = wait;
            }else if((tmpA & 0x03) == 0x02){
                State = inc;
            }else if((tmpA & 0x03) == 0x01){
                State = dec;
            }else if((tmpA & 0x03) == 0x00){
                State = reset;
            }
            break;

        case inc:
            State = waitRelease;
            break;

        case dec:
            State = waitRelease;
            break;

        case reset:
            State = waitRelease;
            break;

	case waitRelease:
	    if((tmpA & 0x03) == 0x03){
		State = wait;
	    }else if((tmpA & 0x03) == 0x00){
		State = reset;
	    }
	    break;

        default:
            State = Start;
            break;
    }

    switch(State){
        case Start:
            tmpB = 0x07;
            break;

        case wait:
            break;

        case inc:
            if(tmpB < 8){
                tmpB++;
            }
            break;

        case dec:
            if(tmpB > 0){
                tmpB--;
            }
            break;

        case reset:
            tmpB = 0;
            break;
	
	case waitRelease:
	    break;

        default:
            tmpB = 7;
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x07;

    /* Insert your solution below */
    State = Start;
    while (1) {
        tmpA = PINA;
        tmpB = PORTB;
        TickFct();
        PORTB = tmpB;
    }
    return 1;
}
