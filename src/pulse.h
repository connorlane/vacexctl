#ifndef PULSE_H
#define PULSE_H

#include <pwm.h>
#include <serial.h>

#ifndef PULSE_INITIALIZED
#define PULSE_INITIALIZED
#define Pulse_Init() _Pulse_Init();
#else
#define Pulse_Init()
#endif

void _Pulse_Init() {
	PWM_Init();

        // Fast PWM Mode
        TCCR0B |= (1 << WGM02);
        TCCR0A |= (1 << WGM01) | (1 << WGM00);

        // Enable interrupts on compare match A and B
        TIMSK0 |= (1 << OCIE0B) | (1 << TOIE0);
}

void Pulse_Start() {
        // Prescaler 1/64
        //TCCR0B |= (1 << CS01) | (1 << CS00);

	// Prescaler 1/1024
	TCCR0B |= (1 << CS02) | (1 << CS00);
}

void Pulse_Stop() {
        // Prescaler 1/64
        //TCCR0B &= ~((1 << CS01) | (1 << CS00));

	// Prescaler 1/1024
	TCCR0B &= ~((1 << CS02) | (1 << CS00));

	PWM_Stop();
}

void Pulse_Set(int ontime_us, int offtime_us) {
        int oncounts = ontime_us * (F_CPU / 1024) / 1000000UL;
        int offcounts = offtime_us * (F_CPU / 1024) / 1000000UL;

        OCR0B = oncounts;
        OCR0A = oncounts + offcounts;
}

ISR(TIMER0_OVF_vect) {
        PWM_Stop();
}

ISR(TIMER0_COMPB_vect) {
        PWM_Start();
}

#endif
