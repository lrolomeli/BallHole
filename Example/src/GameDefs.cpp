#include "GameDefs.h"

Color color[5] = {{RGB_BLACK},{RGB_WHITE},{RGB_RED},{RGB_GREEN},{RGB_BLUE}};

Color* getColor(Colors c) {
    return &color[c];
}