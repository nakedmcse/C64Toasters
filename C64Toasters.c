// C64 Flying Toasters
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "c64.h"
#include "types.h"

#define MAXTOASTERS 4
#define SWIDTH 39
#define SHEIGHT 24
#define INRANGE(x, low, high) \
x>=low && x<=high

void initToasters(toaster *farToaster, toaster *nearToaster) {
    int i;
    _randomize();
    for(i = 0; i < MAXTOASTERS; i++) {
        farToaster[i].x = rand() % SWIDTH;
        farToaster[i].y = (rand() % (SHEIGHT - 2))+1;
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
        nearToaster[i].y = (rand() % (SHEIGHT - 3))+1;
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
    }
}

void initScreen() {
    CLRSCR;
    SET_COLORS(C64_COLOR_BLACK,C64_COLOR_BLACK,C64_COLOR_GREEN);
    GRAPHICS_ON;
}

bool checkLayerCollision(int x, int y, toaster *layer) {
    int i;
    if(layer == NULL) {
        return false;
    }
    for(i = 0; i < MAXTOASTERS; i++) {
        if(INRANGE(x, layer[i].x, layer[i].x+layer[i].frameWidth)
            && INRANGE(y, layer[i].y, layer[i].y+layer[i].frameHeight)) {
            return true;
        }
    }
    return false;
}

void drawFrame(toaster *target, toaster *prevLayer) {
    int i,j,edge,frame;
    edge = target->oldX+target->frameWidth-target->speed;
    frame = target->maxFrame > 1 ? target->frame : 0;
    for(j=0; j<target->frameHeight; j++) {
        for(i=0; i<target->frameWidth; i++) {
            if(checkLayerCollision(target->x+i, target->y+j, prevLayer)) {
                continue;
            }
            if((INRANGE(target->x+i, 0, SWIDTH)) &&
                (INRANGE(target->y+j, 0, SHEIGHT))) {
                POKE_INK(target->x+i, target->y+j, target->color);
                WRITE_CHAR(BASE_SCREEN_ADDRESS, target->x+i, target->y+j, target->frames[frame][(j*target->frameWidth)+i]);
            }
        }
        if((INRANGE(edge, 0, SWIDTH)) && (INRANGE(target->oldY+j, 0, SHEIGHT))) {
            WRITE_CHAR(BASE_SCREEN_ADDRESS, edge, target->oldY+j, ' ');
            if(target->speed == 2) {
                WRITE_CHAR(BASE_SCREEN_ADDRESS, edge+1, target->oldY+j, ' ');
            }
        }
    }
}

void drawToasters(toaster *farToaster, toaster *nearToaster) {
    int i;
    for(i = 0; i < MAXTOASTERS; i++) {
        drawFrame(&nearToaster[i], NULL);
    }
    for(i = 0; i < MAXTOASTERS; i++) {
        drawFrame(&farToaster[i], &nearToaster[0]);
    }
}

void moveToasters(toaster *farToaster, toaster *nearToaster) {
    int i;
    for(i = 0; i < MAXTOASTERS; i++) {
        farToaster[i].oldX = farToaster[i].x;
        farToaster[i].oldY = farToaster[i].y;
        farToaster[i].x -= farToaster[i].speed;
        if(farToaster[i].x < 0-farToaster[i].frameWidth) {
            farToaster[i].x = SWIDTH;
            farToaster[i].y = (rand() % (SHEIGHT - farToaster[i].frameHeight))+1;
            farToaster[i].color = (rand() % 15) + 1;
        }
        farToaster[i].frame++;
        farToaster[i].frame = farToaster[i].frame % farToaster[i].maxFrame;

        nearToaster[i].oldX = nearToaster[i].x;
        nearToaster[i].oldY = nearToaster[i].y;
        nearToaster[i].x -= nearToaster[i].speed;
        if(nearToaster[i].x < 0-nearToaster[i].frameWidth) {
            nearToaster[i].x = SWIDTH;
            nearToaster[i].y = (rand() % (SHEIGHT - nearToaster[i].frameHeight))+1;
            nearToaster[i].color = (rand() % 15) + 1;
        }
        nearToaster[i].frame++;
        nearToaster[i].frame = nearToaster[i].frame % nearToaster[i].maxFrame;
    }
}

bool pollInput() {
    unsigned char key, joy1, joy2;

    key = GET_PKEY_VIEW;
    joy1 = GET_JOY1;
    joy2 = GET_JOY2;


    if((joy1 & C64_JOYSTICK_BUTTON) == 0) {
        return false;
    }
    if((joy2 & C64_JOYSTICK_BUTTON) == 0) {
        return false;
    }

    switch(key) {
        case PKEY_NOKEY: break;
        case PKEY_Q: return false; break;
        default: break;
    }

    CLRKEY;
    return true;
}

int main(void) {
    toaster farToasters[MAXTOASTERS], nearToasters[MAXTOASTERS];
    bool isRunning = true;

    initScreen();
    initToasters(&farToasters[0], &nearToasters[0]);

    // Main Loop
    while(isRunning) {
        drawToasters(&farToasters[0], &nearToasters[0]);
        moveToasters(&farToasters[0], &nearToasters[0]);
        isRunning = pollInput();
    }

    CLRSCR;
    return 0;
}
