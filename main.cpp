#include "mbed.h"

DigitalOut led1(LED1);

EventQueue *queue;
uint8_t buffer[16+1];

int main() 
{
    // dispatch events
    while(1) {
        led1 = !led1;
        ThisThread::sleep_for(200ms);
        //queue->dispatch(50);
    }
}

