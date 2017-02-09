//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Test Spline Assessment
// Test.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Test_h
#define Test_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "Spline1D.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    // x = x[i] + h[i] * t;
    // dx_dt = h[i];

    // y = a0 * y[i] + a1 * y[i + 1] + h[i] * b0 * s[i] + h[i] * b1 * s[i + 1];
    // a0 = 2.0 * t * t * t - 3.0 * t * t + 1.0;
    // a1 = -2.0 * t * t * t + 3.0 * t * t;
    // b0 = t * t * t - 2.0 * t * t + t;
    // b1 = t * t * t - t * t;

    // dy_dt = da0_dt * y[i] + da1_dt * y[i + 1] + h[i] * db0_dt * s[i] + h[i] * db1_dt * s[i + 1];
    // dy_dx = dy_dt * dt_dx = dy_dt / h[i];
    // dy_dx = (da0_dt * y[i] + da1_dt * y[i + 1] + h[i] * db0_dt * s[i] + h[i] * db1_dt * s[i + 1]) / h[i];
    // da0_dt = 6.0 * t * t - 6.0 * t;
    // da1_dt = -6.0 * t * t + 6.0 * t;
    // db0_dt = 3.0 * t * t - 4.0 * t + 1.0;
    // db1_dt = 3.0 * t * t - 2.0 * t;

    // d2y_dt2 = d2a0_dt2 * y[i] + d2a1_dt2 * y[i + 1] + h[i] * d2b0_dt2 * s[i] + h[i] * d2b1_dt2 * s[i + 1];
    // d2y_dx2 = (d2y_dt2 / h[i]) * dt_dx = d2y_dt2 / (h[i] * h[i]);
    // d2y_dx2 = (d2a0_dt2 * y[i] + d2a1_dt2 * y[i + 1] + h[i] * d2b0_dt2 * s[i] + h[i] * d2b1_dt2 * s[i + 1]) / (h[i] * h[i]);
    // d2a0_dt2 = 12.0 * t - 6.0;
    // d2a1_dt2 = -12.0 * t + 6.0;
    // d2b0_dt2 = 6.0 * t - 4.0;
    // d2b1_dt2 = 6.0 * t - 2.0;

    // t = 0.5
    // y = 0.5 * y[i] + 0.5 * y[i + 1] + 0.125 * h[i] * s[i] - 0.125 * h[i] * s[i + 1];
    // dy_dx = (-1.5 * y[i] + 1.5 * y[i + 1] - 0.25 * h[i] * s[i] - 0.25 * h[i] * s[i + 1]) / h[i];
    // d2y_dx2 = (0.0 * y[i] + 0.0 * y[i + 1] - 1.0 * h[i] * s[i] + 1.0 * h[i] * s[i + 1]) / (h[i] * h[i]);

    // y = a * x * x * x + b * x * x + c * x + d;
    // dy_dx = 3.0 * a * x * x + 2.0 * b * x + c;
    // d2y_dx2 = 6.0 * a * x + 2.0 * b;

    //------------------------------------------------------------------------------
    // class definition

    class Test {

    public:

        //------------------------------------------------------------------------------
        // constructor
        Test() : _a(0.0), _b(0.0), _c(0.0), _d(0.0) {
        }

        //------------------------------------------------------------------------------
        // setup
        void setup(Spline1D &spline1D, const string &filename) {
            ofstream out(filename.c_str());
            if (!out.good()) {
                throw string("Error : Invalid file name = " + filename);
            }
            int i;
            // generate a cubic
            _a = 0.5;
            _b = -0.25;
            _c = 0.5;
            _d = 0.25;
            const int n = 5;
            const double x[n] = { -1.0, -0.7, -0.3, 0.2, 1.0 };
            out << endl;
            out << "The cubic function defined by" << endl;
            out << "    y = (((((a * x) + b) * x) + c) * x) + d" << endl;
            out << "was evaluated with coefficients" << endl;
            out << "    a = " << _a << endl;
            out << "    b = " << _b << endl;
            out << "    c = " << _c << endl;
            out << "    d = " << _d << endl;
            out << "for " << n << " values of x" << endl;
            for (i = 0; i < n; i++) {
                out << "    x[" << i << "] = " << x[i] << endl;
            }
            out << "to produce " << n << " values of y" << endl;
            for (i = 0; i < n; i++) {
                out << "    y[" << i << "] = " << y(x[i]) << endl;
            }
            out << endl;
            // generate a cubic spline
            spline1D.clear();
            for (i = 0; i < n; i++) {
                spline1D.add(x[i], y(x[i]));
            }
            spline1D.xFirst(a(x[0]));
            spline1D.xLast(a(x[n - 1]));
            out << "The spline function generated from " << n << " data points and defined by" << endl;
            out << "    y = a0 * y0 + a1 * y1 + h * b0 * s0 + h * b1 * s1" << endl;
            out << "was evaluated at its midpoints" << endl;
            out << "    y = 0.5 * y0 + 0.5 * y1 + 0.125 * h * s0 - 0.125 * h * s1" << endl;
            out << "    dy/dx = (-1.5 * y0 + 1.5 * y1 - 0.25 * h * s0 - 0.25 * h * s1) / h" << endl;
            out << "    d2y/dx2 = (0.0 * y0 + 0.0 * y1 - 1.0 * h * s0 + 1.0 * h * s1) / (h * h)" << endl;
            out << endl;
            // determine errors in value
            out << "The values of the cubic and the spline were compared" << endl;
            double yError = 0.0;
            for (i = 0; i < n - 1; i++) {
                double error;
                double xMidpoint = 0.5 * (x[i] + x[i + 1]);
                if ((error = fabs(y(xMidpoint) - yMidpoint(spline1D, i))) > yError) {
                    yError = error;
                }
                out << left << "    x = " << setw(9) << xMidpoint << " cubic = " << setw(9) << y(xMidpoint) << " spline = " << setw(9) << yMidpoint(spline1D, i) << " error = " << (y(xMidpoint) - yMidpoint(spline1D, i)) << endl;
            }
            out << "to find the maximum absolute error of " << yError << endl;
            out << endl;
            // determine errors in first derivative
            out << "The first derivatives of the cubic and the spline were compared" << endl;
            double sError = 0.0;
            for (i = 0; i < n - 1; i++) {
                double error;
                double xMidpoint = 0.5 * (x[i] + x[i + 1]);
                if ((error = fabs(s(xMidpoint) - sMidpoint(spline1D, i))) > sError) {
                    sError = error;
                }
                out << left << "    x = " << setw(9) << xMidpoint << " cubic = " << setw(9) << s(xMidpoint) << " spline = " << setw(9) << sMidpoint(spline1D, i) << " error = " << (s(xMidpoint) - sMidpoint(spline1D, i)) << endl;
            }
            out << "to find the maximum absolute error of " << sError << endl;
            out << endl;
            // determine errors in second derivative
            out << "The second derivatives of the cubic and the spline were compared" << endl;
            double aError = 0.0;
            for (i = 0; i < n - 1; i++) {
                double error;
                double xMidpoint = 0.5 * (x[i] + x[i + 1]);
                if ((error = fabs(a(xMidpoint) - aMidpoint(spline1D, i))) > aError) {
                    aError = error;
                }
                out << left << "    x = " << setw(9) << xMidpoint << " cubic = " << setw(9) << a(xMidpoint) << " spline = " << setw(9) << aMidpoint(spline1D, i) << " error = " << (a(xMidpoint) - aMidpoint(spline1D, i)) << endl;
            }
            out << "to find the maximum absolute error of " << aError << endl;
            out << endl;
        }

        //------------------------------------------------------------------------------
        // get value of cubic
        double y(double x) {
            return ((_a * x + _b) * x + _c) * x + _d;
        }

        //------------------------------------------------------------------------------
        // get first derivative of cubic
        double s(double x) {
            return (3.0 * _a * x + 2.0 * _b) * x + _c;
        }

        //------------------------------------------------------------------------------
        // get second derivative of cubic
        double a(double x) {
            return 6.0 * _a * x + 2.0 * _b;
        }

        //------------------------------------------------------------------------------
        // get value at midpoint of spline
        double yMidpoint(Spline1D &spline1D, int i) {
            return 0.5 * spline1D.x().f(i)
                + 0.5 * spline1D.x().f(i + 1)
                + 0.125 * (spline1D.x().t(i + 1) - spline1D.x().t(i)) * spline1D.x().df(i)
                - 0.125 * (spline1D.x().t(i + 1) - spline1D.x().t(i)) * spline1D.x().df(i + 1);
        }

        //------------------------------------------------------------------------------
        // get first derivative at midpoint of spline
        double sMidpoint(Spline1D &spline1D, int i) {
            return (-1.5 * spline1D.x().f(i)
                + 1.5 * spline1D.x().f(i + 1)
                - 0.25 * (spline1D.x().t(i + 1) - spline1D.x().t(i)) * spline1D.x().df(i)
                - 0.25 * (spline1D.x().t(i + 1) - spline1D.x().t(i)) * spline1D.x().df(i + 1))
                / (spline1D.x().t(i + 1) - spline1D.x().t(i));
        }

        //------------------------------------------------------------------------------
        // get second derivative at midpoint of spline
        double aMidpoint(Spline1D &spline1D, int i) {
            return (-spline1D.x().df(i)
                + spline1D.x().df(i + 1))
                / (spline1D.x().t(i + 1) - spline1D.x().t(i));
        }

    private:

        double _a;
        double _b;
        double _c;
        double _d;

    };

} // ComputerGraphics

#endif // Test_h

//------------------------------------------------------------------------------
