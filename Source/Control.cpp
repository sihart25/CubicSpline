//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Cubic Spline Assessment
// Control.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <GL/glut.h>
#pragma hdrstop
#include "Control.h"
#include "Constants.h"
#include "Test.h"
#include "Spiral.h"
#include "Clover.h"
#include "Circle.h"
#include "Sphere.h"
#include "Torus.h"
#include "Helix.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// init
void Control::init(int argc, char **argv) {
    // display menu
    cout << "Press <escape>          to exit program" << endl;
    cout << "Press <f1>              to select dimensions" << endl;
    cout << "Press <f2>              to select test" << endl;
    cout << "Press <f3>              to select spiral" << endl;
    cout << "Press <f4>              to select clover" << endl;
    cout << "Press <f5>              to select circle" << endl;
    cout << "Press <f6>              to select helix" << endl;
    cout << "Press <f7>              to select torus" << endl;
    cout << "Press <f8>              to select sphere" << endl;
    cout << "Press <f9>              to change position with mouse" << endl;
    cout << "Press <f10>             to change time with mouse" << endl;
    cout << "Press <f11>             to change second derivative with mouse" << endl;
    cout << "Press <1>               to select markers" << endl;
    cout << "Press <2>               to play or stop animation" << endl;
    cout << "Press <3>               to play or stop spin" << endl;
    cout << "Press <4>               to play or pause spin" << endl;
    cout << "Press <5>               to select spin axis" << endl;
    cout << "Press <6>               to read files" << endl;
    cout << "Press <7>               to write files" << endl;
    cout << "Press <enter>           to clear points" << endl;
    cout << "Press <insert>          to insert point" << endl;
    cout << "Press <delete>          to delete point" << endl;
    cout << "Press <left> or <down>  to select previous point" << endl;
    cout << "Press <right> or <up>   to select next point" << endl;
    cout << "Press <home>            to select first point" << endl;
    cout << "Press <end>             to select last point" << endl;
    cout << "Press left mouse button and move to change x and y coordinates" << endl;
    cout << "Press right mouse button and move to change z coordinate" << endl;
    // initialize OpenGL
    glutReshapeWindow(WIDTH, HEIGHT);
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepth(1.0);
    // initialize splines
    _test.setup(_spline1D, "../Data/Test.txt");
    _circle.setup(_spline2D);
    _sphere.setup(_spline3D);
}

