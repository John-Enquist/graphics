#ifndef SCREEN_BUFFER_H
#define SCREEN_BUFFER_H

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <tr1/functional>

using namespace std;
using namespace std::tr1;

class ScreenBuffer
{
public:
    ScreenBuffer(int width, int height, int pixel_width, int pixel_height);
    ~ScreenBuffer();
    
    void energizePixel(int x, int y);
    void energizePixel(int x, int y, double intensity);

    void deenergizePixel(int x, int y);

    double getPixelIntensity(int x, int y);

    int getWidth(void) {return this->width;}
    int getHeight(void) {return this->height;}

    void draw(void);


private:
    double ** buffer;
    int width;
    int height;
    int winWidth;
    int winHeight;
    int pixelWidth;
    int pixelHeight;

    void repaint();
    void drawPixel(int x, int y, double intensity);
    void initWindow();
};

#endif
