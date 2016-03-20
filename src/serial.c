#include "serial.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include "status.h"
#include "config.h"
#include "utilities.h"

static RingBuff_t _receiveBuffer;
static RingBuff_t _transmitBuffer;

static inline void _HandleTransmitCompleteInterrupt();
static inline void _HandleTransmitInterrupt();
static inline void _HandleReceiveInterrupt();

void _Serial_Init()
{
	// Set up the buffers
	RingBuffer_InitBuffer(&_receiveBuffer);
	RingBuffer_InitBuffer(&_transmitBuffer);

	// UART Transmit pin
	UART_TX_DDR |= (1 << UART_TX);

	// Set the transmit-enable pin direction and default to receive
	TXEN_DDR |= (1 << TXEN);
	TXEN_PORT &= ~(1 << TXEN);

		/* Setup UART */
	UBRR0H = 0;
	UBRR0L = 64; // 19200 Baud
		
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);	// No parity, eight data bits
	UCSR0B = ((1 << RXCIE0) | (1 << TXEN0) | (1 << RXEN0));
}

void Serial_Write(uint8_t byte)
{
	// Wait for the buffer to clear out. If interrupts are not enabled here, this will hang
	while(RingBuffer_IsFull(&_transmitBuffer));

	// Put the byte in the transmit buffer to be sent
	RingBuffer_Insert(&_transmitBuffer, byte);

	// Enable the interrupt when the data register empties
	UCSR0B |= (1 << UDRIE0);
}

void Serial_WriteBuffer(uint8_t* data, int numBytes)
{
	for(int i = 0; i < numBytes; i++)
		Serial_Write(data[i]);
}

void Serial_PrintHex(uint8_t val)
{
	uint8_t lower, upper;
	lower = (val & 0x0F);	// Lower
	upper = (val >> 4); 	// Upper

	if (upper <= 9)
		Serial_Write(upper + '0');
	else
		Serial_Write(upper + 'A' - 10);

	if (lower <= 9)
		Serial_Write(lower + '0');
	else
		Serial_Write(lower + 'A' - 10);
}

uint8_t Serial_Read()
{
	while (RingBuffer_IsEmpty(&_receiveBuffer));

	return RingBuffer_Remove(&_receiveBuffer);
}

int Serial_Available()
{
	return !RingBuffer_IsEmpty(&_receiveBuffer);
}

static inline void _HandleTransmitCompleteInterrupt()
{
	// Turn off transmit-enable
	TXEN_PORT &= ~(1 << TXEN);

	// Disable future transmit-complete interrupts
	UCSR0B &= ~(1 << TXCIE0);	
}

static inline void _HandleTransmitInterrupt()
{
	// If interrupts enabled, there must be more data in the output buffer, so send
	// the next byte
	uint8_t byte = RingBuffer_Remove(&_transmitBuffer);

	// Turn on transmit-enable
	TXEN_PORT |= (1 << TXEN);

	UDR0 = byte;

	// If the buffer is empty...
	if (RingBuffer_IsEmpty(&_transmitBuffer))
	{
		// Disable the interrupt
		UCSR0B &= ~(1 << UDRIE0);

		// Clear the transmit-complete flag	
		UCSR0A |= (1 << TXC0);

		// Schedule transmit-complete interrupt
		UCSR0B |= (1 << TXCIE0);
	}
	else
	{
		// Disable the transmit-complete interrupt
		UCSR0B &= ~(1 << TXCIE0);
	}
}

static inline void _HandleReceiveInterrupt()
{
	uint8_t temp = UDR0;
	if (!RingBuffer_IsFull(&_receiveBuffer))
		RingBuffer_Insert(&_receiveBuffer, temp);
	else
		Error();
}

ISR(USART_TX_vect, ISR_BLOCK)
{
	_HandleTransmitCompleteInterrupt();
}

ISR(USART_UDRE_vect, ISR_BLOCK)
{
	_HandleTransmitInterrupt();
}

ISR(USART_RX_vect, ISR_BLOCK)
{
	_HandleReceiveInterrupt();
}
