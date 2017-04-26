#ifndef SCAN_CONVERTER_H
#define SCAN_CONVERTER_H

#include "screen_buffer.h"

class ScanConverter
{
public:
    virtual void drawLine(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend) = 0;
};

#endif
