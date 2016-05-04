
#define RING_BUFFER_SIZE 255

#define UART_TX PD1
#define UART_TX_DDR DDRD

#define XON_CHAR 17
#define XOFF_CHAR 19

#define PRESSURE_ADC_CHANNEL 5
#define MIN_ADC_VALUE (53)
#define MAX_ADC_VALUE (255)
#define MIN_PRESSURE (-14.50F)
#define MAX_PRESSURE (11.81F)

// In #1
#define BUTTON PC3
#define BUTTON_PIN PINC
#define BUTTON_DDR DDRC

// In #2
#define PRESSUREFAULT PC4
#define PRESSUREFAULT_PIN PINC
#define PRESSUREFAULT_DDR DDRC

// Out #1
#define AIR PD7
#define AIR_PORT PORTD
#define AIR_DDR DDRD

// Out #2
#define PUMP PB0
#define PUMP_PORT PORTB
#define PUMP_DDR DDRB

// Out #3
#define ARGON PD6
#define ARGON_PORT PORTD
#define ARGON_DDR DDRD

// Out #4
#define LED PD0
#define LED_PORT PORTD
#define LED_DDR DDRD

