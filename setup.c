/********************************************************************************
* setup.c: Inneh�ller initieringsrutiner.
********************************************************************************/
#include "header.h"

/* Statiska funktioner: */
static inline void init_ports(void);
static inline void init_interrupts(void);

/********************************************************************************
* setup: Initierar mikrodatorn vid start.
********************************************************************************/
void setup(void)
{
   init_ports();
   init_interrupts();
   fsm_reset();
   return;
}

/********************************************************************************
* init_ports: S�tter lysdiodernas pinnar till utportar och s�tter tryckknapparnas
*             pinnar till aktiva inportar (insignalerna blir alltid 0 eller 1).
********************************************************************************/
static inline void init_ports(void)
{
   DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3);
   PORTD = (1 << PREVIOUS_BUTTON) | (1 << NEXT_BUTTON);
   PORTD = (1 << RESET_BUTTON);
   return;
}

/********************************************************************************
* init_interrupts: Aktiverar PCI-avbrott p� pin 12 - 13 / PORTB4 - PORTB5 samt
*                  externt avbrott INT0 p� pin 2 (PORTD2) p� stigande flank.
*
*                  PCI-avbrotten har avbrottsvektor PCINT0_vect.
*                  Externt avbrott INT0 har avbrottsvektor INT0_vect.
********************************************************************************/
static inline void init_interrupts(void)
{
   asm("SEI");
   PCICR = (1 << PCIE0);
   PCMSK0 = (1 << PREVIOUS_BUTTON) | (1 << NEXT_BUTTON);

   EICRA = (1 << ISC00) | (1 << ISC01);
   EIMSK = (1 << INT0);
   return;
}