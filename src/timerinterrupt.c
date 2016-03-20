#include <timerinterrupt.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// DEBUG
#include <printf.h>

static const int _PRESCALER = 246;

static void (*_callback)() = 0;

static int _countdown;
static int _period;

static int _running;

void TimerInterrupt_EnterCrit()
{
	TCCR2B &= ~((1 << CS22)|(1 << CS21)|(1 << CS20));
}

void TimerInterrupt_ExitCrit()
{
	if(_running)	
		TCCR2B |= (1 << CS22)|(1 << CS21)|(1 << CS20);
}

void _TimerInterrupt_Init(int period_ms, void (*callback)())
{
	TimerInterrupt_Stop();

	_callback = callback;
	
	// Set the interrupt frequency
	_period = period_ms * (F_CPU / 1000) / _PRESCALER;
	
	// Copy to the _counter register for the first iteration
	_countdown = _period;

	// Set the timer register
	if(_countdown > 255) {
		OCR2A = 255;
		_countdown = _countdown - 255;
	}
	else {
		OCR2A = _countdown;
	}

	printf("OCR2A: %u", OCR2A);

	// CTC Mode
	TCCR2A |= (1 << WGM21);

	// Enable interrupt on compare match between TCNT2 and OCR2A
	TIMSK2 |= (1 << OCIE2A);
}

void TimerInterrupt_Start()
{
	// Start the timer, prescaler = 1024
	TCCR2B |= (1 << CS22)|(1 << CS21)|(1 << CS20);

	// Set the running flag
	_running = 1;
}

void TimerInterrupt_Stop()
{
	// Stop the timer
	TCCR2B &= ~((1 << CS22)|(1 << CS21)|(1 << CS20));

	// Unset the running flag
	_running = 0;

	// Reset the timer
	TCNT2 = 0;
}

ISR(TIMER2_COMPA_vect)
{
	if(_countdown == 0) {
		_callback();
		_countdown = _period;
	}

	// Set the countdown for next time
	if(_countdown > 255) { // We have more counts to go
		OCR2A = 255;
		_countdown = _countdown - 255;
	}
	else { // If we're on the last count
		OCR2A = _countdown;
		_countdown = 0;
	}
}

