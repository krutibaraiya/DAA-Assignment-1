#include <bits/stdc++.h>
#include "Point.h"
using namespace std;


class LineSegment
{
    public:
    Point A;
    Point B;
    static long double sweep_line;   //sweep-line status
    int index;

    LineSegment()
    {
        this -> index = -1;
    }

    LineSegment(long double sl) {
        this -> sweep_line = sl;
    }
    LineSegment(const LineSegment &L)
    {
        A = L.A;
        B = L.B;
        index = L.index;
    }

    LineSegment(Point X, Point Y, int index)
    {
        A = X;
        B = Y;
        this->index = index;
    }

    long double intersection_of_sweep_line_with_linesegment()
    {   
        if(abs(A.x - B.x) < EPS)  //vertical 
            return A.x;

        if(abs(A.y - B.y) < EPS)   //horizontal
            return A.x;
        
        long double slope = (B.y - A.y)/(B.x - A.x);

        long double intersection = (sweep_line - (A.y - slope * A.x))/slope; 
        // cout << A.x << " " << B.x << " " << sweep_line << endl;
        return intersection;
    }

    //todo- intersection with segment and operator overload(?)
    bool operator < (LineSegment &ls) {
        long double x1 = intersection_of_sweep_line_with_linesegment();
        long double x2 = ls.intersection_of_sweep_line_with_linesegment();
        // cout << "x1: " << x1 << " x2: " << endl;
        bool check = (x1 < x2 + EPS);
        //bool check = (x1 + EPS > x2);
        return check;
    }

    bool operator > (LineSegment &ls) {
        long double x1 = intersection_of_sweep_line_with_linesegment();
        long double x2 = ls.intersection_of_sweep_line_with_linesegment();
        // cout << "x1: " << x1 << " x2: " << endl;
        bool check = (x1 + EPS > x2);
        //bool check = (x1 < x2 + EPS);
        return check;
    }

    bool operator == (LineSegment &ls) {
        return (A == ls.A && B == ls.B);
    }
    bool operator != (LineSegment &ls) {
        return !(A == ls.A && B == ls.B);
    }

    pair < bool , Point > intersection_with_linesegment (LineSegment &ls) {
        long double x, y, z, x1, y1, z1;
        /**
         * x stores slope of line segment of this line segment which calls this method
         * x1 stores slope of line segment of line segment ls
         * y stores the y intercept of this line segment which call this method
         * y1 stores the y intercept of line segment ls
         * z stores the x intercept of this line segment which call this method
         * z1 stores the x intercept of line segment ls
         */
        if(abs(A.x - B.x) < EPS) {  // parralel to y axis
            x = 1, y = 0, z = -A.x;
        } else {
            x = (A.y - B.y) / (B.x - A.x);
            y = 1.0;
            z = -(x * A.x + A.y);
        }

        if(abs(ls.A.x - ls.B.x) < EPS) { // parallel to y axis
            x1 = 1, y1 = 0, z1 = -ls.A.x;
        } else {
            x1 = (ls.A.y - ls.B.y) / (ls.B.x - ls.A.x);
            y1 = 1.0;
            z1 = -(x1 * ls.A.x + ls.A.y); 
        }

        if(abs(x - x1) < EPS && abs(y - y1) < EPS) { // parallel to y axis
            return make_pair(0, Point());
        } else {
            long double a = (y * z1 - z * y1) / (x * y1 - y * x1);
            long double b;

            if(abs(y) < EPS) {
                b = -x1 * a - z1;
            } else {
                b = -x * a - z;
            }
            // cout << "a: " << a << "b: " << b << "x: " << x << "y: " << y << "z: " << z << "x1: " << x1 << "y1: " << y1 << "z1: " << z1 << endl;
            Point intersection = Point(a,b);
            // cout << intersection.x << " " << intersection.y << "intersection" << endl;
            if(intersection.check_if_a_point_lies_between_two_points(A,B) && intersection.check_if_a_point_lies_between_two_points(ls.A, ls.B)) {
                return make_pair(1, intersection);
            } else {
                return make_pair(0, Point());
            }
        }
    }


};