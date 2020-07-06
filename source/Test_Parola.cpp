#include "mbed.h"
#include "MD_Parola.h"
#include "MD_MAX72xx.h"

MD_Parola P(MD_MAX72XX::FC16_HW, PA_7, PA_5, PA_1, 4);

void setup(void)
{
  P.begin();
//  P.displayText("Schalke", PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayScroll("Das ist die Einschaltmeldung.", PA_RIGHT, PA_SCROLL_LEFT, 50);
}

int intensity = 8;
int delta = -1;

void loop(void)
{
    if (P.displayAnimate()) {
        // animation done, restart
        P.displayScroll("Schalke ist der geilste Club der Welt :)", PA_RIGHT, PA_SCROLL_LEFT, 50);
    }

    ThisThread::sleep_for(10ms);
}