//------------------------------------------------------------------------------
// display
void Control::display() {
    time_t start;
    start = clock();
    // plot spline
    double aspectRatio = (double)glutGet(GLUT_WINDOW_WIDTH) / (double)glutGet(GLUT_WINDOW_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (_dimension) {
        case DIM_1D: {
            _spline1D.plot(_markers, _animation);
            break;
        }
        case DIM_2D: {
            _spline2D.plot(_markers, _animation);
            break;
        }
        case DIM_3D: {
            _spline3D.plot(_markers, _animation);
            break;
        }
    }
    // report time and status
    time_t finish;
    finish = clock();
    ostringstream oss;
    oss << setiosflags(ios::fixed) << setprecision(3);
    oss << "Cubic Spline - ";
    switch (_dimension) {
        case DIM_1D: {
            oss << "One Dimension - ";
            break;
        }
        case DIM_2D: {
            oss << "Two Dimensions - ";
            break;
        }
        case DIM_3D: {
            oss << "Three Dimensions - ";
            break;
        }
    }
    oss << (double)(finish - start) / (double)CLOCKS_PER_SEC << " seconds";
    glutSetWindowTitle(oss.str().c_str());
    glutSwapBuffers();
}

//------------------------------------------------------------------------------
// reshape
void Control::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(atan(1.0 / 4.0) * RAD_2_DEG * 2.0, 1.0, 0.1, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glutPostRedisplay();
}

//------------------------------------------------------------------------------
// keyboard
void Control::keyboard(unsigned char key, int /*x*/, int /*y*/) {
    switch (key) {
        case '1': {
            _markers = !_markers;
            break;
        }
        case '2': {
            _animation = !_animation;
            break;
        }
        case '3': {
            _spline3D.stop();
            break;
        }
        case '4': {
            _spline3D.play();
            break;
        }
        case '5': {
            _spline3D.spin();
            break;
        }
        case '6': {
            _spline1D.read("../Data/Spline1D.txt");
            _spline2D.read("../Data/Spline2D.txt");
            _spline3D.read("../Data/Spline3D.txt");
            break;
        }
        case '7': {
            _spline1D.write("../Data/Spline1D.txt");
            _spline2D.write("../Data/Spline2D.txt");
            _spline3D.write("../Data/Spline3D.txt");
            break;
        }
        case 0x0D: {
            switch (_dimension) {
                case DIM_1D: {
                    _spline1D.clear();
                    break;
                }
                case DIM_2D: {
                    _spline2D.clear();
                    break;
                }
                case DIM_3D: {
                    _spline3D.clear();
                    break;
                }
            }
            break;
        }
        case 0x7F: {
            switch (_dimension) {
                case DIM_1D: {
                    _spline1D.remove();
                    break;
                }
                case DIM_2D: {
                    _spline2D.remove();
                    break;
                }
                case DIM_3D: {
                    _spline3D.remove();
                    break;
                }
            }
            break;
        }
        case 0x1B: {
            glutDestroyWindow(glutGetWindow());
            delete this;
            exit(0);
        }
    }
}

//------------------------------------------------------------------------------
// special
void Control::special(int key, int /*x*/, int /*y*/) {
    switch (key) {
        case GLUT_KEY_F1: {
            switch (_dimension) {
                case DIM_1D: {
                    _dimension = DIM_2D;
                    break;
                }
                case DIM_2D: {
                    _dimension = DIM_3D;
                    break;
                }
                case DIM_3D: {
                    _dimension = DIM_1D;
                    break;
                }
            }
            break;
        }
        case GLUT_KEY_F2: {
            _dimension = DIM_1D;
            _test.setup(_spline1D, "../Data/Test.txt");
            break;
        }
        case GLUT_KEY_F3: {
            _dimension = DIM_2D;
            _spiral.setup(_spline2D);
            break;
        }
        case GLUT_KEY_F4: {
            _dimension = DIM_2D;
            _clover.setup(_spline2D);
            break;
        }
        case GLUT_KEY_F5: {
            _dimension = DIM_2D;
            _circle.setup(_spline2D);
            break;
        }
        case GLUT_KEY_F6: {
            _dimension = DIM_3D;
            _helix.setup(_spline3D);
            break;
        }
        case GLUT_KEY_F7: {
            _dimension = DIM_3D;
            _torus.setup(_spline3D);
            break;
        }
        case GLUT_KEY_F8: {
            _dimension = DIM_3D;
            _sphere.setup(_spline3D);
            break;
        }
        case GLUT_KEY_F9: {
            _position = true;
            _time = false;
            _second = false;
            break;
        }
        case GLUT_KEY_F10: {
            _position = false;
            _time = true;
            _second = false;
            break;
        }
        case GLUT_KEY_F11: {
            _position = false;
            _time = false;
            _second = true;
            break;
        }
    }
    switch (_dimension) {
        case DIM_1D: {
            switch (key) {
                case GLUT_KEY_INSERT: {
                    _spline1D.insert();
                    break;
                }
                case GLUT_KEY_LEFT: {
                    _spline1D.previous();
                    break;
                }
                case GLUT_KEY_RIGHT: {
                    _spline1D.next();
                    break;
                }
                case GLUT_KEY_DOWN: {
                    _spline1D.previous();
                    break;
                }
                case GLUT_KEY_UP: {
                    _spline1D.next();
                    break;
                }
                case GLUT_KEY_HOME: {
                    _spline1D.first();
                    break;
                }
                case GLUT_KEY_END: {
                    _spline1D.last();
                    break;
                }
            }
            break;
        }
        case DIM_2D: {
            switch (key) {
                case GLUT_KEY_INSERT: {
                    _spline2D.insert();
                    break;
                }
                case GLUT_KEY_LEFT: {
                    _spline2D.previous();
                    break;
                }
                case GLUT_KEY_RIGHT: {
                    _spline2D.next();
                    break;
                }
                case GLUT_KEY_DOWN: {
                    _spline2D.previous();
                    break;
                }
                case GLUT_KEY_UP: {
                    _spline2D.next();
                    break;
                }
                case GLUT_KEY_HOME: {
                    _spline2D.first();
                    break;
                }
                case GLUT_KEY_END: {
                    _spline2D.last();
                    break;
                }
            }
            break;
        }
        case DIM_3D: {
            switch (key) {
                case GLUT_KEY_INSERT: {
                    _spline3D.insert();
                    break;
                }
                case GLUT_KEY_LEFT: {
                    _spline3D.previous();
                    break;
                }
                case GLUT_KEY_RIGHT: {
                    _spline3D.next();
                    break;
                }
                case GLUT_KEY_DOWN: {
                    _spline3D.previous();
                    break;
                }
                case GLUT_KEY_UP: {
                    _spline3D.next();
                    break;
                }
                case GLUT_KEY_HOME: {
                    _spline3D.first();
                    break;
                }
                case GLUT_KEY_END: {
                    _spline3D.last();
                    break;
                }
            }
            break;
        }
    }
}

//------------------------------------------------------------------------------
// mouse
void Control::mouse(int button, int state, int x, int y) {
    _motionX = x;
    _motionY = y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        _axis = false;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        _axis = true;
    }
}

