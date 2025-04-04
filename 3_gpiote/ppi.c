#include "ppi.h"
#include "gpiote.h"

void ppi_init(){
    for (int i  = 0; i < 4; i++){
        PPI->PPI_CH[i].EEP = (uint32_t)& (GPIOTE->EVENTS_IN[0]); // Link with button 1 event
        PPI->PPI_CH[i].TEP = (uint32_t)& (GPIOTE->TASKS_OUT[1 + i]); // Link with LED task
        PPI->CHENSET = (1 << i); // Activate PPI channel
    }
    
}