#include "uart.h"
#include "gpio.h"


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
    volatile uint16_t RESERVED7[93];
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
    GPIO->PIN_CNF[6] = 1; //TXD output
    GPIO->PIN_CNF[8] = 0; //RXD input

    UART->PSELTXD = 6;
    UART->PSELRXD = 8;

    UART->PSELCTS = 0xFFFFFFFF; //CTS disconnected
    UART->PSELRTS = 0xFFFFFFFF; //RTS discnnected

    UART->BAUDRATE = 0x00275000; //9600 baudrate

    UART->ENABLE = 4;
    UART->TASKS_STARTRX = 1;
}
void uart_send(char letter){
    UART->TXD = letter;
    UART->TASKS_STARTTX = 1;
    while (!UART->EVENTS_TXDRDY); //wait while transmitting
    UART->EVENTS_TXDRDY = 0; //clear event
    UART->TASKS_STOPTX = 1;
}
char uart_read(){
    UART->EVENTS_RXDRDY = 0;
    UART->TASKS_STARTRX = 1;
    return (UART->EVENTS_RXDRDY) ? UART->RXD : 0;
}