//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Sphere Spline Assessment
// Sphere.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Sphere_h
#define Sphere_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include "Spline3D.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Sphere {

    public:

        //------------------------------------------------------------------------------
        // constructor
        Sphere() : _a(0.0), _b(0.0), _c(0.0) {
        }

        //------------------------------------------------------------------------------
        // setup
        void setup(Spline3D &spline3D) {
            int i;
            // generate a polar coordinate curve
            _a = 0.5;
            _b = 0.5;
            _c = 7.0;
            const int N = 61;
            double t[N];
            for (i = 0; i < N; i++) {
                t[i] = -1.0 + 2.0 * (double)i / (double)(N - 1);
            }
            // generate a cubic spline
            spline3D.clear();
            for (i = 0; i < N; i++) {
                spline3D.add(t[i], x(t[i]), y(t[i]), z(t[i]));
            }
            spline3D.xFirst(aX(t[0]));
            spline3D.xLast(aX(t[N - 1]));
            spline3D.yFirst(aY(t[0]));
            spline3D.yLast(aY(t[N - 1]));
            spline3D.zFirst(aZ(t[0]));
            spline3D.zLast(aZ(t[N - 1]));
        }

        //------------------------------------------------------------------------------
        // get x value
        double x(double t) {
            return _a * cos(0.5 * PI * t) * cos(_c * PI * t);
        }

        //------------------------------------------------------------------------------
        // get y value
        double y(double t) {
            return _a * cos(0.5 * PI * t) * sin(_c * PI * t);
        }

        //------------------------------------------------------------------------------
        // get z value
        double z(double t) {
            return _b * sin(0.5 * PI * t);
        }

        //------------------------------------------------------------------------------
        // get x first derivative
        double sX(double t) {
            return -_a * 0.5 * PI * sin(0.5 * PI * t) * cos(_c * PI * t) - _a * cos(0.5 * PI * t) * _c * PI * sin(_c * PI * t);
        }

        //------------------------------------------------------------------------------
        // get y first derivative
        double sY(double t) {
            return -_a * 0.5 * PI * sin(0.5 * PI * t) * sin(_c * PI * t) + _a * cos(0.5 * PI * t) * _c * PI * cos(_c * PI * t);
        }

        //------------------------------------------------------------------------------
        // get z first derivative
        double sZ(double t) {
            return _b * 0.5 * PI * cos(0.5 * PI * t);
        }

        //------------------------------------------------------------------------------
        // get x second derivative
        double aX(double t) {
            return -_a * 0.5 * PI * 0.5 * PI * cos(0.5 * PI * t) * cos(_c * PI * t) + _a * 0.5 * PI * sin(0.5 * PI * t) * _c * PI * sin(_c * PI * t)
                + _a * 0.5 * PI * sin(0.5 * PI * t) * _c * PI * sin(_c * PI * t) - _a * cos(0.5 * PI * t) * _c * PI * _c * PI * cos(_c * PI * t);
        }

        //------------------------------------------------------------------------------
        // get y second derivative
        double aY(double t) {
            return -_a * 0.5 * PI * 0.5 * PI * cos(0.5 * PI * t) * sin(_c * PI * t) - _a * 0.5 * PI * sin(0.5 * PI * t) * _c * PI * cos(_c * PI * t)
                - _a * 0.5 * PI * sin(0.5 * PI * t) * _c * PI * cos(_c * PI * t) - _a * cos(0.5 * PI * t) * _c * PI * _c * PI * sin(_c * PI * t);
        }

        //------------------------------------------------------------------------------
        // get z second derivative
        double aZ(double t) {
            return -_b * 0.5 * PI * 0.5 * PI * sin(0.5 * PI * t);
        }

    private:

        double _a;
        double _b;
        double _c;

    };

} // ComputerGraphics

#endif // Sphere_h

//------------------------------------------------------------------------------
