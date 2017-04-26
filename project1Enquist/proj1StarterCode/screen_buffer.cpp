#include "glsupport.h"

#include <algorithm>
#include <iostream>

#include "screen_buffer.h"



ScreenBuffer::ScreenBuffer(int width, int height, int pixelWidth, int pixelHeight)
{
    buffer = new double*[width];

    for (int i = 0; i < width; i++) {
        buffer[i] = new double[height];
        for (int j = 0; j < height; j++) {
            buffer[i][j] = 0.0;
        }
    }

    this->width = width;
    this->height = height;

    this->pixelWidth = pixelWidth;
    this->pixelHeight = pixelHeight;

    initWindow();
}

ScreenBuffer::~ScreenBuffer()
{
    for (int i = 0; i < width; i++) {
        delete buffer[i];
    }

    delete buffer;
}

static bool inRange(int x, int min, int max)
{
    return (x >= min && x <= max);
}

static bool inRange(double x, double min, double max)
{
    return (x >= min && x <= max);
}

void ScreenBuffer::energizePixel(int x, int y, double intensity)
{
    if (inRange(x, 0, width - 1)
        && inRange(y, 0, height - 1)
        && inRange(intensity, 0.0, 1.0)) {
        buffer[x][y] = intensity;

        repaint();
    }
}

void ScreenBuffer::energizePixel(int x, int y)
{
    energizePixel(x, y, 1.0);
}

void ScreenBuffer::deenergizePixel(int x, int y)
{
    energizePixel(x, y, 0.0);
}

double ScreenBuffer::getPixelIntensity(int x, int y)
{
    return buffer[x][y];
}

void ScreenBuffer::repaint()
{
    glutPostRedisplay();
}


void ScreenBuffer::draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (int x = 0; x < getWidth(); x ++) {
        for (int y = 0; y < getHeight(); y ++) {
            if (getPixelIntensity(x, y) != 0.0) {
                drawPixel(x, y, getPixelIntensity(x, y));
            }
        }
    }
    
    glFlush();
    glutSwapBuffers();
}

void ScreenBuffer::drawPixel(int x, int y, double intensity)
{
    int leftx = x * pixelWidth;
    int rightx = leftx + pixelWidth;
    int bottomy = y * pixelHeight;
    int topy = bottomy + pixelHeight;
    
    int p1 [] = {leftx , bottomy};
    int p2 [] = {leftx , topy};
    int p3 [] = {rightx , topy};
    int p4 [] = {rightx , bottomy};

    // cout << "dimensions of pixel square are: "
    //      << p1[0] << ", " << p1[1]
    //      << " -- "
    //      << p3[0] << ", " << p3[1] << "\n";

    glColor3d(intensity, intensity, intensity);
    glBegin (GL_POLYGON);
        glVertex2iv ( p1 );
        glVertex2iv ( p4 );
        glVertex2iv ( p3 );
        glVertex2iv ( p2 );
    glEnd();

    checkGlErrors();
}

static ScreenBuffer *the_screen_buffer;

static int displaycount = 1;
static void drawScreenBuffer(void)
{
    cout << "Displaying " << displaycount++ << "\n";
    the_screen_buffer->draw();
}

void ScreenBuffer::initWindow()
{
    the_screen_buffer = this;
    winWidth = pixelWidth * getWidth();
    winHeight = pixelHeight * getHeight();
    
    glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("2D Screen Buffer");
    
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D (0.0, winWidth, 0.0, winHeight);
    glClearColor(0.0, 0.0, 0.0, 0.0);

    cout << "window size is "
         << winWidth << " by " << winHeight
         << "\n";
    
    glutDisplayFunc(drawScreenBuffer);
}



