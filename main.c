/********************************************************************************
* main.c: Implementering av en tillståndsmaskin för tre lysdioder, som kan
*         anta tre tillstånd:
*
*
*         Tillstånd            Resultat
*            OFF       Lysdioderna hålls släckta.
*           BLINK      Lysdioderna blinkar i en slinga var 100:e millisekund.
*            ON        Lysdioderna hålls tända.
*
*          Två tryckknappar PREVIOUS_BUTTON samt NEXT_BUTTON anslutna till
*          pin 12 - 13 (PORTB4 - PORTB5) används för att uppdatera lysdiodernas
*          tillstånd framåt eller bakåt. En resetknapp RESET_BUTTON ansluten 
*          till pin 2 (PORTD2) används för att omedelbart återställa
*          lysdioderna till startläget (lysdioderna släcks).
********************************************************************************/
#include "header.h"

/********************************************************************************
* main: Initierar systemet vid start (konfigurerar I/O-portar samt aktiverar
*       avbrott på tryckknapparnas pinnar). Programmet hålls sedan igång
*       kontinuerligt så länge matningsspänning tillförs. Lysdioderna tillstånd
*       uppdateras via avbrottsrutiner. Tillstånsdmaskinens utsignaler 
*       uppdateras kontinuerligt utefter aktuellt tillstånd.
********************************************************************************/
int main(void)
{
   setup();

   while (1)
   {
      fsm_set_output(100);
   }

   return 0;
}

