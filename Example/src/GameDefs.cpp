#include "GameDefs.h"

Color color[6] = {{RGB_BLACK},{RGB_WHITE},{RGB_RED},{RGB_GREEN},{RGB_BLUE},{RGB_GRAY}};

Color* getColor(Colors c) {
    return &color[c];
}