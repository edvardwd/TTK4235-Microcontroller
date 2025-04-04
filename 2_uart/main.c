#include "uart.h"
#include "gpio.h"
#include <stdio.h>
#include <sys/types.h>


ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
    uart_send(*letter);
    letter++;
    }
    return count;
}

ssize_t _read(int fd, void *buf, size_t count){
    char *str = (char *)(buf);
    char letter;
    do {
        letter = uart_read();
    } while(letter == 0);
    *str = letter;
    return 1;
}

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
    GPIO->PIN_CNF[15] = (3 << 2);
    GPIO->PIN_CNF[16] = (3 << 2);
}

int buttonPressed(int button){
	return !(GPIO->IN & (1 << (button + 12)));
}

void triggerLEDMatrix(int on){
	for(int i = 17; i <= 20; i++){
		if (on) GPIO->OUTCLR = (1 << i); // Matrix is active-low
		else GPIO->OUTSET = (1 << i);
	}
}

int main(){
    int LEDon = 0; // Flag to indicate if the LED matrix is on
    for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
        LEDon = 1;
	}

    uart_init();
    button_init();

    int sleep;
    int a, b;
    

    while (1){
        // Send functionality
        if (buttonPressed(1)){
            uart_send('A');
        }
        if (buttonPressed(2)){
            uart_send('B');
        }

        if (buttonPressed(3)){
            iprintf("The average grade in TTK%d in %d was: %c\n\r", 4235, 2022, 'B');
        }

        if (buttonPressed(4)){
            iprintf("Enter one integer:\n\r");
            scanf("%d", &a);
            iprintf("Enter another:\n\r");
            scanf("%d", &b);
            iprintf("%d * %d = %d\n\r", a, b, a*b);
        }

        // Receive functionality
        if (uart_read()){
            triggerLEDMatrix(!LEDon);
            LEDon = !LEDon;
        }

        sleep = 1000000;
		while(--sleep); // Delay
    }


    return 0;
}