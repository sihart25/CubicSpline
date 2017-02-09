//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Clover Spline Assessment
// Clover.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Clover_h
#define Clover_h

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

    class Clover {

    public:

        //------------------------------------------------------------------------------
        // constructor
        Clover() : _a(0.0), _b(0.0), _c(0.0) {
        }

        //------------------------------------------------------------------------------
        // setup
        void setup(Spline2D &spline2D) {
            int i;
            // generate a polar coordinate curve
            _a = 0.5;
            _b = 0.4;
            _c = 5.0;
            const int N = 31;
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
            return (_a + _b * cos(_c * PI * t)) * cos(PI * t);
        }

        //------------------------------------------------------------------------------
        // get y value
        double y(double t) {
            return (_a + _b * cos(_c * PI * t)) * sin(PI * t);
        }

        //------------------------------------------------------------------------------
        // get x first derivative
        double sX(double t) {
            return (-_b * _c * PI * sin(_c * PI * t)) * cos(PI * t) - (_a + _b * cos(_c * PI * t)) * PI * sin(PI * t);
        }

        //------------------------------------------------------------------------------
        // get y first derivative
        double sY(double t) {
            return (-_b * _c * PI * sin(_c * PI * t)) * sin(PI * t) + (_a + _b * cos(_c * PI * t)) * PI * cos(PI * t);
        }

        //------------------------------------------------------------------------------
        // get x second derivative
        double aX(double t) {
            return (-_b * _c * PI * _c * PI * cos(_c * PI * t)) * cos(PI * t) - (-_b * _c * PI * sin(_c * PI * t)) * PI * sin(PI * t)
                + (_b * _c * PI * sin(_c * PI * t)) * PI * sin(PI * t) - (_a + _b * cos(_c * PI * t)) * PI * PI * cos(PI * t);
        }

        //------------------------------------------------------------------------------
        // get y second derivative
        double aY(double t) {
            return (-_b * _c * PI * _c * PI * cos(_c * PI * t)) * sin(PI * t) + (-_b * _c * PI * sin(_c * PI * t)) * PI * cos(PI * t)
                - (_b * _c * PI * sin(_c * PI * t)) * PI * cos(PI * t) - (_a + _b * cos(_c * PI * t)) * PI * PI * sin(PI * t);
        }

    private:

        double _a;
        double _b;
        double _c;

    };

} // ComputerGraphics

#endif // Clover_h

//------------------------------------------------------------------------------
