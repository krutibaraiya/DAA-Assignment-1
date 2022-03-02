#include <bits/stdc++.h>
#include<Point.h>
using namespace std;

const long double EPS = 1e-15;

class LineSegment
{
    public:
    Point A;
    Point B;
    long double sweep_line;   //sweep-line status
    int count;

    LineSegment()
    {
        count = -1;
    }

    LineSegment(const LineSegment &L)
    {
        A = L.A;
        B = L.B;
        count = L.count;
    }

    LineSegment(Point X, Point Y, int count)
    {
        A = X;
        B = Y;
        count = count;
    }

    long double intersection_of_sweep_line_with_linesegment()
    {
        if(abs(A.y - B.y) < EPS)   //horizontal
            return A.x;
        
        if(abs(A.x - B.x) < EPS)  //vertical 
            return A.x;
        
        long double slope = (B.y - A.y)/(B.x - A.x);

        long double intersection = (sweep_line - (A.y - slope * A.x))/slope; 
        return intersection;
    }

    //todo- intersection with segment and operator overload(?)


};