#include "GameDefs.h"

Color color[7] = {{RGB_BLACK},{RGB_WHITE},{RGB_RED},{RGB_GREEN},{RGB_BLUE},{RGB_GRAY},{RGB_DARK_GRAY}};

Color* getColor(Colors c) {
    return &color[c];
}