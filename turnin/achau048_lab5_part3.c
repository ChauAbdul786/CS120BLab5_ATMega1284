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

enum States {Start, off, one, two, three, four, five, six, button} State; 
unsigned char tmpA;
unsigned char tmpB;
unsigned char stateCount;

void TickFct(){
    switch(State){
    case Start:
        State = off;
        break;
    case off:
        if((tmpA & 0x01) == 0x00){
            State = button;
        }
        break;
    case one:
        if((tmpA & 0x01) == 0x00){
            State = button;
        }
        break;
    case two:
        if((tmpA & 0x01) == 0x00){
            State = button;
        }
        break;
    case three:
        if((tmpA & 0x01) == 0x00){
            State = button;
        }
        break;
    case four:
        if((tmpA & 0x01) == 0x00){
            State = button;
        }
        break;
    case five:
        if((tmpA & 0x01) == 0x00){
            State = button;
        }
        break;
    case six:
        if((tmpA & 0x01) == 0x00){
            State = button;
        }
        break;
    case button:
        if((tmpA & 0x01) == 0x01){
            if(stateCount == 0 || stateCount == 10){
                State = one;
            }else if(stateCount == 1 || stateCount == 9){
                State = two;
            }else if(stateCount == 2 || stateCount == 8){
                State = three;
            }else if(stateCount == 3 || stateCount == 7){
                State = four;
            }else if(stateCount == 4 || stateCount == 6){
                State = five;
            }else if(stateCount == 5){
                State = six;
            }else if(stateCount == 11){
		State = off;
	    }
            stateCount++;
        }
	break;
    default:
        State = off;
        break;
    }

    switch(State){
    case Start:
        break;
    case off:
        tmpB = 0x00;
        break;
    case one:
        tmpB = 0x01; //0000 0001
        break;
    case two:
        tmpB = 0x21; //0010 0001
        break;
    case three:
        tmpB = 0x23; //0010 0011
        break;
    case four:
        tmpB = 0x33; //0011 0011
        break;
    case five:
        tmpB = 0x37; //0011 0111
        break;
    case six:
        tmpB = 0x3F; //0011 1111
        break;
    case button:
   	break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0xFF;

    /* Insert your solution below */
    State = Start;
    stateCount = 0;
    while (1) {
        tmpA = PINA;
        tmpB = PORTB;
        TickFct();
        PORTB = tmpB;
    }
    return 1;
}
