#include <bits/stdc++.h>
using namespace std;
const long double EPS = 1e-15;

class Point
{
    public:
    long double x;
    long double y;

    public:
    Point()
    {
        x = INT_MIN;
        y = INT_MAX;
    }

    Point(long double x_coord, long double y_coord)
    {
        x = x_coord;
        y = y_coord;
    }

    bool check_if_a_point_lies_between_two_points(Point &A, Point &B)
    {
        bool check_X = x < max(A.x, B.x) + EPS && x + EPS > min(A.x, B.x);
        bool check_Y = y < max(A.y, B.y) + EPS && y + EPS > min(A.y, B.y);
        bool check_point = check_X && check_Y;
        return check_point;

    }

    bool operator == (Point &p)
	{
        bool value = abs(x - p.x) < EPS && abs(y - p.y) < EPS;
		return value;
	}
};

