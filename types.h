// Types
#ifndef TYPES_H
#define TYPES_H
typedef struct toaster {
    int x, y, oldX, oldY, frame, speed, frameSpeed, color;
    int frameHeight, frameWidth, maxFrame;
    char *frames[3];
} toaster;

// Far Toaster frames
static char farFrame0[4] = {112, 110, 109, 125};
static char farFrame1[4] = {112, 47, 109, 125};
static char farFrame2[4] = {112, 45, 109, 125};

// Near Toaster frames
static char nearFrame0[9] = {79, 119, 80, 101, 87, 103, 76, 82, 122};
static char nearFrame1[9] = {79, 119, 47, 101, 47, 103, 76, 82, 122};
static char nearFrame2[9] = {79, 119, 80, 101, 45, 45, 76, 82, 122};

#endif //TYPES_H
