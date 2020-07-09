#include "mbed.h"
#include "MD_Parola.h"
#include "MD_MAX72xx.h"

MD_Parola P(MD_MAX72XX::FC16_HW, PA_7, PA_5, PA_1, 4);

char frameBuffer[64];
static int counter = 0;

void setup(void)
{
    P.begin();
    P.setFrameBuffer(frameBuffer, sizeof(frameBuffer));
    P.displayScroll("Das ist die Einschaltmeldung.", PA_RIGHT, PA_SCROLL_LEFT, 50);
}

void loop(void)
{
    if (P.displayAnimate()) {
        // animation done, restart
        P.printf("%i: Schalke ist der geilste Club der Welt :)\n", counter++);
    }

    ThisThread::sleep_for(10ms);
}