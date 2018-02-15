#if defined(__AVR__)
#include <avr/wdt.h>
#endif

#if defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
#define LED	13
#define TIME	WDTO_1S

#elif defined(__MSP430FR5739__)
#define LED	RED_LED
#define TIME	1

#elif defined(__AVR_ATtiny85__)
#define LED	0
#define TIME	WDTO_1S

#else
#error "Unsupported architecture!"

#endif
