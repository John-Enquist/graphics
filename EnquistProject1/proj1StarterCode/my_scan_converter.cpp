#include "my_scan_converter.h"

#include <iostream>

void MyScanConverter::drawLine(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend)
{
    if (xend < xbegin) {
        int lowx = xend;
        xend = xbegin;
        xbegin = lowx;
    }
    if (yend < ybegin) {
        int lowy = yend;
        yend = ybegin;
        ybegin = lowy;
    }

    double dx = xend - xbegin;
    double dy = yend - ybegin;

    if (dx == 0) {
        for (int y = ybegin; y <= yend; y++) {
            buf -> energizePixel(xbegin, y);
        }
    } else {
        for (int x = xbegin; x <= xend; x++) {
            int y = ybegin + dy * (x - xbegin) / dx;
            buf -> energizePixel(x, y);
        }
    }
}

