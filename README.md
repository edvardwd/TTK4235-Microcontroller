# TTK4235 - Embedded Systems - Microcontroller lab
Group members: 
- Edvard Wekre Dingsør
- Havan Palo Darbandi

## Simple C project on a nRF52832 microcontroller
The project tries to answer the tasks described in the TTK4235 microcontroller lab description.

### Contents
| Folder | Description |
|:------ | :---------- |
| 1_gpio |Button 1 turns on the LED matrix and button 2 turns it off.|  
| 2_uart |Button 1 and 2 sends respectively 'A' and 'B' to the computer. Button 3 prints a message. Button 4 performs a multiplication.|
|3_gpiote|Button 1 toggles the LED matrix without CPU usage.|

### How to run
1. Clone this repository.
2. Make sure to have the [nRF52DK Development Environment](https://github.com/ITK-TTK4235/nrf52dk-environment) set up.
3. Navigate to the desired folder.
4. Plug in the nRF52832 microcontroller and turn it on.
5. For first time use, run 
```
make recover
make 
make flash
```

after first time use, you can skip "make recover".
* On task 2, also run 
```
picocom -b 9600 /dev/ttyACMx
```
in the terminal, where x should be swapped with either 0, 1 or 2. After that you can interact with the microcontroller through the computer.