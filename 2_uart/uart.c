#include "uart.h"
#include "gpio.h"

#define TXD_PIN 6
#define RXD_PIN 8

#define UART ((NRF_UART_REG*)0x40002000)

typedef struct{
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX;
    volatile uint32_t TASKS_STOPTX;
    volatile uint32_t RESERVED0[3];
    volatile uint32_t TASKS_SUSPEND;
    volatile uint32_t RESERVED1[56];
    volatile uint32_t EVENTS_CTS;
    volatile uint32_t EVENTS_NCTS;
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t EVENTS_TXDRDY;
    volatile uint32_t RESERVED3;
    volatile uint32_t EVENTS_ERROR;
    volatile uint32_t RESERVED4[7];
    volatile uint32_t EVENTS_RXTO;
    volatile uint32_t RESERVED5[46];
    volatile uint32_t SHORTS;
    volatile uint32_t RESERVED6[64];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED7[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED8[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED9;
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED10;
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED11[17];
    volatile uint32_t CONFIG;
} NRF_UART_REG;



void uart_init(){
    GPIO->PIN_CNF[TXD_PIN] = 1; // TXD output
    GPIO->PIN_CNF[RXD_PIN] = 0; // RXD input

    UART->PSELTXD = TXD_PIN;
    UART->PSELRXD = RXD_PIN;

    UART->BAUDRATE = 0x00275000; // 9600 baudrate

    UART->PSELCTS = 0xFFFFFFFF; // CTS disconnected
    UART->PSELRTS = 0xFFFFFFFF; // RTS discnnected

    UART->ENABLE = 4;
    UART->TASKS_STARTRX = 1;
}


void uart_send(char letter){
    UART->TASKS_STARTTX = 1;
    UART->TXD = letter;
    
    while (!UART->EVENTS_TXDRDY); // Wait while transmitting

    UART->TASKS_STOPTX = 1;
    UART->EVENTS_TXDRDY = 0; // Clear event
}


char uart_read(){
    UART->TASKS_STARTRX = 1;
    char letter = (UART->EVENTS_RXDRDY) ? UART->RXD : 0;
    UART->EVENTS_RXDRDY = 0;
    return letter;
}