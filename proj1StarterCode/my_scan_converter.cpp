#include "my_scan_converter.h"

#include <iostream>


int MyScanConverter::octantFinder(float slope)
{
    if (slope > 1) {
        return 1;
    }
    if (slope > 0 && slope <= 1) {
        return 0;
    }
    if (slope <= 0 && slope > -1) {
        return 3;
    }
    if (slope < -1) {
        return 2;
    }
}

int MyScanConverter::convertToOctantZeroX(int octant, int x, int y)
{
     if (octant == 0){
        return x;
     }
     if (octant == 1){
        return y;
     }
     if (octant == 2){
        return y;
     }
     if (octant == 3){
        return -x;
     }
}

int MyScanConverter::convertToOctantZeroY(int octant, int x, int y)
{
     if (octant == 0){
        return y;
     }
     if (octant == 1){
        return x;
     }
     if (octant == 2){
        return -x;
     }
     if (octant == 3){
        return y;
     }
}

int MyScanConverter::convertToOriginalOctantX(int octant, int x, int y)
{
    if (octant == 0){
        return x;
     }
     if (octant == 1){
        return y;
     }
     if (octant == 2){
        return -y;
     }
     if (octant == 3){
        return -x;
     }
}

int MyScanConverter::convertToOriginalOctantY(int octant, int x, int y)
{
    if (octant == 0){
        return y;
     }
     if (octant == 1){
        return x;
     }
     if (octant == 2){
        return x;
     }
     if (octant == 3){
        return y;
     }
}

void MyScanConverter::drawLine(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend)
{
    // setting up initial x and y variables 
    int xs = xbegin;
    int ys = ybegin;
    int xe = xend;
    int ye = yend; 
    // this if is to account for lines with negative which would be drawn backwards by swapping the
    // start and end coordinates. getting rid of octants 4-7
    if (xbegin > xend) {
        xs = xend;
        ys = yend;
        xe = xbegin;
        ye = ybegin;
    }
    int dx = xe - xs;
    int dy = ye - ys;
    float slope = dy / (float)dx;
    int octant = octantFinder(slope);
    buf -> energizePixel(xs, ys);

    cout << "octant is " << octant << "\n";

    if (octant == 0) {
        drawLineOctZero(buf, xs, ys, xe, ye);
    }
    if (octant == 1) {
        drawLineOctOne(buf, xs, ys, xe, ye);
    }
    if (octant == 2) {
        drawLineOctTwo(buf, xs, ys, xe, ye);
    }
    if (octant == 3) {
        drawLineOctThree(buf, xs, ys, xe, ye);
    }

}

void MyScanConverter::drawLineOctZero(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend)
{
    int dx = xend - xbegin;
    int dy = yend - ybegin;
    int pk = 2*(dy - dx);
    int currentX = xbegin;
    int currentY = ybegin;
    if (pk > 0) {
        currentY = currentY + 1;
        pk = pk - (2 * dx);
    }
    for (int x = (currentX + 1); x != xend; x++) {
        buf -> energizePixel(x, currentY);
        pk = pk + (2*dy);
        if (pk > 0) {
            currentY = currentY + 1;
            pk = pk - (2 * dx);
        } 
    }
}

void MyScanConverter::drawLineOctOne(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend)
{
    int dx = xend - xbegin;
    int dy = yend - ybegin;
    int pk = 2*(dx - dy);
    int currentX = xbegin;
    int currentY = ybegin;
    if (pk > 0) {
        currentX = currentX + 1;
        pk = pk - (2 * dy);
    }
    for (int y = (currentY + 1); y != yend; y++) {
        buf -> energizePixel(currentX, y);
        pk = pk + (2*dx);
        if (pk > 0) {
            currentX = currentX + 1;
            pk = pk - (2 * dy);
        } 
    }

}

void MyScanConverter::drawLineOctTwo(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend)
{
    int dx = xend - xbegin;
    int dy = ybegin - yend;
    int pk = 2*(dx - dy);
    int currentX = xbegin;
    int currentY = ybegin;
    if (pk > 0) {
        currentX = currentX + 1;
        pk = pk - (2 * dy);
    }
    for (int y = (currentY - 1); y != yend; y--) {
        buf -> energizePixel(currentX, y);
        pk = pk + (2*dx);
        if (pk > 0) {
            currentX = currentX + 1;
            pk = pk - (2 * dy);
        } 
    }    
}

void MyScanConverter::drawLineOctThree(ScreenBuffer *buf, int xbegin, int ybegin, int xend, int yend)
{
    int dx = xend - xbegin;
    int dy = ybegin - yend;
    int pk = 2*(dx - dy);
    int currentX = xbegin;
    int currentY = ybegin;
    if (pk > 0) {
        currentY = currentY - 1;
        pk = pk - (2 * dx);
    }
    for (int x = (currentX + 1); x != xend; x++) {
        buf -> energizePixel(x, currentY);
        pk = pk + (2*dy);
        if (pk > 0) {
            currentY = currentY - 1;
            pk = pk - (2 * dx);
        } 
    }
}

void MyScanConverter::drawTriangle(ScreenBuffer *buf, int x0, int y0, int x1, int y1, int x2, int y2)
{
    drawLine(buf, x0, y0, x1, y1);
    drawLine(buf, x0, y0, x2, y2);
    drawLine(buf, x1, y1, x2, y2);
}



