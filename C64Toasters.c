// C64 Flying Toasters
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "c64.h"
#include "types.h"

#define MAXTOASTERS 6
#define SWIDTH 40
#define SHEIGHT 20

void initToasters(toaster *far, toaster *near, toaster *toast) {
    for(int i = 0; i < MAXTOASTERS; i++) {
        far[i].x = rand() % SWIDTH;
        far[i].y = rand() % SHEIGHT;
        far[i].oldX = x;
        far[i].oldY = y;
        far[i].speed = 1;
        far[i].frameSpeed = 2;
        far[i].frame = 0;
        far[i].color = (rand() % 15) + 1;
        //TODO: Char pointer for frames

        near[i].x = rand() % SWIDTH;
        near[i].y = rand() % SHEIGHT;
        near[i].oldX = x;
        near[i].oldY = y;
        near[i].speed = 2;
        near[i].frameSpeed = 1;
        near[i].frame = 0;
        near[i].color = (rand() % 15) + 1;
        //TODO: Char pointer for frames

        toast[i].x = rand() % SWIDTH;
        toast[i].y = rand() % SHEIGHT;
        toast[i].oldX = x;
        toast[i].oldY = y;
        toast[i].speed = 1;
        toast[i].frameSpeed = 0;
        toast[i].frame = 0;
        toast[i].color = C64_COLOR_BROWN;
        //TODO: Char pointer for frame
    }
}

void initScreen() {
    CLRSCR;
    SET_COLORS(C64_COLOR_BLACK,C64_COLOR_BLACK,C64_COLOR_GREEN);
    GRAPHICS_OFF;
}

void drawToasters(toaster *far, toaster *near, toaster *toast) {
    //TODO Implement drawing of toasters
}

void moveToasters(toaster *far, toaster *near, toaster *toast) {
    //TODO Implement movement and animation of toasters
}

bool pollInput() {
    unsigned char key, joy1, joy2;
    bool evalKeyboard = false, retval = true;

    key = GET_PKEY_VIEW;
    joy1 = GET_JOY1;
    joy2 = GET_JOY2;

    // Evaluate joysticks first -- joy1 interferes with the keyboard!
    if((joy1 & C64_JOYSTICK_NONE) == C64_JOYSTICK_NONE) {
        if((joy2 & C64_JOYSTICK_NONE) == C64_JOYSTICK_NONE) evalKeyboard = true;
    }
    else {
        if((joy1 & C64_JOYSTICK_BUTTON) == 0) retval = false;
    }

    if((joy2 & C64_JOYSTICK_NONE) == C64_JOYSTICK_NONE) {
        if((joy1 & C64_JOYSTICK_NONE) == C64_JOYSTICK_NONE) evalKeyboard = true;
    }
    else {
        if((joy2 & C64_JOYSTICK_BUTTON) == 0) retval = false;
    }

    if(evalKeyboard) {
        switch(key) {
        case PKEY_NOKEY: break;
        case PKEY_Q: retval = false; break;
        default: break;
        }
    }

    CLRKEY;
    return retval;
}

int main(void) {
    toaster farToasters[MAXTOASTERS], nearToasters[MAXTOASTERS], toasts[MAXTOASTERS];
    bool isRunning = true;

    initScreen();
    initToasters(&farToasters[0], &nearToasters[0], &toasts[0]);

    // Main Loop
    while(isRunning) {
        drawToasters(&farToasters[0], &nearToasters[0], &toasts[0]);
        moveToasters(&farToasters[0], &nearToasters[0], &toasts[0]);
        isRunning = pollInput();
    }

    return 0;
}
