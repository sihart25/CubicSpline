//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Cubic Spline Assessment
// Display.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#pragma hdrstop
#include "Display.h"
#include "Control.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// static data member
Control *Display::_control = 0;

//------------------------------------------------------------------------------
// initialize
void Display::init(int argc, char **argv) {
    try {
        _control = new Control();
        // initialise OpenGL
        glutInit(&argc, argv);
        glutInitWindowPosition(0, 0);
        glutInitWindowSize(WIDTH, HEIGHT);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutCreateWindow("Mandelbrot Set");
        glutDisplayFunc(Display::display);
        glutReshapeFunc(Display::reshape);
        glutKeyboardFunc(Display::keyboard);
        glutMouseFunc(Display::mouse);
        glutMotionFunc(Display::motion);
        glutSpecialFunc(Display::special);
        glutIdleFunc(Display::idle);
        // initialise control
        _control->init(argc, argv);
        // call GLUT main loop
        glutMainLoop();
    }
    catch (...) {
        cout << "Error : Unknown exception caught in display" << endl;
    }
    delete _control;
}

//------------------------------------------------------------------------------
