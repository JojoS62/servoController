#include "mbed.h"

DigitalOut led1(LED1);


int main() {
    
	while (true) {
		
		led1 = 0;
		
        wait_ms(100);

        led1 = 1;
		
        wait_ms(100);
    }
}

