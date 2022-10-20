/********************************************************************************
* main.c: Implementering av en tillst�ndsmaskin f�r tre lysdioder, som kan
*         anta tre tillst�nd:
*
*
*         Tillst�nd            Resultat
*            OFF       Lysdioderna h�lls sl�ckta.
*           BLINK      Lysdioderna blinkar i en slinga var 100:e millisekund.
*            ON        Lysdioderna h�lls t�nda.
*
*          Tv� tryckknappar PREVIOUS_BUTTON samt NEXT_BUTTON anslutna till
*          pin 12 - 13 (PORTB4 - PORTB5) anv�nds f�r att uppdatera lysdiodernas
*          tillst�nd fram�t eller bak�t. En resetknapp RESET_BUTTON ansluten 
*          till pin 2 (PORTD2) anv�nds f�r att omedelbart �terst�lla
*          lysdioderna till startl�get (lysdioderna sl�cks).
********************************************************************************/
#include "header.h"

/********************************************************************************
* main: Initierar systemet vid start (konfigurerar I/O-portar samt aktiverar
*       avbrott p� tryckknapparnas pinnar). Programmet h�lls sedan ig�ng
*       kontinuerligt s� l�nge matningssp�nning tillf�rs. Lysdioderna tillst�nd
*       uppdateras via avbrottsrutiner. Tillst�nsdmaskinens utsignaler 
*       uppdateras kontinuerligt utefter aktuellt tillst�nd.
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

