#include <bits/stdc++.h>
using namespace std;

class Point
{
    public:
    long double x;
    long double y;

    public:
    Point()
    {
        x = 0;
        y = 0;
    }

    Point(long double x_coord, long double y_coord)
    {
        x = x_coord;
        y = y_coord;
    }

    bool check_if_a_point_lies_between_two_points(Point &A, Point &B)
    {
        bool check_X = x < max(A.x, B.x) && x > min(A.x, B.x);
        bool check_Y = y < max(A.y, B.y) && y > min(A.y, B.y);
        bool check_point = check_X && check_Y;
        return check_point;

    }
};

