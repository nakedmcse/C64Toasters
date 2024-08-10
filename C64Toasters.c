// C64 Flying Toasters
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "c64.h"
#include "types.h"

#define MAXTOASTERS 6

int main(void) {
    toaster farToasters[MAXTOASTERS], nearToasters[MAXTOASTERS], toasts[MAXTOASTERS];
    bool isRunning = true;

    // Init Screen
    CLRSCR;
    SET_COLORS(C64_COLOR_BLACK,C64_COLOR_BLACK,C64_COLOR_GREEN);
    GRAPHICS_OFF;

    // Init Toasters

    // Main Loop
    while(isRunning) {
        // Draw Far Toasters
        // Draw Toast
        // Draw Near Toasters
        // Move Far Toasters
        // Move Toast
        // Move Near Toasters
        // Poll Keyboard for quit
    }

    return 0;
}
