/********************************************************************************
* fsm.c: Innehåller funktionalitet för implementering av tillståndsmaskinen
*        för styrning av lysdioderna. Pekare används vid passering av 
*        blinkhastigheten för att direkt kunna avbryta en blinkning ifall
*        aktuellt tillstånd övergår från blinkande till annat tillstånd.
*        Fördröjningstiden som refereras till nollställs när detta sker, 
*        vilket medför att kvarvarande fördröjningstid sätts till noll.
********************************************************************************/
#include "header.h"

/* Statiska funktioner: */
static void leds_blink(const volatile uint16_t* blink_speed_ms);
static void delay_ms(const volatile uint16_t* delay_time_ms);

/* Statiska datamedlemmar: */
static enum led_state state = LED_STATE_OFF; /* Lagrar dörrens tillstånd. */
static uint16_t speed_ms = 0;                /* Lysdiodernas blinkhastighet i ms. */

/********************************************************************************
* fsm_reset: Återställer tillståndsmaskinen till startläget, vilket innebär
*            att lysdioderna släcks.
********************************************************************************/
void fsm_reset(void)
{
   state = LED_STATE_OFF;
   speed_ms = 0;
   LEDS_OFF;
   return;
}

/********************************************************************************
* fsm_uppdate: Uppdaterar tillståndsmaskinen utefter nuvarande tillstånd samt
*              vilken tryckknapp som trycks ned. För att avbryta eventuell
*              blinkning så nollställs lysdiodernas blinkhastighet temporärt 
*              när aktuellt tillstånd övergår från blinkande till något annat. 
*              Tillståndsmaskinens utsignaler uppdateras innan funktionen
*              avslutas (eventuell blinkning genomförs ej, utan kräver att
*              användaren kör tillståndsmaskinen via funktionen fsm_set_output).
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
* fsm_set_output: Uppdaterar tillståndsmaskinens utsignaler utefter aktuellt 
*                 tillstånd. 
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
*             Blinkhastigheten refereras till via en pekare för att direkt kunna 
*             uppdateras, exempelvis för att avbrytas, vilket åstadkommes genom
*             att värdet på den passerade adressen nollställs).
*
*             - blink_speed_ms: Pekare till blinkhastigheten mätt i ms.
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
* delay_ms: Genererar fördröjning mätt i millisekunder. Fördröjningstiden
*           refereras till via en pekare för att direkt kunna uppdateras, 
*           exempelvis för att avbrytas (åstadkommes genom att värdet på den
*           passerade adressen nollställs). 
*
*           - delay_time_ms: Pekare till fördröjningstiden mätt i ms.
********************************************************************************/
static void delay_ms(const volatile uint16_t* delay_time_ms)
{
   for (uint16_t i = 0; i < *delay_time_ms; ++i)
   {
      _delay_ms(1);
   }

   return;
}


