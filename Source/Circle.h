//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Circle Spline Assessment
// Circle.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Circle_h
#define Circle_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include "Spline2D.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Circle {

    public:

        //------------------------------------------------------------------------------
        // constructor
        Circle() : _a(0.0) {
        }

        //------------------------------------------------------------------------------
        // setup
        void setup(Spline2D &spline2d) {
            int i;
            // generate a polar coordinate curve
            _a = 0.5;
            const int N = 9;
            double t[N];
            for (i = 0; i < N; i++) {
                t[i] = -1.0 + 2.0 * (double)i / (double)(N - 1);
            }
            // generate a cubic spline
            spline2d.clear();
            for (i = 0; i < N; i++) {
                spline2d.add(t[i], x(t[i]), y(t[i]));
            }
            spline2d.xFirst(aX(t[0]));
            spline2d.xLast(aX(t[N - 1]));
            spline2d.yFirst(aY(t[0]));
            spline2d.yLast(aY(t[N - 1]));
        }

        //------------------------------------------------------------------------------
        // get x value
        double x(double t) {
            return _a * cos(PI * t);
        }

        //------------------------------------------------------------------------------
        // get y value
        double y(double t) {
            return _a * sin(PI * t);
        }

        //------------------------------------------------------------------------------
        // get x first derivative
        double sX(double t) {
            return -_a * PI * sin(PI * t);
        }

        //------------------------------------------------------------------------------
        // get y first derivative
        double sY(double t) {
            return _a * PI * cos(PI * t);
        }

        //------------------------------------------------------------------------------
        // get x second derivative
        double aX(double t) {
            return -_a * PI * PI * cos(PI * t);
        }

        //------------------------------------------------------------------------------
        // get y second derivative
        double aY(double t) {
            return -_a * PI * PI * sin(PI * t);
        }

    private:

        double _a;

    };

} // ComputerGraphics

#endif // Circle_h

//------------------------------------------------------------------------------
