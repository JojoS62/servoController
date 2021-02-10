#include "mbed.h"
#include "console.h"
#include "Test_MAX72xx.h"

DigitalIn  btn0(USER_BUTTON, PullUp);
int btnOld;
DigitalOut led1(LED1);
PwmOut servoTurn(PB_10);
PwmOut servoTilt(PB_1);
int posTurn = 1500;
int posTilt = 1500;
int stepSize = 50;

EventQueue *queue = mbed_event_queue(); // shared event queue;
uint8_t buffer[32+1];
uint8_t *bufptr = buffer;

BufferedSerial  serial(STDIO_UART_TX, STDIO_UART_RX, 115200);

//Console console(&serial);

void messageComplete()
{
    led1 = !led1;
    printf("message: %s\n", buffer);
    bufptr = buffer;

    switch (buffer[0]) {
        case 's': if (posTurn > 1000) posTurn -= stepSize; break;
        case 'd': if (posTurn < 2000) posTurn += stepSize; break;
        case 'a': if (posTilt > 1000) posTilt -= stepSize; break;
        case 'y': if (posTilt < 2000) posTilt += stepSize; break;
    }
}

void on_rx_interrupt()
{
    int nbytes = serial.read(bufptr, 1);
    bufptr += nbytes;
    if (bufptr[-1] == '\n' || bufptr[-1] == '\r') {
        *bufptr = '\0';
        queue->call(messageComplete);
    }
}

int main() 
{
    printf("Moin from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
 
    serial.set_blocking(false);
    
    servoTurn.period_ms(20);
    servoTurn.pulsewidth_us(posTurn);

    servoTilt.period_ms(20);
    servoTilt.pulsewidth_us(posTilt);

    setup();
    while(true) {
        char buffer;

        loop();
        int nbytes = serial.read(&buffer, 1); 
        if (nbytes > 0) {
            switch (buffer) {
                case 's': if (posTurn > 1000) posTurn -= stepSize; break;
                case 'd': if (posTurn < 2000) posTurn += stepSize; break;
                case 'a': if (posTilt > 1000) posTilt -= stepSize; break;
                case 'y': if (posTilt < 2000) posTilt += stepSize; break;
                case '0': posTurn = 1500; posTilt = 1500; break;
            }

            servoTurn.pulsewidth_us(posTurn);
            servoTilt.pulsewidth_us(posTilt);
        }

    }

    btnOld = btn0;
    // dispatch events
    while(1) {

        int btn = btn0;

        if (btn != btnOld && btn==1) {
            led1 = !led1;
        }
        btnOld = btn;

#if 0
        char ch = getc(stdin);
        if (ch >= '0' && ch <= '9') {
            //posTurn = (ch - '0') * 100 + 1000;
            stepSize = (ch - '0' + 1) * 10;
        }

        switch (ch) {
            case 's': if (posTurn > 1000) posTurn -= stepSize; break;
            case 'd': if (posTurn < 2000) posTurn += stepSize; break;
            case 'a': if (posTilt > 1000) posTilt -= stepSize; break;
            case 'y': if (posTilt < 2000) posTilt += stepSize; break;
        }
#endif

        //queue->dispatch(20);
        //console.process();      // blocking for now

        servoTurn.pulsewidth_us(posTurn);
        servoTilt.pulsewidth_us(posTilt);

        //ThisThread::sleep_for(20ms);
        //ThisThread::sleep_for(2s);
        //queue->dispatch(50);
    }
}

