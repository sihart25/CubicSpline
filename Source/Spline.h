//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Cubic Spline Assessment
// Spline.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Spline_h
#define Spline_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Spline {

    public:

        //------------------------------------------------------------------------------
        // constructor
        Spline() : _n(0), _i(0), _size(1), _aFirst(0.0), _aLast(0.0) {
            _t = new double[_size];
            _f = new double[_size];
            _df = new double[_size];
        }

        //------------------------------------------------------------------------------
        // destructor
        ~Spline() {
            erase();
        }

        //------------------------------------------------------------------------------
        // plot data points
        void plot(bool markers) const {
            int point;
            glColor3d(0.0, 0.0, 1.0);
            glLineWidth(LINE_WIDTH);
            glDisable(GL_LINE_SMOOTH);
            glBegin(GL_LINE_STRIP);
                glColor3d(0.0, 0.0, 1.0);
                for (point = 0; point <= RESOLUTION; point++) {
                    double tPlot = t(0) + (double)point / (double)RESOLUTION * (t(n() - 1) - t(0));
                    glVertex2d(tPlot, get(tPlot));
                }
            glEnd();
            if (markers) {
                glPointSize(POINT_SIZE);
                glEnable(GL_POINT_SMOOTH);
                glBegin(GL_POINTS);
                    glColor3d(0.0, 0.0 ,1.0);
                    for (point = 0; point < n(); point++) {
                        glVertex2d(t(point), f(point));
                    }
                    glColor3d(1.0, 0.0, 0.0);
                    glVertex2d(t(i()), f(i()));
                glEnd();
            }
        }

        //------------------------------------------------------------------------------
        // add data point
        void add(double t, double f) {
            _n++;
            resize();
            _t[n() - 1] = t;
            _f[n() - 1] = f;
            slopes();
        }

        //------------------------------------------------------------------------------
        // modify data point
        void modify(double t, double f, double a) {
            if (i() >= 0 && i() < n()) {
                double SEPARATION = 0.1 * 2.0 / (double)(n() - 1);
                _t[i()] += t;
                if ((i() > 0) && (_t[i()] < _t[i() - 1] + SEPARATION)) {
                    _t[i()] = _t[i() - 1] + SEPARATION;
                }
                else if ((i() < n() - 1) && (_t[i()] > _t[i() + 1] - SEPARATION)) {
                    _t[i()] = _t[i() + 1] - SEPARATION;
                }
                if (n() > 1) {
                    double minimum = _t[0];
                    double maximum = _t[n() - 1];
                    for (int point = 0; point < n(); point++) {
                        _t[point] = -1.0 + 2.0 * (_t[point] - minimum) / (maximum - minimum);
                    }
                }
                _f[i()] += f;
                if (i() == 0) {
                    _aFirst += a;
                }
                if (i() == n() - 1) {
                    _aLast += a;
                }
                slopes();
            }
        }

        //------------------------------------------------------------------------------
        // insert data point
        void insert() {
            if (n() <= 0) {
                add(0.0, 0.0);
            }
            else if (i() >= 0 && i() < n()) {
                double tInsert;
                double fInsert;
                if (i() < n() - 1) {
                    tInsert = 0.5 * (_t[i()] + _t[i() + 1]);
                }
                else if (i() == 0) {
                    tInsert = _t[i()];
                }
                else {
                    tInsert = _t[i()] + (_t[i()] - _t[i() - 1]);
                }
                fInsert = get(tInsert);
                _n++;
                resize();
                for (int point = n() - 1; point > i(); point--) {
                    _t[point] = _t[point - 1];
                    _f[point] = _f[point - 1];
                }
                _i++;
                _t[i()] = tInsert;
                _f[i()] = fInsert;
            }
            modify(0.0, 0.0, 0.0);
        }

        //------------------------------------------------------------------------------
        // remove data point
        void remove() {
            if (n() <= 1) {
                clear();
            }
            else if (i() >= 0 && i() < n()) {
                _n--;
                for (int point = i(); point < n(); point++) {
                    _t[point] = _t[point + 1];
                    _f[point] = _f[point + 1];
                }
                if (i() > 0) {
                    _i--;
                }
            }
            slopes();
        }

        //------------------------------------------------------------------------------
        // clear arrays
        void clear() {
            _n = 0;
            _i = 0;
            _aFirst = 0.0;
            _aLast = 0.0;
        }

        //------------------------------------------------------------------------------
        // next data point
        void next() {
            _i++;
            wrap();
        }

        //------------------------------------------------------------------------------
        // previous data point
        void previous() {
            _i--;
            wrap();
        }

        //------------------------------------------------------------------------------
        // first data point
        void first() {
            _i = 0;
        }

        //------------------------------------------------------------------------------
        // last data point
        void last() {
            _i = n() - 1;
        }

        //------------------------------------------------------------------------------
        // wrap data point
        void wrap() {
            if (i() < 0) {
                _i = n() - 1;
            }
            else if (_i > n() - 1) {
                _i = 0;
            }
        }

        //------------------------------------------------------------------------------
        // get data point
        double get(double find) const {
            double result = 0.0;
            if (n() == 1) {
                result = f(0);
            }
            else {
                int i = 0;
                while ((t(i + 1) <= find) && (i + 1 < n() - 1)) {
                    i++;
                }
                double dt = t(i + 1) - t(i);
                double a[4][4] = {{ 2.0, -2.0, 1.0, 1.0 }, { -3.0, 3.0, -2.0, -1.0 }, { 0.0, 0.0, 1.0, 0.0 }, { 1.0, 0.0, 0.0, 0.0 }};
                double h = dt;
                double s = (find - t(i)) / dt;
                double v[4] = { f(i), f(i + 1), h * df(i), h * df(i + 1) };
                for (int j = 0; j < 4; j++) {
                    double sum = a[0][j];
                    for (int k = 1; k < 4; k++) {
                        sum = sum * s + a[k][j];
                    }
                    result += sum * v[j];
                }
            }
            return result;
        }

        //------------------------------------------------------------------------------
        // get data point
        int i() const {
            return _i;
        }

        //------------------------------------------------------------------------------
        // get number of data points
        int n() const {
            return _n;
        }

        //------------------------------------------------------------------------------
        // get data point parameter
        double t(int m) const {
            double tValid;
            if (n() == 0) {
                tValid = 0.0;
            }
            else if (m < 0) {
                tValid = _t[0];
            }
            else if (m > n() - 1) {
                tValid = _t[n() - 1];
            }
            else {
                tValid = _t[m];
            }
            return tValid;
        }

        //------------------------------------------------------------------------------
        // get data point parameter
        double t() const {
            return t(i());
        }

        //------------------------------------------------------------------------------
        // get data point value
        double f(int m) const {
            if (n() == 0) {
                return 0.0;
            }
            else if (m < 0) {
                return _f[0];
            }
            else if (m > n() - 1) {
                return _f[n() - 1];
            }
            else {
                return _f[m];
            }
        }

        //------------------------------------------------------------------------------
        // get data point value
        double f() const {
            return f(i());
        }

        //------------------------------------------------------------------------------
        // get data point slope
        double df(int m) const {
            if (n() == 0) {
                return 0.0;
            }
            else if (m < 0) {
                return _df[0];
            }
            else if (m > n() - 1) {
                return _df[n() - 1];
            }
            else {
                return _df[m];
            }
        }

        //------------------------------------------------------------------------------
        // get data point slope
        double df() const {
            return df(i());
        }

        //------------------------------------------------------------------------------
        // set first data point second derivative
        void aFirst(double a) {
            _aFirst = a;
            slopes();
        }

        //------------------------------------------------------------------------------
        // set last data point second derivative
        void aLast(double a) {
            _aLast = a;
            slopes();
        }

        //------------------------------------------------------------------------------
        // get first data point second derivative
        double aFirst() const {
            return _aFirst;
        }

        //------------------------------------------------------------------------------
        // get last data point second derivative
        double aLast() const {
            return _aLast;
        }

    private:

        //------------------------------------------------------------------------------
        // hidden copy constructor
        Spline(const Spline &spline) {}

        //------------------------------------------------------------------------------
        // hidden assignment operator
        Spline &operator=(const Spline &spline) {}

        //------------------------------------------------------------------------------
        // erase arrays
        void erase() {
            delete[] _t;
            delete[] _f;
            delete[] _df;
        }

        //------------------------------------------------------------------------------
        // resize arrays
        void resize() {
            if (_n > _size) {
                double *_tOld = _t;
                double *_fOld = _f;
                double *_dfOld = _df;
                _t = new double[_n];
                _f = new double[_n];
                _df = new double[_n];
                for (int i = 0; i < _size; i++) {
                    _t[i] = _tOld[i];
                    _f[i] = _fOld[i];
                    _df[i] = _dfOld[i];
                }
                _size = _n;
                delete[] _tOld;
                delete[] _fOld;
                delete[] _dfOld;
            }
        }

        //------------------------------------------------------------------------------
        // set slopes
        void slopes() {
            if (n() >= 2) {
                int i;
                int j;
                double r = 1.0 / (t(1) - t(0));
                double g = 3.0 * (f(1) - f(0)) * r * r;
                double *a = new double[n()];
                double *b = new double[n()];
                double *c = new double[n()];
                double *d = new double[n()];
                b[0] = 2.0 * r;
                c[0] = r;
                d[0] = g - 0.5 * _aFirst;
                j = 1;
                while (j < n() - 1) {
                    i = j;
                    j++;
                    double rOld = r;
                    r = 1.0 / (t(j) - t(i));
                    double gOld = g;
                    g = 3.0 * (f(j) - f(i)) * r * r;
                    a[i] = rOld;
                    b[i] = 2.0 * (rOld + r);
                    c[i] = r;
                    d[i] = gOld + g;
                }
                a[n() - 1] = r;
                b[n() - 1] = 2.0 * r;
                d[n() - 1] = g + 0.5 * _aLast;
                j = 0;
                while (j < n() - 1) {
                    i = j;
                    j++;
                    double m = a[j] / b[i];
                    b[j] -= c[i] * m;
                    d[j] -= d[i] * m;
                }
                _df[n() - 1] = d[n() - 1] / b[n() - 1];
                i = n() - 1;
                while (i > 0) {
                    j = i;
                    i--;
                    _df[i] = (d[i] - c[i] * _df[j]) / b[i];
                }
                delete[] a;
                delete[] b;
                delete[] c;
                delete[] d;
            }
        }

        //------------------------------------------------------------------------------
        // attributes
        int _n;
        int _i;
        int _size;
        double *_t;
        double *_f;
        double *_df;
        double _aFirst;
        double _aLast;

    };

} // ComputerGraphics

#endif // Spline_h

//------------------------------------------------------------------------------
