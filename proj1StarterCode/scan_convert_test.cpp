#include "glsupport.h"
#include "screen_buffer.h"
#include "my_scan_converter.h"

static void initScene(ScreenBuffer * buf)
{
    MyScanConverter msc;
    // //octant 0: slope >= 0 but < 1
    // msc.drawLine(buf, 0, 0, 0, 50);
    // msc.drawLine(buf, 0, 1, 50, 1);
    // msc.drawLine(buf, 0, 10, 50, 20);
    // //octant 1: slope > 1
    // msc.drawLine(buf, 0, 0, 50, 60);
    // msc.drawLine(buf, 0, 10, 30, 80);
    // //octant 2: slope < -1 
    // msc.drawLine(buf, 0, 50, 50, 70);
    // msc.drawLine(buf, 0, 80, 40, 0);
    // //octant 3: slope <= 0 but > -1
    // msc.drawLine(buf, 0, 50, 50, 40);
    // msc.drawLine(buf, 0, 50, 50, 30);

    // cout << "diagonal" << "\n";
    // msc.drawLine(buf, 10, 10, 50, 25);

    // buf -> energizePixel(50, 25, 0.5);
    // buf -> energizePixel(50, 50, 0.5);
    // buf -> energizePixel(50, 10, 0.5);
    msc.drawTriangle(buf, 10, 10, 10, 30, 30, 20);
}

int main(int argc, char **argv)
{
    try {
        glutInit(&argc, argv);

        int pixel_width = 8;
        int pixel_height = 8;
        int buffer_width = 100;
        int buffer_height = 100;

        cout << "screen buffer being constructed" << "\n";
        
        ScreenBuffer * buf = new ScreenBuffer(buffer_width, buffer_height, pixel_width, pixel_height);

        cout << "screen buffer constructed" << "\n";

        glewInit();

        initScene(buf);

        glutMainLoop();
        return 0;
    } catch (const runtime_error& e) {
        cout << "Exception caught: " << e.what() << endl;
        return -1;
    }
}
