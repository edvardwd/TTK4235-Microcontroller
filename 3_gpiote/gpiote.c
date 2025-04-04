#include "gpiote.h"

void gpiote_init(){
	GPIOTE->CONFIG[BTN_1_CH] = ((1 << 0) // Mode: event
							  | (13 << 8) // Pin select: button 13
							  | (2 << 16)); // Polarity: HiToLow

	// Configure LED matrix
	for (int i = 1; i <= 4; i++){
		GPIOTE->CONFIG[i] = ( (3 << 0) // Mode: task
							| ((16 + i) << 8) // Pin select: LED pins
							| (3 << 16) // Polarity: Toggle
							| ((i % 2) << 20)); // Initial light: on half
	}
}