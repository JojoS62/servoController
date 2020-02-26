#include "mbed.h"

//RawSerial com1(PA_2, PA_3, 115200);
RawSerial com2(PA_2, PA_3, 115200);
RawSerial com1(PB_6, PB_7, 115200);

DigitalOut led1(LED1);

EventQueue *queue;
uint8_t buffer[16+1];

void rxEvent(int);

void startReading() {
    com1.read(buffer, sizeof(buffer)-1, 
              callback(rxEvent), 
              SERIAL_EVENT_RX_COMPLETE | SERIAL_EVENT_RX_CHARACTER_MATCH, 
              '\n');
}

void printMessage(const char* evtText) {
    com2.puts(evtText);

    com2.puts((const char*)buffer);
    com2.puts("\n");

    startReading();
}

void rxEvent(int serialEvent) {
    led1 = !led1;
   
    if (serialEvent & SERIAL_EVENT_RX_COMPLETE) {
        buffer[sizeof(buffer)-1] = 0;
        queue->call(printMessage, "complete\n");
    } else if (serialEvent & SERIAL_EVENT_RX_CHARACTER_MATCH) {
        *strchr((const char*)buffer, '\n') = 0;
        queue->call(printMessage, "Bingo!\n");
    }
}

int main() 
{
    com1.printf("hello world\n");

    queue = mbed_event_queue();

    com1.puts("Hello com1\n");
    com2.puts("Hello com2\n");

    // start reading from com1
    startReading();

    // dispatch events
    while(1) {
        led1 = !led1;
        queue->dispatch(50);
    }
}

