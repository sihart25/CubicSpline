//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Cubic Spline Assessment
// Control.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Control_h
#define Control_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Spline1D.h"
#include "Spline2D.h"
#include "Spline3D.h"
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

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // constants

    const int DIM_1D = 0;
    const int DIM_2D = 1;
    const int DIM_3D = 2;

    //------------------------------------------------------------------------------
    // class definition

    class Control {

    public:

        Control() : _motionX(0), _motionY(0), _dimension(DIM_1D), _markers(true), _animation(false), 
            _position(true), _time(false), _second(false), _axis(false) {}
        ~Control() { cout << "Control object destructed" << endl; }
        void init(int argc, char **argv);
        void display();
        void reshape(int width, int height);
        void keyboard(unsigned char key, int x, int y);
        void special(int key, int x, int y);
        void mouse(int button, int state, int x, int y);
        void motion(int x, int y);
        void idle();

    private:

        Spline1D _spline1D;
        Spline2D _spline2D;
        Spline3D _spline3D;
        Test _test;
        Spiral _spiral;
        Clover _clover;
        Circle _circle;
        Sphere _sphere;
        Torus _torus;
        Helix _helix;
        int _motionX;
        int _motionY;
        int _dimension;
        bool _markers;
        bool _animation;
        bool _position;
        bool _time;
        bool _second;
        bool _axis;

    };

} // ComputerGraphics

#endif // Control_h

//------------------------------------------------------------------------------
