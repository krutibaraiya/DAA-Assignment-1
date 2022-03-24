#include <bits/stdc++.h>
#include "Point.h"
using namespace std;

/**
 * @brief Line segment class
 * 
 */
class LineSegment
{
    public:
    Point A; /// Starting point of the line segment
    Point B; /// Ending point of the line segment
    static long double sweep_line; /// sweep-line status
    int index; /// index of the line segment

    /**
     * @brief Construct a new Line Segment object
     * 
     */
    public:
    LineSegment()
    {
        this -> index = -1;
    }

    /**
     * @brief Construct a new Line Segment object
     * 
     * @param sl 
     */
    LineSegment(long double sl) {
        this -> sweep_line = sl;
    }

    /**
     * @brief Construct a new Line Segment object
     * 
     * @param L 
     */
    LineSegment(const LineSegment &L)
    {
        A = L.A;
        B = L.B;
        index = L.index;
    }

    /**
     * @brief Construct a new Line Segment object
     * 
     * @param X Point X of the line segment
     * @param Y Point Y of the line segment
     * @param index index of the line segment
     */
    LineSegment(Point X, Point Y, int index)
    {
        A = X;
        B = Y;
        this->index = index;
    }

    /**
     * @brief method to find the intersection of the sweep line with the line segment
     * 
     * @return long double 
     */
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

    /**
     * @brief operator overloading for <
     * 
     * @param ls line segment to be compared with
     * @return true if the given line segment is smaller than the compared segment
     * @return false if the given line segment is greater than the compared segment
     */
    bool operator < (LineSegment &ls) {
        long double x1 = intersection_of_sweep_line_with_linesegment();
        long double x2 = ls.intersection_of_sweep_line_with_linesegment();
        // cout << "x1: " << x1 << " x2: " << endl;
        bool check = (x1 < x2 + EPS);
        //bool check = (x1 + EPS > x2);
        return check;
    }

    /**
     * @brief operator overloading for >
     * 
     * @param ls the line segment to be compared with
     * @return true if line segment is greater than the compared line segment
     * @return false if line segment is smaller than the compared line segment
     */
    bool operator > (LineSegment &ls) {
        long double x1 = intersection_of_sweep_line_with_linesegment();
        long double x2 = ls.intersection_of_sweep_line_with_linesegment();
        // cout << "x1: " << x1 << " x2: " << endl;
        bool check = (x1 + EPS > x2);
        //bool check = (x1 < x2 + EPS);
        return check;
    }

    /**
     * @brief operator overloading for ==
     * 
     * @param ls line segment to be compared with
     * @return true if both line segments are equal
     * @return false if both line segments are not equal
     */
    bool operator == (LineSegment &ls) {
        return (A == ls.A && B == ls.B);
    }

    /**
     * @brief operator overloading for !=
     * 
     * @param ls line segment
     * @return true if both line segments are not equal
     * @return false if both line segments are equal
     */
    bool operator != (LineSegment &ls) {
        return !(A == ls.A && B == ls.B);
    }

    /**
     * @brief method to find intersection points of two line segments
     * 
     * @param ls 
     * @return pair < bool , Point > 
     */
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
        if(abs(A.x - B.x) < EPS) {  /// parralel to y axis
            x = 1, y = 0, z = -A.x;
        } else {
            x = (A.y - B.y) / (B.x - A.x);
            y = 1.0;
            z = -(x * A.x + A.y);
        }

        if(abs(ls.A.x - ls.B.x) < EPS) { /// parallel to y axis
            x1 = 1, y1 = 0, z1 = -ls.A.x;
        } else {
            x1 = (ls.A.y - ls.B.y) / (ls.B.x - ls.A.x);
            y1 = 1.0;
            z1 = -(x1 * ls.A.x + ls.A.y); 
        }

        if(abs(x - x1) < EPS && abs(y - y1) < EPS) { /// parallel to y axis
            return make_pair(0, Point());
        } else {
            long double a = (y * z1 - z * y1) / (x * y1 - y * x1); /// x coordinate of the intersection point
            long double b; /// y coordinate of the intersection points

            if(abs(y) < EPS) {
                b = -x1 * a - z1;
            } else {
                b = -x * a - z;
            }
            // cout << "a: " << a << "b: " << b << "x: " << x << "y: " << y << "z: " << z << "x1: " << x1 << "y1: " << y1 << "z1: " << z1 << endl;
            Point intersection = Point(a,b); /// constructing the intersection point
            // cout << intersection.x << " " << intersection.y << "intersection" << endl;

            /**
             * @brief check if the line segments actually intersect without extending
             * 
             */
            if(intersection.check_if_a_point_lies_between_two_points(A,B) && intersection.check_if_a_point_lies_between_two_points(ls.A, ls.B)) {
                return make_pair(1, intersection);
            } else {
                return make_pair(0, Point());
            }
        }
    }


};