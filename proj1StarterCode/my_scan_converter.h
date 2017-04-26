#ifndef MY_SCAN_CONVERTER_H
#define MY_SCAN_CONVERTER_H

#include "scan_converter.h"
#include "screen_buffer.h"

class MyScanConverter : ScanConverter
{
public:
    virtual void drawLine(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend);
    void drawTriangle(ScreenBuffer *buf, int x0, int y0, int x1, int y1, int x2, int y2);

private:
    void drawLineOctZero(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend);
    void drawLineOctOne(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend);
    void drawLineOctTwo(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend);
    void drawLineOctThree(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend);
    int octantFinder(float slope);
    int convertToOctantZeroX(int octant, int x, int y);
    int convertToOctantZeroY(int octant, int x, int y);
    int convertToOriginalOctantX(int octant, int x, int y);
    int convertToOriginalOctantY(int octant, int x, int y);
};

#endif
