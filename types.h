// Types
#ifndef TYPES_H
#define TYPES_H
typedef struct toaster {
    int x, y, oldX, oldY, frame, speed, frameSpeed, color;
    int frameHeight, frameWidth, maxFrame;
    char *frames[3];
} toaster;

// Toast frames
static char toastFrame0[4] = {102, 102, 102, 102};

// Far Toaster frames
static char farFrame0[4] = {102, 102, 102, 102};;
static char farFrame1[4];
static char farFrame2[4];

// Near Toaster frames
static char nearFrame0[9] = {102, 102, 102, 102, 102, 102, 102, 102, 102};;
static char nearFrame1[9];
static char nearFrame2[9];

#endif //TYPES_H
