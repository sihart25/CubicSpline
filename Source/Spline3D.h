//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Cubic Spline3D Assessment
// Spline3D.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Spline3D_h
#define Spline3D_h

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

    class Spline3D {

    public:

        //------------------------------------------------------------------------------
        // constructor
        Spline3D() : _spin(false), _stop(true), _angleX(0.0), _angleY(0.0), _angleZ(0.0), _spinX(false), _spinY(true), _spinZ(false), _position(0) {
        }

        //------------------------------------------------------------------------------
        // plot data points
        void plot(bool markers, bool animation) {
            static double angle = 0.0;
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
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'X');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ',');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ',');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Z');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
            glPushMatrix();
            glRotated(_angleZ, 0.0, 0.0, 1.0);
            glRotated(_angleX, 1.0, 0.0, 0.0);
            glRotated(_angleY, 0.0, 1.0, 0.0);
            const double INCREMENT = 1.0;
            if (_spin && _spinX) {
                _angleX += INCREMENT;
            }
            if (_spin && _spinY) {
                _angleY += INCREMENT;
            }
            if (_spin && _spinZ) {
                _angleZ += INCREMENT;
            }
            glLineWidth(LINE_WIDTH);
            glDisable(GL_LINE_SMOOTH);
            glBegin(GL_LINE_STRIP);
                glColor3d(0.0, 0.0, 1.0);
                for (point = 0; point <= RESOLUTION; point++) {
                    double tPoint = t(0) + (double)point / (double)RESOLUTION * (t(n() - 1) - t(0));
                    glVertex3d(x().get(tPoint), y().get(tPoint), z().get(tPoint));
                }
            glEnd();
            if (markers) {
                glPointSize(POINT_SIZE);
                glEnable(GL_POINT_SMOOTH);
                glBegin(GL_POINTS);
                    glColor3d(0.0, 0.0, 1.0);
                    for (point = 0; point < n(); point++) {
                        glVertex3d(x().f(point), y().f(point), z().f(point));
                    }
                    glColor3d(1.0, 0.0, 0.0);
                    glVertex3d(x().f(x().i()), y().f(y().i()), z().f(y().i()));
                glEnd();
            }
            if (animation) {
                glPointSize(POINT_SIZE);
                glEnable(GL_POINT_SMOOTH);
                glBegin(GL_POINTS);
                    glColor3d(1.0, 0.0, 0.0);
                    double tPoint = t(0) + (double)_position / (double)RESOLUTION * (t(n() - 1) - t(0));
                    glVertex3d(x().get(tPoint), y().get(tPoint), z().get(tPoint));
                    _position = (_position + 1) % RESOLUTION;
                glEnd();
            }
            else {
                _position = 0;
            }
            glPopMatrix();
            // x window
            glViewport(BORDER * width, 0, (1.0 - BORDER) * width, BORDER * height);
            glColor3d(0.0, 0.0, 0.0);
            glRasterPos2d(-1.0, -1.0);
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'X');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
            glPushMatrix();
            glScaled(-1.0, 1.0, 1.0);
            glRotated(90.0, 0.0, 0.0, 1.0);
            x().plot(markers);
            glPopMatrix();
            // y window
            glViewport(0, BORDER * height, BORDER * width, (1.0 - BORDER) * height);
            glColor3d(0.0, 0.0, 0.0);
            glRasterPos2d(-1.0, -1.0);
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
            y().plot(markers);
            // z window
            glViewport(0, 0, BORDER * width, BORDER * height);
            glColor3d(0.0, 0.0, 0.0);
            glRasterPos2d(-1.0, -1.0);
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Z');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
            glPushMatrix();
            glScaled(1.0, -1.0, 1.0);
            z().plot(markers);
            glPopMatrix();
        }

        //------------------------------------------------------------------------------
        // get x
        const Spline &x() const {
            return _x;
        }

        //------------------------------------------------------------------------------
        // get y
        const Spline &y() const {
            return _y;
        }

        //------------------------------------------------------------------------------
        // get z
        const Spline &z() const {
            return _z;
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
                double y;
                double z;
                in >> t >> x >> y >> z;
                add(t, x, y, z);
            }
            double first;
            double last;
            in >> first >> last;
            xFirst(first);
            xLast(last);
            in >> first >> last;
            yFirst(first);
            yLast(last);
            in >> first >> last;
            zFirst(first);
            zLast(last);
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
                out << t(i) << " " << _x.f(i) << " " << _y.f(i) << " " << _z.f(i) << endl;
            }
            out << xFirst() << " " << xLast() << endl;
            out << yFirst() << " " << yLast() << endl;
            out << zFirst() << " " << zLast() << endl;
        }

        //------------------------------------------------------------------------------
        // add data point
        void add(double t, double x, double y, double z) {
            _x.add(t, x);
            _y.add(t, y);
            _z.add(t, z);
        }

        //------------------------------------------------------------------------------
        // modify data point
        void modify(double t, double x, double y, double z, double aX, double aY, double aZ) {
            _x.modify(t, x, aX);
            _y.modify(t, y, aY);
            _z.modify(t, z, aZ);
        }

        //------------------------------------------------------------------------------
        // insert data point
        void insert() {
            _x.insert();
            _y.insert();
            _z.insert();
        }

        //------------------------------------------------------------------------------
        // remove data point
        void remove() {
            _x.remove();
            _y.remove();
            _z.remove();
        }

        //------------------------------------------------------------------------------
        // clear arrays
        void clear() {
            _x.clear();
            _y.clear();
            _z.clear();
        }

        //------------------------------------------------------------------------------
        // next data point
        void next() {
            _x.next();
            _y.next();
            _z.next();
        }

        //------------------------------------------------------------------------------
        // previous data point
        void previous() {
            _x.previous();
            _y.previous();
            _z.previous();
        }

        //------------------------------------------------------------------------------
        // first data point
        void first() {
            _x.first();
            _y.first();
            _z.first();
        }

        //------------------------------------------------------------------------------
        // last data point
        void last() {
            _x.last();
            _y.last();
            _z.last();
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
        // set y first data point second derivative
        void yFirst(double a) {
            _y.aFirst(a);
        }

        //------------------------------------------------------------------------------
        // set y last data point second derivative
        void yLast(double a) {
            _y.aLast(a);
        }

        //------------------------------------------------------------------------------
        // set z first data point second derivative
        void zFirst(double a) {
            _z.aFirst(a);
        }

        //------------------------------------------------------------------------------
        // set z last data point second derivative
        void zLast(double a) {
            _z.aLast(a);
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

        //------------------------------------------------------------------------------
        // get y first data point second derivative
        double yFirst() const {
            return _y.aFirst();
        }

        //------------------------------------------------------------------------------
        // get y last data point second derivative
        double yLast() const {
            return _y.aLast();
        }

        //------------------------------------------------------------------------------
        // get z first data point second derivative
        double zFirst() const {
            return _z.aFirst();
        }

        //------------------------------------------------------------------------------
        // get z last data point second derivative
        double zLast() const {
            return _z.aLast();
        }

        //------------------------------------------------------------------------------
        // play spin
        void play() {
            if (_stop) {
                _spin = true;
            }
            else {
                _spin = !_spin;
            }
            _stop = false;
        }

        //------------------------------------------------------------------------------
        // stop spin
        void stop() {
            if (_stop) {
                _spin = true;
            }
            else {
                _spin = false;
            }
            _stop = !_stop;
            _angleX = 0.0;
            _angleY = 0.0;
            _angleZ = 0.0;
        }

        //------------------------------------------------------------------------------
        // set spin axis
        void spin() {
            if (_spinX) {
                _spinX = false;
                _spinY = true;
                _spinZ = false;
            }
            else if (_spinY) {
                _spinX = false;
                _spinY = false;
                _spinZ = true;
            }
            else if (_spinZ) {
                _spinX = true;
                _spinY = false;
                _spinZ = false;
            }
        }

    private:

        //------------------------------------------------------------------------------
        // attributes
        Spline _x;
        Spline _y;
        Spline _z;
        bool _spin;
        bool _stop;
        double _angleX;
        double _angleY;
        double _angleZ;
        bool _spinX;
        bool _spinY;
        bool _spinZ;
        int _position;

    };

} // ComputerGraphics

#endif // Spline3D_h

//------------------------------------------------------------------------------
