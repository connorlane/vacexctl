#ifndef TIMERINTERRUPT_H
#define TIMERINTERRUPT_H

#ifndef TIMERINTERRUPT_INITIALIZED
#define TIMERINTERRUPT_INITIALIZED
#define TimerInterrupt_Init(f, c) _TimerInterrupt_Init(f, c)
#else
#define TimerInterrupt_Init()
#endif

void TimerInterrupt_EnterCrit();

void TimerInterrupt_ExitCrit();

void _TimerInterrupt_Init(int period_ms, void (*callback)());

void TimerInterrupt_Start();

void TimerInterrupt_Stop();

#endif
