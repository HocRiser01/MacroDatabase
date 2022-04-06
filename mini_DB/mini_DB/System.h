#pragma once

#if (defined _WIN64) || (defined _WIN32)
#include <conio.h>
#else
#include <termios.h>
int getch();
#endif

void cls();

void pause();

void Closefile();
