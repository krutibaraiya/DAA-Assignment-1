#include <bits/stdc++.h>
using namespace std;
/**
 * @brief Epsilon to compare two equal points
 * 
 */
const long double EPS = 0.00000000000002;

/**
 * @brief Point class
 * 
 */
class Point
{
    public:

    /**
     * @param x X coordinate of the point
     * @param y Y coordinate of the point
     */
    long double x;
    long double y;

    public:

    /**
     * @brief Construct a new Point object
     * 
     */
    Point()
    {
        x = 0;
        y = 0;
    }

    /**
     * @brief Construct a new Point object
     * 
     * @param x_coord x coordinate of the point
     * @param y_coord y coordinate of the point
     */
    Point(long double x_coord, long double y_coord)
    {
        x = x_coord;
        y = y_coord;
    }


    /**
     * @brief method to check if a point lies between two points
     * 
     * @param A Point A
     * @param B Point B
     * @return true If point exists between two points
     * @return false If point does not exist between two points
     */
    bool check_if_a_point_lies_between_two_points(Point &A, Point &B)
    {   
        bool checkX1 = x < max(A.x, B.x) + EPS;
        bool checkX2 = x + EPS > min(A.x, B.x);
        bool checkY1 = y < max(A.y, B.y) + EPS;
        bool checkY2 = y + EPS > min(A.y, B.y);
        // bool check_X = x < max(A.x, B.x) + EPS && x + EPS > min(A.x, B.x);
        // bool check_Y = y < max(A.y, B.y) + EPS && y + EPS > min(A.y, B.y);
        bool check_X = checkX1 && checkX2;
        bool check_Y = checkY1 && checkY2;
        bool check_point = check_X && check_Y;
        return check_point;

    }

    /**
     * @brief overloading == operator
     * 
     * @param p Point p
     * @return true if both points are equal
     * @return false if both points are not equal
     */
    bool operator == (Point &p)
	{
        bool value = abs(x - p.x) < EPS && abs(y - p.y) < EPS;
		return value;
	}
};

