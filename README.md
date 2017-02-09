# CubicSpline
The aim of this assessment was to produce a program to generate and display cubic splines. The program was tested by fitting a cubic spline to a cubic function, and comparing the results of the cubic spline with those of the cubic function. The program’s user interface allows data points to be inserted, deleted and moved. Data points can be read from and written to text files, and several pre-defined curves are provided. Cubic splines of one, two or three functions can be displayed. Cubic splines of more than one function are displayed both independently, and as curves in a two or three dimensional coordinate system. Three dimensional curves can be rotated and projected.
 
#Summary
The aim of this assessment was to produce a program to generate and display cubic splines. The program was tested by fitting a cubic spline to a cubic function, and comparing the results of the cubic spline with those of the cubic function. The program’s user interface allows data points to be inserted, deleted and moved. Data points can be read from and written to text files, and several pre-defined curves are provided. Cubic splines of one, two or three functions can be displayed. Cubic splines of more than one function are displayed both independently, and as curves in a two or three dimensional coordinate system. Three dimensional curves can be rotated and projected.
Appendix 1: Absolute Errors

The cubic function defined by
    y = (((((a * x) + b) * x) + c) * x) + d
was evaluated with coefficients
    a = 0.5
    b = -0.25
    c = 0.5
    d = 0.25
for 5 values of x
    x[0] = -1
    x[1] = -0.7
    x[2] = -0.3
    x[3] = 0.2
    x[4] = 1
to produce 5 values of y
    y[0] = -1
    y[1] = -0.394
    y[2] = 0.064
    y[3] = 0.344
    y[4] = 1

The spline function generated from 5 data points and defined by
    y = a0 * y0 + a1 * y1 + h * b0 * s0 + h * b1 * s1
was evaluated at its midpoints
    y = 0.5 * y0 + 0.5 * y1 + 0.125 * h * s0 - 0.125 * h * s1
    dy/dx = (-1.5 * y0 + 1.5 * y1 - 0.25 * h * s0 - 0.25 * h * s1) / h
    d2y/dx2 = (0.0 * y0 + 0.0 * y1 - 1.0 * h * s0 + 1.0 * h * s1) / (h * h)

The values of the cubic and the spline were compared
    x = -0.85     cubic = -0.662687 spline = -0.662687 error = 0
    x = -0.5      cubic = -0.125    spline = -0.125    error = -2.77556e-017
    x = -0.05     cubic = 0.224313  spline = 0.224312  error = 2.77556e-017
    x = 0.6       cubic = 0.568     spline = 0.568     error = 1.11022e-016
to find the maximum absolute error of 1.11022e-016

The first derivatives of the cubic and the spline were compared
    x = -0.85     cubic = 2.00875   spline = 2.00875   error = -4.44089e-016
    x = -0.5      cubic = 1.125     spline = 1.125     error = 2.22045e-016
    x = -0.05     cubic = 0.52875   spline = 0.52875   error = -1.11022e-016
    x = 0.6       cubic = 0.74      spline = 0.74      error = 1.11022e-016
to find the maximum absolute error of 4.44089e-016

The second derivatives of the cubic and the spline were compared
    x = -0.85     cubic = -3.05     spline = -3.05     error = 1.33227e-015
    x = -0.5      cubic = -2        spline = -2        error = -8.88178e-016
    x = -0.05     cubic = -0.65     spline = -0.65     error = 0
    x = 0.6       cubic = 1.3       spline = 1.3       error = -4.44089e-016
to find the maximum absolute error of 1.33227e-015
Appendix 2: Sample Curves
Figure 1:
A plot of the cubic spline fitted to the cubic function, showing the data points.
y = at3 + bt2 + ct + d
for a = 0.5, b = -0.25, c = 0.5, d = 0.25
for t = -1.0, -0.7, -0.3, 0.2, 1.0


Figure 2:
A plot of the cubic spline fitted to the circular function, showing the data points, and the animation point.
x = a.cos(.t)
y = a.sin(.t)
for a = 0.5
for t = -1.0 … 1.0 in 8 steps


Figure 3:
A plot of the cubic spline fitted to the spherical function, showing the data points.
x = a.cos(0.5..t).cos(c..t)
y = a.cos(0.5..t).sin(c..t)
z = b.sin(0.5..t)
for a = 0.5, b = 0.5, c = 7.0
for t = -1.0 ... 1.0 in 60 steps


Figure 4:
A plot of the cubic spline fitted to the conical helix function.
x = (a+b.t).cos(c..t)
y = (a+b.t).sin(c..t)
z = d.t
for a = 0.5, b = 0.2, c = 3.0, d = 0.5
for t = -1.0 ... 1.0 in 30 steps


#Appendix 3: User Guide
The program is run from the command line as “CubicSpline.exe”. The following menu, which details the use of the mouse and keyboard, is displayed in the console window.

Escape		Exit Program
F1		Select Dimensions
F2		Select Test
F3		Select Spiral
F4		Select Clover
F5		Select Circle
F6		Select Helix
F7		Select Torus
F8		Select Sphere
F9		Change Position with Mouse
F10		Change Time with Mouse
F11		Change Second Derivative with Mouse
1  		Select Markers
2		Play or Stop Animation
3		Play or Stop Spin
4		Play or Pause Spin
5		Select Spin Axis
6		Read Files
7		Write Files
Enter		Clear Points
Insert		Insert Point
Delete		Delete Point
Left or Down	Select Previous Point
Right or Up	Select Next Point
Home		Select First Point
End		Select Last Point
Left Mouse	Change X and Y Coordinates
Right Mouse 	Change Z Coordinate

