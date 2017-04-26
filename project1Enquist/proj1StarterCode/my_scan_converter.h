#ifndef MY_SCAN_CONVERTER_H
#define MY_SCAN_CONVERTER_H

#include "scan_converter.h"
#include "screen_buffer.h"

class MyScanConverter : ScanConverter
{
public:
    virtual void drawLine(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend);
};

#endif
