#include <bits/stdc++.h>
#include<Point.h>
#include<LineSegment.h>
using namespace std;

//EPS required for comparing events or not??
const long double EPS = 1e-15;

class Event
{
    public:
    Point P;
    int event_type;
    int event_index;


    public:
    Event()
    {
        event_type = -1;
        event_index = 0;
    }

    Event(Point P, int event_type, int event_index)
    {
        P = P;
        event_type = event_type;
        event_index = event_index;
    }

    //Todo: Comparing Events - >, < (use Operator overload)

};