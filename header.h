/********************************************************************************
* header.h: Innehåller diverse definitioner och deklarationer för implementering
*           av tillståndsmaskinen.
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

/* Klockfrekvens (behövs för fördröjningsgenerering med funktionen _delay_ms): */
#define F_CPU 16000000UL /* 16 MHz. */

/* Inkluderingsdirektiv: */
#include <avr/io.h>        /* Innehåller information om I/O-register såsom DDRB och PORTB. */
#include <avr/interrupt.h> /* Innehåller information om avbrottsvektorer såsom PCINT0_vect. */
#include <util/delay.h>    /* Innehåller funktionalitet för fördröjningsgenerering. */

/* Makrodefinitioner: */
#define LED1 0 /* Lysdiod 1 ansluten till pin 8 / PORTB0. */
#define LED2 1 /* Lysdiod 2 ansluten till pin 9 / PORTB1. */
#define LED3 2 /* Lysdiod 3 ansluten till pin 10 / PORTB2. */

#define PREVIOUS_BUTTON 4 /* Knapp för byte till föregående tillstånd ansluten till pin 12 / PORTB4. */
#define NEXT_BUTTON 5     /* Knapp för byte till nästa tillstånd ansluten till pin 13 / PORTB5. */
#define RESET_BUTTON 2    /* Reset-knapp ansluten till pin 2 / PORTD2. */

#define LED1_ON PORTB |= (1 << LED1) /* Tänder lysdiod 1. */
#define LED2_ON PORTB |= (1 << LED2) /* Tänder lysdiod 2. */
#define LED3_ON PORTB |= (1 << LED3) /* Tänder lysdiod 3. */

#define LED1_OFF PORTB &= ~(1 << LED1) /* Släcker lysdiod 1. */
#define LED2_OFF PORTB &= ~(1 << LED2) /* Släcker lysdiod 2. */
#define LED3_OFF PORTB &= ~(1 << LED3) /* Släcker lysdiod 3. */

#define LEDS_ON PORTB |= (1 << LED1) | (1 << LED2) | (1 << LED3)     /* Tänder lysdioderna. */
#define LEDS_OFF PORTB &= ~((1 << LED1) | (1 << LED2) | (1 << LED3)) /* Släcker lysdioderna. */

#define PREVIOUS_BUTTON_PRESSED (PINB & (1 << PREVIOUS_BUTTON)) /* Indikerar byte till föregående tillstånd. */
#define NEXT_BUTTON_PRESSED (PINB & (1 << NEXT_BUTTON))         /* Indikerar byte till nästa tillstånd */
#define RESET_BUTTON_PRESSED (PIND & (1 << RESET_BUTTON))       /* Indikerar nedtryckning av reset-knappen. */

/********************************************************************************
* bool: Datatyp som indikerar sant eller falskt. Denna datatyp är vanlig i
*       flertalet programmeringsspråk. I C utgör bool dock inte en primitiv
*       datatyp, men kan implementeras via en enumeration som här eller via
*       inkludering av standardbiblioteket stdbool.h (för C99 och senare).
********************************************************************************/
typedef enum { false, true } bool;

/********************************************************************************
* led_state: Datatyp för lagring av lysdiodernas tillstånd.
********************************************************************************/
enum led_state { LED_STATE_OFF, LED_STATE_BLINK, LED_STATE_ON };

/********************************************************************************
* setup: Initierar mikrodatorn vid start.
********************************************************************************/
void setup(void);

/********************************************************************************
* fsm_reset: Återställer tillståndsmaskinen till startläget, vilket innebär
*            att lysdioderna släcks.
********************************************************************************/
void fsm_reset(void);

/********************************************************************************
* fsm_uppdate: Uppdaterar tillståndsmaskinen utefter nuvarande tillstånd samt
*              vilken tryckknapp som trycks ned.
********************************************************************************/
void fsm_update(void);

/********************************************************************************
* fsm_set_output: Uppdaterar tillståndsmaskinens utsignaler utefter aktuellt
*                 tillstånd.
*
*                 blink_speed_ms: Lysdiodernas blinkhastighet vid blinkning.
********************************************************************************/
void fsm_set_output(const uint16_t blink_speed_ms);

#endif /* HEADER_H_ */