//------------------------------------------------------------------------------
// motion
void Control::motion(int x, int y) {
    const double INCREMENT = 0.01;
    const double INCREMENT_SECOND = 0.1;
    switch (_dimension) {
        case DIM_1D: {
            if (_position) {
                _spline1D.modify(0.0, (double)(_motionY - y) * INCREMENT, 0.0);
            }
            else if (_time) {
                _spline1D.modify((double)((x - _motionX) + (_motionY - y)) * INCREMENT, 0.0, 0.0);
            }
            else if (_second) {
                _spline1D.modify(0.0, 0.0, (double)((x - _motionX) + (_motionY - y)) * INCREMENT_SECOND);
            }
            break;
        }
        case DIM_2D: {
            if (_position) {
                _spline2D.modify(0.0, (double)(x - _motionX) * INCREMENT, (double)(_motionY - y) * INCREMENT, 0.0, 0.0);
            }
            else if (_time) {
                _spline2D.modify((double)((x - _motionX) + (_motionY - y)) * INCREMENT, 0.0, 0.0, 0.0, 0.0);
            }
            else if (_second) {
                _spline2D.modify(0.0, 0.0, 0.0, (double)(x - _motionX) * INCREMENT_SECOND, (double)(_motionY - y) * INCREMENT_SECOND);
            }
            break;
        }
        case DIM_3D: {
            if (_position) {
                if (!_axis) {
                    _spline3D.modify(0.0, (double)(x - _motionX) * INCREMENT, (double)(_motionY - y) * INCREMENT, 0.0, 0.0, 0.0, 0.0);
                }
                else {
                    _spline3D.modify(0.0, 0.0, 0.0, -(double)((x - _motionX) + (_motionY - y)) * INCREMENT, 0.0, 0.0, 0.0);
                }
            }
            else if (_time) {
                _spline3D.modify((double)((x - _motionX) + (_motionY - y)) * INCREMENT, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
            }
            else if (_second) {
                if (!_axis) {
                    _spline3D.modify(0.0, 0.0, 0.0, 0.0, (double)(x - _motionX) * INCREMENT_SECOND, (double)(_motionY - y) * INCREMENT_SECOND, 0.0);
                }
                else {
                    _spline3D.modify(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -(double)((x - _motionX) + (_motionY - y)) * INCREMENT_SECOND);
                }
            }
            break;
        }
     }
    _motionX = x;
    _motionY = y;
}

//------------------------------------------------------------------------------
// idle
void Control::idle() {
    glutPostRedisplay();
}

//------------------------------------------------------------------------------
