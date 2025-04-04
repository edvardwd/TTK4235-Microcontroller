#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2);
}

void LEDmatrix_init(){
    for(int i = 17; i <= 20; i++){
        GPIO->DIRSET = (1 << i);
    }    
}

int main(){
    button_init();
    LEDmatrix_init();
    gpiote_init();
    ppi_init();
    for(;;);

    return 0;
}