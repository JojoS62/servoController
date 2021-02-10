#include "mbed.h"
#include "MD_Parola.h"
#include "MD_MAX72xx.h"

MD_Parola P(MD_MAX72XX::FC16_HW, PA_7, PA_5, PA_1, 4);
DigitalIn   touchBtn(PB_13, PullUp);
DigitalOut  touchLED(PB_9);

char frameBuffer[64];
static int counter = 0;

void setup(void)
{
    P.begin();
    P.setFrameBuffer(frameBuffer, sizeof(frameBuffer));
    P.displayScroll("Hallo, Das ist die Einschaltmeldung.", PA_RIGHT, PA_SCROLL_LEFT, 50);
    while (!P.displayAnimate()) { 
        ThisThread::sleep_for(10ms); 
    }
    P.printf("Und die zweite Meldung.\n");
}

void loop(void)
{ 
    
    if (P.displayAnimate()) {
        // animation done, restart
        P.printf("%i: Schalke ist der geilste Club der Welt :)\n", counter++);
        P.setTextEffect(PA_SCROLL_LEFT, PA_SCROLL_LEFT);
    }

    touchLED = touchBtn.read();

    //ThisThread::sleep_for(10ms);
}