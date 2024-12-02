#!/bin/bash
g++ -c src/*.cpp -std=c++14 -O3 -Wall -m64 -I include -I C:/tools/SDL2-2.30.9/x86_64-w64-mingw32/include
g++ *.o -o bin/release/main -s -L C:/tools/SDL2-2.30.9/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
#g++ -static-libgcc -static-libstdc++ *.o -o bin/release/main -s -L C:/tools/SDL2-2.30.9/x86_64-w64-mingw32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
start bin/release/main