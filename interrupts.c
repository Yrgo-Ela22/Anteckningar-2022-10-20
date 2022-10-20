/********************************************************************************
* interrupts.c: Inneh�ller avbrottsrutiner.
********************************************************************************/
#include "header.h"

/********************************************************************************
* ISR (PCINT0_vect): Avbrottsrutin f�r PCI-avbrott p� I/O-port B, som anropas
*                    vid uppsl�ppning eller nedtryckning av tryckknappar
*                    anslutna till pin 12 - 13 (PORTB4 - PORTB4). Om n�gon av
*                    dessa knappar trycks ned s� uppdateras tillst�ndsmaskinen.
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
*                  ansluten till pin 2 (PORTD2). Vid reset s� �terst�lls
*                  tillst�ndsmaskinen till startl�get (lysdioderna sl�cks).
********************************************************************************/
ISR (INT0_vect)
{
   fsm_reset();
   return;
}