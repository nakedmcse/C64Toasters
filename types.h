// Types
#ifndef TYPES_H
#define TYPES_H
typedef struct toaster {
    int x, y, oldX, oldY, frame, speed, frameSpeed, color;
    int frameHeight, frameWidth, maxFrame;
    char *frames[3];
} toaster;

// Toast frames
static char toastFrame0[6] = {102, 102, '\n', 102, 102, 0};

// Far Toaster frames
static char farFrame0[6];
static char farFrame1[6];
static char farFrame2[6];

// Near Toaster frames
static char nearFrame0[6];
static char nearFrame1[6];
static char nearFrame2[6];

#endif //TYPES_H
