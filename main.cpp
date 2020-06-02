#include "mbed.h"

DigitalIn  btn0(USER_BUTTON, PullUp);
int btnOld;
DigitalOut led1(LED1);
PwmOut servoTurn(PB_10);
PwmOut servoTilt(PB_1);
int posTurn = 1500;
int posTilt = 1500;
int stepSize = 50;

EventQueue *queue;
uint8_t buffer[16+1];

int main() 
{
    printf("Hello from "  MBED_STRINGIFY(TARGET_NAME) "\n");
    printf("Mbed OS version: %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
 
    servoTurn.period_ms(20);
    servoTurn.pulsewidth_us(posTurn);

    servoTilt.period_ms(20);
    servoTilt.pulsewidth_us(posTilt);

    btnOld = btn0;
    // dispatch events
    while(1) {

        int btn = btn0;

        if (btn != btnOld && btn==1) {
            led1 = !led1;
        }
        btnOld = btn;

        char ch = getc(stdin);
        if (ch >= '0' && ch <= '9') {
            //posTurn = (ch - '0') * 100 + 1000;
            stepSize = (ch - '0' + 1) * 10;
        }

        switch (ch) {
            case 's': if (posTurn < 2000) posTurn += stepSize; break;
            case 'd': if (posTurn > 1000) posTurn -= stepSize; break;
            case 'a': if (posTilt < 2000) posTilt += stepSize; break;
            case 'y': if (posTilt > 1000) posTilt -= stepSize; break;
        }
        servoTurn.pulsewidth_us(posTurn);
        servoTilt.pulsewidth_us(posTilt);

        ThisThread::sleep_for(20ms);
        //queue->dispatch(50);
    }
}

