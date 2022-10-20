/********************************************************************************
* interrupts.c: Innehåller avbrottsrutiner.
********************************************************************************/
#include "header.h"

/********************************************************************************
* ISR (PCINT0_vect): Avbrottsrutin för PCI-avbrott på I/O-port B, som anropas
*                    vid uppsläppning eller nedtryckning av tryckknappar
*                    anslutna till pin 12 - 13 (PORTB4 - PORTB4). Om någon av
*                    dessa knappar trycks ned så uppdateras tillståndsmaskinen.
********************************************************************************/
ISR (PCINT0_vect)
{
   if (PREVIOUS_BUTTON_PRESSED || NEXT_BUTTON_PRESSED)
   {
      fsm_update();
   }

   return;
}

/********************************************************************************
* ISR (INT0_vect): Avbrottsrutin, som anropas vid nedtryckning av reset-knappen
*                  ansluten till pin 2 (PORTD2). Vid reset så återställs
*                  tillståndsmaskinen till startläget (lysdioderna släcks).
********************************************************************************/
ISR (INT0_vect)
{
   fsm_reset();
   return;
}