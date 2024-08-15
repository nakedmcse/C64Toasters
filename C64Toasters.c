// C64 Flying Toasters
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "c64.h"
#include "types.h"

#define MAXTOASTERS 3
#define SWIDTH 39
#define SHEIGHT 25

void initToasters(toaster *farToaster, toaster *nearToaster, toaster *toast) {
    int i;
    _randomize();
    for(i = 0; i < MAXTOASTERS; i++) {
        farToaster[i].x = rand() % SWIDTH;
        farToaster[i].y = rand() % SHEIGHT;
        farToaster[i].oldX = farToaster[i].x;
        farToaster[i].oldY = farToaster[i].y;
        farToaster[i].speed = 1;
        farToaster[i].frameSpeed = 2;
        farToaster[i].frame = 0;
        farToaster[i].color = (rand() % 15) + 1;
        farToaster[i].frameHeight = 2;
        farToaster[i].frameWidth = 2;
        farToaster[i].maxFrame = 3;
        farToaster[i].frames[0] = farFrame0;
        farToaster[i].frames[1] = farFrame1;
        farToaster[i].frames[2] = farFrame2;

        nearToaster[i].x = rand() % SWIDTH;
        nearToaster[i].y = rand() % SHEIGHT;
        nearToaster[i].oldX = nearToaster[i].x;
        nearToaster[i].oldY = nearToaster[i].y;
        nearToaster[i].speed = 2;
        nearToaster[i].frameSpeed = 1;
        nearToaster[i].frame = 0;
        nearToaster[i].color = (rand() % 15) + 1;
        nearToaster[i].frameHeight = 3;
        nearToaster[i].frameWidth = 3;
        nearToaster[i].maxFrame = 3;
        nearToaster[i].frames[0] = nearFrame0;
        nearToaster[i].frames[1] = nearFrame1;
        nearToaster[i].frames[2] = nearFrame2;

        toast[i].x = rand() % SWIDTH;
        toast[i].y = rand() % SHEIGHT;
        toast[i].oldX = toast[i].x;
        toast[i].oldY = toast[i].y;
        toast[i].speed = 1;
        toast[i].frameSpeed = 0;
        toast[i].frame = 0;
        toast[i].color = C64_COLOR_BROWN;
        toast[i].frameHeight = 1;
        toast[i].frameWidth = 2;
        toast[i].maxFrame = 1;
        toast[i].frames[0] = toastFrame0;
        toast[i].frames[1] = NULL;
        toast[i].frames[2] = NULL;
    }
}

void initScreen() {
    CLRSCR;
    SET_COLORS(C64_COLOR_BLACK,C64_COLOR_BLACK,C64_COLOR_GREEN);
    GRAPHICS_ON;
}

void drawFrame(toaster *target) {
    int i,j,edge,frame;
    edge = target->oldX+target->frameWidth-target->speed;
    frame = target->maxFrame > 1 ? target->frame : 0;
    for(j=0; j<target->frameHeight; j++) {
        for(i=0; i<target->frameWidth; i++) {
            if((target->x+i>=0 && target->x+i<=SWIDTH) && (target->y+j>=0 && target->y+j<=SHEIGHT)) {
                POKE_INK(target->x+i, target->y+j, target->color);
                WRITE_CHAR(target->x+i, target->y+j, target->frames[frame][(j*target->frameWidth)+i]);
            }
        }
        if((edge>=0 && edge<=SWIDTH) && (target->oldY+j>=0 && target->oldY+j<=SHEIGHT)) {
            WRITE_CHAR(edge, target->oldY+j, ' ');
            if(target->speed == 2) {
                WRITE_CHAR(edge+1, target->oldY+j, ' ');
            }
        }
    }
}

void drawToasters(toaster *farToaster, toaster *nearToaster, toaster *toast) {
    int i;
    for(i = 0; i < MAXTOASTERS; i++) {
        drawFrame(&farToaster[i]);
        drawFrame(&toast[i]);
        drawFrame(&nearToaster[i]);
    }
}

void moveToasters(toaster *farToaster, toaster *nearToaster, toaster *toast) {
    int i;
    for(i = 0; i < MAXTOASTERS; i++) {
        farToaster[i].oldX = farToaster[i].x;
        farToaster[i].x -= farToaster[i].speed;
        if(farToaster[i].x < 0-farToaster[i].frameWidth) {
            farToaster[i].x = SWIDTH;
            //farToaster[i].y = rand() % SHEIGHT;
            farToaster[i].color = (rand() % 15) + 1;
        }
        farToaster[i].frame++;
        farToaster[i].frame = farToaster[i].frame % farToaster[i].maxFrame;

        nearToaster[i].oldX = nearToaster[i].x;
        nearToaster[i].x -= nearToaster[i].speed;
        if(nearToaster[i].x < 0-nearToaster[i].frameWidth) {
            nearToaster[i].x = SWIDTH;
            //nearToaster[i].y = rand() % SHEIGHT;
            nearToaster[i].color = (rand() % 15) + 1;
        }
        nearToaster[i].frame++;
        nearToaster[i].frame = nearToaster[i].frame % nearToaster[i].maxFrame;

        toast[i].oldX = toast[i].x;
        toast[i].x -= toast[i].speed;
        if(toast[i].x < 0-toast[i].frameWidth) {
            toast[i].x = SWIDTH;
            //toast[i].y = rand() % SHEIGHT;
        }
    }
}

bool pollInput() {
    unsigned char key, joy1, joy2;
    bool retval = true;

    key = GET_PKEY_VIEW;
    joy1 = GET_JOY1;
    joy2 = GET_JOY2;


    if((joy1 & C64_JOYSTICK_BUTTON) == 0) {
        retval = false;
    }
    if((joy2 & C64_JOYSTICK_BUTTON) == 0) {
        retval = false;
    }

    switch(key) {
        case PKEY_NOKEY: break;
        case PKEY_Q: retval = false; break;
        default: break;
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

    CLRSCR;
    return 0;
}
