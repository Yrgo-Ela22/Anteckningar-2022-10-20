/********************************************************************************
* fsm.c: Inneh�ller funktionalitet f�r implementering av tillst�ndsmaskinen
*        f�r styrning av lysdioderna. Pekare anv�nds vid passering av 
*        blinkhastigheten f�r att direkt kunna avbryta en blinkning ifall
*        aktuellt tillst�nd �verg�r fr�n blinkande till annat tillst�nd.
*        F�rdr�jningstiden som refereras till nollst�lls n�r detta sker, 
*        vilket medf�r att kvarvarande f�rdr�jningstid s�tts till noll.
********************************************************************************/
#include "header.h"

/* Statiska funktioner: */
static void leds_blink(const volatile uint16_t* blink_speed_ms);
static void delay_ms(const volatile uint16_t* delay_time_ms);

/* Statiska datamedlemmar: */
static enum led_state state = LED_STATE_OFF; /* Lagrar d�rrens tillst�nd. */
static uint16_t speed_ms = 0;                /* Lysdiodernas blinkhastighet i ms. */

/********************************************************************************
* fsm_reset: �terst�ller tillst�ndsmaskinen till startl�get, vilket inneb�r
*            att lysdioderna sl�cks.
********************************************************************************/
void fsm_reset(void)
{
   state = LED_STATE_OFF;
   speed_ms = 0;
   LEDS_OFF;
   return;
}

/********************************************************************************
* fsm_uppdate: Uppdaterar tillst�ndsmaskinen utefter nuvarande tillst�nd samt
*              vilken tryckknapp som trycks ned. F�r att avbryta eventuell
*              blinkning s� nollst�lls lysdiodernas blinkhastighet tempor�rt 
*              n�r aktuellt tillst�nd �verg�r fr�n blinkande till n�got annat. 
*              Tillst�ndsmaskinens utsignaler uppdateras innan funktionen
*              avslutas (eventuell blinkning genomf�rs ej, utan kr�ver att
*              anv�ndaren k�r tillst�ndsmaskinen via funktionen fsm_set_output).
********************************************************************************/
void fsm_update(void)
{
   switch (state)
   {
      case LED_STATE_OFF:
      {
         if (NEXT_BUTTON_PRESSED)
         {
            state = LED_STATE_BLINK;
         }
         else if (PREVIOUS_BUTTON_PRESSED)
         {
            state = LED_STATE_ON;
         }

         break;
      }

      case LED_STATE_BLINK:
      {
         if (NEXT_BUTTON_PRESSED)
         {
            state = LED_STATE_ON;
            speed_ms = 0;
         }
         else if (PREVIOUS_BUTTON_PRESSED)
         {
            state = LED_STATE_OFF;
            speed_ms = 0;
         }

         break;
      }

      case LED_STATE_ON:
      {
         if (NEXT_BUTTON_PRESSED)
         {
            state = LED_STATE_OFF;
         }
         else if (PREVIOUS_BUTTON_PRESSED)
         {
            state = LED_STATE_BLINK;
         }

         break;
      }

      default:
      {
         fsm_reset();
         break;
      }
   }

   fsm_set_output(0);
   return;
}

/********************************************************************************
* fsm_set_output: Uppdaterar tillst�ndsmaskinens utsignaler utefter aktuellt 
*                 tillst�nd. 
*
*                 blink_speed_ms: Lysdiodernas blinkhastighet vid blinkning.
********************************************************************************/
void fsm_set_output(const uint16_t blink_speed_ms)
{
   if (state == LED_STATE_OFF)
   {
      LEDS_OFF;
   }
   else if (state == LED_STATE_BLINK)
   {
      speed_ms = blink_speed_ms;
      leds_blink(&speed_ms);
   }
   else if (state == LED_STATE_ON)
   {
      LEDS_ON;
   }
   else
   {
      fsm_reset();
   }
   return;
}

/********************************************************************************
* leds_blink: Blinkar lysdioderna i en slinga med angiven blinkhastighet.
*             Blinkhastigheten refereras till via en pekare f�r att direkt kunna 
*             uppdateras, exempelvis f�r att avbrytas, vilket �stadkommes genom
*             att v�rdet p� den passerade adressen nollst�lls).
*
*             - blink_speed_ms: Pekare till blinkhastigheten m�tt i ms.
********************************************************************************/
static void leds_blink(const volatile uint16_t* blink_speed_ms)
{
   LEDS_OFF;
   LED1_ON;
   delay_ms(blink_speed_ms);

   LED1_OFF;
   LED2_ON;
   delay_ms(blink_speed_ms);

   LED2_OFF;
   LED3_ON;
   delay_ms(blink_speed_ms);

   LED3_OFF;
   return;
}

/********************************************************************************
* delay_ms: Genererar f�rdr�jning m�tt i millisekunder. F�rdr�jningstiden
*           refereras till via en pekare f�r att direkt kunna uppdateras, 
*           exempelvis f�r att avbrytas (�stadkommes genom att v�rdet p� den
*           passerade adressen nollst�lls). 
*
*           - delay_time_ms: Pekare till f�rdr�jningstiden m�tt i ms.
********************************************************************************/
static void delay_ms(const volatile uint16_t* delay_time_ms)
{
   for (uint16_t i = 0; i < *delay_time_ms; ++i)
   {
      _delay_ms(1);
   }

   return;
}


