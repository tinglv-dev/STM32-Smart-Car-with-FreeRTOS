#include "oled.h"
#include "Car.h"
#include "Ultrasound.h"
#include <stdio.h>

extern uint8_t mode;          // main.c ????
extern uint8_t BuzzerEnable;  // main.c ????,?????

void OLED_ShowStatus(void)
{
    char buf[24];

    OLED_NewFrame();

    // ???:??
    if (mode == 'A')
        OLED_PrintASCIIString(0, 0, "A: Avoid", &afont16x8, OLED_COLOR_NORMAL);
    else if (mode == 'B')
        OLED_PrintASCIIString(0, 0, "B: Track", &afont16x8, OLED_COLOR_NORMAL);
    else
        OLED_PrintASCIIString(0, 0, "0: Manual", &afont16x8, OLED_COLOR_NORMAL);

    // ???:??(?Avoid?????,????)
    if (mode == 'A')
    {
        float distance = Ultrasound_GetDistance();
        sprintf(buf, "Dist: %.1fcm", distance);
        OLED_PrintASCIIString(0, 16, buf, &afont16x8, OLED_COLOR_NORMAL);
    }
    // ????:????,??????(NewFrame?????)

    // ???:????
    sprintf(buf, "Speed: %d", CarSpeed);
    OLED_PrintASCIIString(0, 32, buf, &afont16x8, OLED_COLOR_NORMAL);

    // ???:?????
    OLED_PrintASCIIString(0, 48, BuzzerEnable ? "Buzzer: Open" : "Buzzer: Close", &afont16x8, OLED_COLOR_NORMAL);

    OLED_ShowFrame();
}
