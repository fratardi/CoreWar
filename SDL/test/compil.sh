#!/bin/bash
gcc -o executable test.c -g -O2 -I/usr/local/include/SDL2 -I/opt/X11/include -D_THREAD_SAFE -I/usr/X11/include -DHAVE_OPENGL -DHAVE_SDL_TTF -g -lSDL2_test -L/usr/local/lib -lSDL2
