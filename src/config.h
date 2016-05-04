
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
#define AIR PD0
#define AIR_PORT PORTD
#define AIR_DDR DDRD

// Out #2
#define PUMP PD6
#define PUMP_PORT PORTD
#define PUMP_DDR DDRD

// Out #3
#define ARGON PD7
#define ARGON_PORT PORTD
#define ARGON_DDR DDRD

// Out #4
#define LED PB0
#define LED_PORT PORTB
#define LED_DDR DDRB

