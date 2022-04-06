#include <cstdio>
#include <cstdlib>
#include "System.h"

#if (defined _WIN64) || (defined _WIN32)

void cls(){
    system("cls");
}

void Closefile(){
    fclose(stdin);
    freopen("CON", "r", stdin);
}

#else

int getch(){
    struct termios tm, tm_old;
    int fd = 0, ch;
    if (tcgetattr(fd, &tm) < 0) {
        return -1;
    }
    tm_old = tm;
    cfmakeraw(&tm);
    if (tcsetattr(fd, TCSANOW, &tm) < 0) {
        return -1;
    }
    ch = getchar();
    if (tcsetattr(fd, TCSANOW, &tm_old) < 0) {
        return -1;
    }
    return ch;
}

void cls(){
    system("clear");
}

void Closefile(){
    fclose(stdin);
    freopen("/dev/tty", "r", stdin);
}

#endif

void pause(){
    getch();
}
