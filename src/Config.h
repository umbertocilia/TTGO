#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// Pin definitions
#define TOUCH_CS 21
#define BUTTON_1 35
#define BUTTON_2 0
#define TFT_BL 4
#define ADC_EN 14

// Display power commands
#ifndef TFT_DISPOFF
#define TFT_DISPOFF 0x28
#endif

#ifndef TFT_SLPIN
#define TFT_SLPIN 0x10
#endif

// Frame and button sizes
#define FRAME_X 0
#define FRAME_Y 0
#define FRAME_W 220
#define FRAME_H 110
#define REDBUTTON_X FRAME_X
#define REDBUTTON_Y FRAME_Y
#define REDBUTTON_W (FRAME_W / 2)
#define REDBUTTON_H FRAME_H
#define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
#define GREENBUTTON_Y FRAME_Y
#define GREENBUTTON_W (FRAME_W / 2)
#define GREENBUTTON_H FRAME_H

// Other constants
#define BLACK_SPOT

#endif // CONFIG_H
