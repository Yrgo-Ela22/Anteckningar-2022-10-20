/********************************************************************************
* header.h: Inneh�ller diverse definitioner och deklarationer f�r implementering
*           av tillst�ndsmaskinen.
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

/* Klockfrekvens (beh�vs f�r f�rdr�jningsgenerering med funktionen _delay_ms): */
#define F_CPU 16000000UL /* 16 MHz. */

/* Inkluderingsdirektiv: */
#include <avr/io.h>        /* Inneh�ller information om I/O-register s�som DDRB och PORTB. */
#include <avr/interrupt.h> /* Inneh�ller information om avbrottsvektorer s�som PCINT0_vect. */
#include <util/delay.h>    /* Inneh�ller funktionalitet f�r f�rdr�jningsgenerering. */

/* Makrodefinitioner: */
#define LED1 0 /* Lysdiod 1 ansluten till pin 8 / PORTB0. */
#define LED2 1 /* Lysdiod 2 ansluten till pin 9 / PORTB1. */
#define LED3 2 /* Lysdiod 3 ansluten till pin 10 / PORTB2. */

#define PREVIOUS_BUTTON 4 /* Knapp f�r byte till f�reg�ende tillst�nd ansluten till pin 12 / PORTB4. */
#define NEXT_BUTTON 5     /* Knapp f�r byte till n�sta tillst�nd ansluten till pin 13 / PORTB5. */
#define RESET_BUTTON 2    /* Reset-knapp ansluten till pin 2 / PORTD2. */

#define LED1_ON PORTB |= (1 << LED1) /* T�nder lysdiod 1. */
#define LED2_ON PORTB |= (1 << LED2) /* T�nder lysdiod 2. */
#define LED3_ON PORTB |= (1 << LED3) /* T�nder lysdiod 3. */

#define LED1_OFF PORTB &= ~(1 << LED1) /* Sl�cker lysdiod 1. */
#define LED2_OFF PORTB &= ~(1 << LED2) /* Sl�cker lysdiod 2. */
#define LED3_OFF PORTB &= ~(1 << LED3) /* Sl�cker lysdiod 3. */

#define LEDS_ON PORTB |= (1 << LED1) | (1 << LED2) | (1 << LED3)     /* T�nder lysdioderna. */
#define LEDS_OFF PORTB &= ~((1 << LED1) | (1 << LED2) | (1 << LED3)) /* Sl�cker lysdioderna. */

#define PREVIOUS_BUTTON_PRESSED (PINB & (1 << PREVIOUS_BUTTON)) /* Indikerar byte till f�reg�ende tillst�nd. */
#define NEXT_BUTTON_PRESSED (PINB & (1 << NEXT_BUTTON))         /* Indikerar byte till n�sta tillst�nd */
#define RESET_BUTTON_PRESSED (PIND & (1 << RESET_BUTTON))       /* Indikerar nedtryckning av reset-knappen. */

/********************************************************************************
* bool: Datatyp som indikerar sant eller falskt. Denna datatyp �r vanlig i
*       flertalet programmeringsspr�k. I C utg�r bool dock inte en primitiv
*       datatyp, men kan implementeras via en enumeration som h�r eller via
*       inkludering av standardbiblioteket stdbool.h (f�r C99 och senare).
********************************************************************************/
typedef enum { false, true } bool;

/********************************************************************************
* led_state: Datatyp f�r lagring av lysdiodernas tillst�nd.
********************************************************************************/
enum led_state { LED_STATE_OFF, LED_STATE_BLINK, LED_STATE_ON };

/********************************************************************************
* setup: Initierar mikrodatorn vid start.
********************************************************************************/
void setup(void);

/********************************************************************************
* fsm_reset: �terst�ller tillst�ndsmaskinen till startl�get, vilket inneb�r
*            att lysdioderna sl�cks.
********************************************************************************/
void fsm_reset(void);

/********************************************************************************
* fsm_uppdate: Uppdaterar tillst�ndsmaskinen utefter nuvarande tillst�nd samt
*              vilken tryckknapp som trycks ned.
********************************************************************************/
void fsm_update(void);

/********************************************************************************
* fsm_set_output: Uppdaterar tillst�ndsmaskinens utsignaler utefter aktuellt
*                 tillst�nd.
*
*                 blink_speed_ms: Lysdiodernas blinkhastighet vid blinkning.
********************************************************************************/
void fsm_set_output(const uint16_t blink_speed_ms);

#endif /* HEADER_H_ */