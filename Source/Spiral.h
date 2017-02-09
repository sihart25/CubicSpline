//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Spiral Spline Assessment
// Spiral.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Spiral_h
#define Spiral_h

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

    class Spiral {

    public:

        //------------------------------------------------------------------------------
        // constructor
        Spiral() : _a(0.0), _b(0.0), _c(0.0) {
        }

        //------------------------------------------------------------------------------
        // setup
        void setup(Spline2D &spline2D) {
            int i;
            // generate a polar coordinate curve
            _a = 0.5;
            _b = 0.1;
            _c = 2.0;
            const int N = 15;
            double t[N];
            for (i = 0; i < N; i++) {
                t[i] = -1.0 + 2.0 * (double)i / (double)(N - 1);
            }
            // generate a cubic spline
            spline2D.clear();
            for (i = 0; i < N; i++) {
                spline2D.add(t[i], x(t[i]), y(t[i]));
            }
            spline2D.xFirst(aX(t[0]));
            spline2D.xLast(aX(t[N - 1]));
            spline2D.yFirst(aY(t[0]));
            spline2D.yLast(aY(t[N - 1]));
        }

        //------------------------------------------------------------------------------
        // get x value
        double x(double t) {
            return (_a + _b * t) * cos(_c * PI * t);
        }

        //------------------------------------------------------------------------------
        // get y value
        double y(double t) {
            return (_a + _b * t) * sin(_c * PI * t);
        }

        //------------------------------------------------------------------------------
        // get x first derivative
        double sX(double t) {
            return _b * cos(_c * PI * t) - (_a + _b * t) * _c * PI * sin(_c * PI * t);
        }

        //------------------------------------------------------------------------------
        // get y first derivative
        double sY(double t) {
            return _b * sin(_c * PI * t) + (_a + _b * t) * _c * PI * cos(_c * PI * t);
        }

        //------------------------------------------------------------------------------
        // get x second derivative
        double aX(double t) {
            return -_b * _c * PI * sin(_c * PI * t) - (_b * _c * PI * sin(_c * PI * t) + (_a + _b * t) * _c * PI * _c * PI * cos(_c * PI * t));
        }

        //------------------------------------------------------------------------------
        // get y second derivative
        double aY(double t) {
            return _b * _c * PI * cos(_c * PI * t) + (_b * _c * PI * cos(_c * PI * t) - (_a + _b * t) * _c * PI * _c * PI * sin(_c * PI * t));
        }

    private:

        double _a;
        double _b;
        double _c;

    };

} // ComputerGraphics

#endif // Spiral_h

//------------------------------------------------------------------------------
