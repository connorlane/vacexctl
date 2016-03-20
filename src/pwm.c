#include <pwm.h>
#include <avr/io.h>
#include <config.h>

void _PWM_Init() {
	PWM_Write(0, 0);

	// Set direction of HVSIG to output (the OC1A pin)
	HVSIG_DDR |= (1 << HVSIG);

	// Make sure pin is zero
	HVSIG_PORT &= ~(1 << HVSIG);
	
	// set Fast PWM mode using ICR1 as TOP
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12)|(1 << WGM13);
}

void PWM_Start()
{
	// If the timer is already started, return
	if ((TCCR1B & (1 <<  CS10)))
		return;

	// Set the timer to zero
	TCNT1 = 0;

	// Connect the output compare pin
	TCCR1A |= (1 << COM1B1)|(1 << COM1A1);

	// Start the timer
	TCCR1B |= (1 << CS10);
}

void PWM_Stop()
{
	// If the timer is already stopped, return
	if (!(TCCR1B & (1 <<  CS10)))
		return;

	// Reset the compare match flag so we can wait for a compare match
	TIFR1 |= (1 << OCF1B);

	// Wait for timer compare match so we don't stop mid pulse
	while (!(TIFR1 & (1 << OCF1B)));

	// Disconnect the output compare pin
	TCCR1A &= ~((1 << COM1B1)|(1 << COM1A1));

	// Stop the timer
	TCCR1B &= ~(1 << CS10);
}

void PWM_Write(uint16_t ontime_ns, uint16_t offtime_ns)
{
	// Scale to on/off times to microseconds (assuming no prescaler)
	uint16_t oncounts = (ontime_ns * (F_CPU / 1000)) / 1000000UL;
	uint16_t offcounts = (offtime_ns * (F_CPU / 1000)) / 1000000UL;	

	// Set the upper
	OCR1B = oncounts;

	// Reset the interrupt overflow flag
	TIFR1 |= (1 << TOV1);

	// If timer is running, wait for an overflow (so the counter doesn't go off into oblivion)
	if (TCCR1B & (1 << CS10))
		while (!(TIFR1 & (1<<TOV1)));

	// Now we can set ICR1 (the counter "top" value)
	ICR1 = oncounts + offcounts;
}

