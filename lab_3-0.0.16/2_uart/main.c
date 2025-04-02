#include "uart.h"
#include "gpio.h"


void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
}

int buttonPressed(int button){
	return !(GPIO->IN & (1 << (button + 12)));
}
void triggerLEDMatrix(int on){
	for(int i = 17; i <= 20; i++){
		if (on) GPIO->OUTCLR = (1 << i); //matrix is active-low
		else GPIO->OUTSET = (1 << i);
	}
}

int main(){

    int sleep;
    for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTSET= (1 << i);
	}
    button_init();
    uart_init();

    while (1){
        if (buttonPressed(1)){
            uart_send('A');
            triggerLEDMatrix(1);
        }
        if (buttonPressed(2)){
            uart_send('b');
            triggerLEDMatrix(0);
        }

        sleep = 10000;
		while(--sleep); // Delay
    }


    return 0;
}