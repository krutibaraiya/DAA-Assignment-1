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


    bool operator > (const Event& E) const	
	{
		if(P.y != E.P.y)
			return P.y < E.P.y;
		else
			if(P.x != E.P.x)
				return P.x > E.P.x;
			else
				if(event_type != E.event_type)
					return event_type > E.event_type;
				else
					return event_index > E.event_index;
	}

    bool operator < (const Event& E) const	
	{
		if(P.y != E.P.y)
			return P.y > E.P.y;
		else
			if(P.x != E.P.x)
				return P.x < E.P.x;
			else
				if(event_type != E.event_type)
					return event_type < E.event_type;
				else
					return event_index < E.event_index;
	}

    bool operator == (Event &E) 
	{
		if(P == E.P && event_index == E.event_index && event_type == E.event_type)
			return true;
		else
			return false;
	}

    bool operator != (Event &E) 
	{
		if(P == E.P && event_index == E.event_index && event_type == E.event_type)
			return false;
		else
			return true;
	}

    

};