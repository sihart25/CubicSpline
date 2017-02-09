//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Cubic Spline1D Assessment
// Spline1D.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Spline1D_h
#define Spline1D_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <GL/glut.h>
#include "Spline.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Spline1D {

    public:

        //------------------------------------------------------------------------------
        // constructor
        Spline1D() : _position(0) {
        }

        //------------------------------------------------------------------------------
        // plot data points
        void plot(bool markers, bool animation) {
            const double BORDER = 0.2;
            int width = glutGet(GLUT_WINDOW_WIDTH);
            int height = glutGet(GLUT_WINDOW_HEIGHT);
            int point;
            glViewport(0, 0, width, height);
            glBegin(GL_LINES);
                glColor3d(0.5, 0.5, 0.5);
                glVertex2d(-1.0 + BORDER * 2.0, -1.0);
                glVertex2d(-1.0 + BORDER * 2.0, 1.0);
                glVertex2d(-1.0, -1.0 + BORDER * 2.0);
                glVertex2d(1.0, -1.0 + BORDER * 2.0);
            glEnd();
            // main window
            glViewport(BORDER * width, BORDER * height, (1.0 - BORDER) * width, (1.0 - BORDER) * height);
            glColor3d(0.0, 0.0, 0.0);
            glRasterPos2d(-1.0, -1.0);
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
            glLineWidth(LINE_WIDTH);
            glDisable(GL_LINE_SMOOTH);
            glBegin(GL_LINE_STRIP);
                glColor3d(0.0, 0.0, 1.0);
                for (point = 0; point <= RESOLUTION; point++) {
                    double tPoint = t(0) + (double)point / (double)RESOLUTION * (t(n() - 1) - t(0));
                    glVertex2d(tPoint, x().get(tPoint));
                }
            glEnd();
            if (markers) {
                glPointSize(POINT_SIZE);
                glEnable(GL_POINT_SMOOTH);
                glBegin(GL_POINTS);
                    glColor3d(0.0, 0.0, 1.0);
                    for (point = 0; point < n(); point++) {
                        glVertex2d(x().t(point), x().f(point));
                    }
                    glColor3d(1.0, 0.0, 0.0);
                    glVertex2d(x().t(x().i()), x().f(x().i()));
                glEnd();
            }
            if (animation) {
                glPointSize(POINT_SIZE);
                glEnable(GL_POINT_SMOOTH);
                glBegin(GL_POINTS);
                    glColor3d(1.0, 0.0, 0.0);
                    double tPoint = t(0) + (double)_position / (double)RESOLUTION * (t(n() - 1) - t(0));
                    glVertex2d(tPoint, x().get(tPoint));
                    _position = (_position + 1) % RESOLUTION;
                glEnd();
            }
            else {
                _position = 0;
            }
            // y window
            glViewport(0, BORDER * height, BORDER * width, (1.0 - BORDER) * height);
            glColor3d(0.0, 0.0, 0.0);
            glRasterPos2d(-1.0, -1.0);
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
            x().plot(markers);
        }

        //------------------------------------------------------------------------------
        // get x
        const Spline &x() const {
            return _x;
        }

        //------------------------------------------------------------------------------
        // read data points
        void read(const string &filename) {
            ifstream in(filename.c_str());
            if (!in.good()) {
                throw string("Error : Invalid file name = " + filename);
            }
            clear();
            int n;
            in >> n;
            for (int i = 0; i < n; i++) {
                double t;
                double x;
                in >> t >> x;
                add(t, x);
            }
            double first;
            double last;
            in >> first >> last;
            xFirst(first);
            xLast(last);
        }

        //------------------------------------------------------------------------------
        // write data points
        void write(const string &filename) const {
            ofstream out(filename.c_str());
            if (!out.good()) {
                throw string("Error : Invalid file name = " + filename);
            }
            out << n() << endl;
            for (int i = 0; i < n(); i++) {
                out << t(i) << " " << _x.f(i) << endl;
            }
            out << xFirst() << " " << xLast() << endl;
        }

        //------------------------------------------------------------------------------
        // add data point
        void add(double t, double x) {
            _x.add(t, x);
        }

        //------------------------------------------------------------------------------
        // modify data point
        void modify(double t, double x, double a) {
            _x.modify(t, x, a);
        }

        //------------------------------------------------------------------------------
        // insert data point
        void insert() {
            _x.insert();
        }

        //------------------------------------------------------------------------------
        // remove data point
        void remove() {
            _x.remove();
        }

        //------------------------------------------------------------------------------
        // clear arrays
        void clear() {
            _x.clear();
        }

        //------------------------------------------------------------------------------
        // next data point
        void next() {
            _x.next();
        }

        //------------------------------------------------------------------------------
        // previous data point
        void previous() {
            _x.previous();
        }

        //------------------------------------------------------------------------------
        // first data point
        void first() {
            _x.first();
        }

        //------------------------------------------------------------------------------
        // last data point
        void last() {
            _x.last();
        }

        //------------------------------------------------------------------------------
        // get index of data point
        int i() const {
            return x().i();
        }

        //------------------------------------------------------------------------------
        // get number of data points
        int n() const {
            return x().n();
        }

        //------------------------------------------------------------------------------
        // get data point parameter
        double t(int m) const {
            return x().t(m);
        }

        //------------------------------------------------------------------------------
        // set x first data point second derivative
        void xFirst(double a) {
            _x.aFirst(a);
        }

        //------------------------------------------------------------------------------
        // set x last data point second derivative
        void xLast(double a) {
            _x.aLast(a);
        }

        //------------------------------------------------------------------------------
        // get x first data point second derivative
        double xFirst() const {
            return _x.aFirst();
        }

        //------------------------------------------------------------------------------
        // get x last data point second derivative
        double xLast() const {
            return _x.aLast();
        }

    private:

        //------------------------------------------------------------------------------
        // attributes
        Spline _x;
        int _position;

    };

} // ComputerGraphics

#endif // Spline1D_h

//------------------------------------------------------------------------------
