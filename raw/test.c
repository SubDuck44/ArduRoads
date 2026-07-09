#include <avr/io.h>
#include <util/delay.h>

#define DELAY 500

int main(void) {
#define BAUD 9600
#include <util/setbaud.h>
	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;
#if USE_2X
	UCSR0A |= (1 << U2X0);
#else
	UCSR0A &= ~(1 << U2X0);
#endif

	UCSR0B = (1 << TXEN0);  // enable transmitter
	UCSR0C = (3 << UCSZ00); // 8-bit characters

	for(;;) {
		for(int i = 33; i < 128; i++) {
			loop_until_bit_is_set(UCSR0A, UDRE0);
			UDR0 = i;
		}

		for(int i = 0; i < 512; i++) {
			loop_until_bit_is_set(UCSR0A, UDRE0);
			UDR0 = ' ';
		}
	}

	////////////////////////////////////////

	// this is some fucking bootleg m328p and setting
	// port B pin 6 or 7 to output kills the thing
	// so uh dont do that    ōnō
	DDRB = 63;
	DDRD = 0xFF;

	for(;;) {
		for(int i = 2; i < 8; i++) {
			PORTD |= 1 << i;
			_delay_ms(DELAY);
		}

		for(int i = 0; i < 6; i++) {
			PORTB |= 1 << i;
			_delay_ms(DELAY);
		}

		for(int i = 2; i < 8; i++) {
			PORTD &= ~(1 << i);
			_delay_ms(DELAY);
		}

		for(int i = 0; i < 6; i++) {
			PORTB &= ~(1 << i);
			_delay_ms(DELAY);
		}
	}
}
