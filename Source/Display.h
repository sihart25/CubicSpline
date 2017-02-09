//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Cubic Spline Assessment
// Display.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Display_h
#define Display_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Control.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Display {

    public:

        static void init(int argc, char **argv);

    private:

        static void display() {
            if (_control) _control->display();
        }
        static void reshape(int width, int height) {
            if (_control) _control->reshape(width, height);
        }
        static void keyboard(unsigned char key, int x, int y) {
            if (_control) _control->keyboard(key, x, y);
        }
        static void mouse(int button, int state, int x, int y) {
            if (_control) _control->mouse(button, state, x, y);
        }
        static void motion(int x, int y) {
            if (_control) _control->motion(x, y);
        }
        static void special(int key, int x, int y) {
            if (_control) _control->special(key, x, y);
        }
        static void idle() {
            if (_control) _control->idle();
        }
        static Control *_control;

    };

} // ComputerGraphics

#endif // Display_h

//------------------------------------------------------------------------------
