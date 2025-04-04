#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1[118]; // Reserved = (0x700 - 0x528) / 4
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
}

void triggerLEDMatrix(int on){
	for(int i = 17; i <= 20; i++){
		if (on) GPIO->OUTCLR = (1 << i); // Matrix is active-low
		else GPIO->OUTSET = (1 << i);
	}
}

int buttonPressed(int button){
	return !(GPIO->IN & (1 << (button + 12)));
}

int main(){
	// Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTSET= (1 << i);
	}

	// Configure buttons -> see button_init()
	button_init();
	int sleep = 0;
	while(1){

		/* Check if button 1 is pressed;
		 * turn on LED matrix if it is. */
		if (buttonPressed(1)) triggerLEDMatrix(1);
		//triggerLEDMatrix(1);

		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */
		if (buttonPressed(2)) triggerLEDMatrix(0);
		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}
