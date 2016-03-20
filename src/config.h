
#define RING_BUFFER_SIZE 255

#define UART_TX PD1
#define UART_TX_DDR DDRD

#define XON_CHAR 17
#define XOFF_CHAR 19

#define LED0 PB0
#define LED0_PORT PORTB
#define LED0_DDR DDRB

#define TXEN PD2
#define TXEN_PORT PORTD
#define TXEN_DDR DDRD

#define HX711_SCK PD3
#define HX711_SCK_PORT PORTD
#define HX711_SCK_DDR DDRD

#define HX711_DOUT PD4
#define HX711_DOUT_PIN PIND
#define HX711_DOUT_DDR DDRD

#define HVSIG PB2
#define HVSIG_PORT PORTB
#define HVSIG_DDR DDRB

#define HVFEEDBACK_CHANNEL 5

#define HV_SAMPLING_FREQUENCY 1000

// This is the number of volts per ADC unit. The hardware is configured
//   so that a full ADC value of 256 is equivalent to 10,000 volts.
//   This value is multiplied by 16. This is to increase the accuracy 
//   without resorting to floating point math. The result must be divided
//   by 16 after mulitplication with the ADC value for the correct voltage.
#define HV_CONVERSION_RATIO_x16 (16*10000UL / 256)
