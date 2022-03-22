#include <bits/stdc++.h>
#include "LineSegment.h"
using namespace std;

//EPS required for comparing events or not??
// const long double EPS = 1e-15;

class Event
{
    public:
    Point P;
	/**
	 * 0 = horizontal line segment start
	 * 1 = horizontal line segment end
	 * 2 = line segment start
	 * 3 = line segment end
	 * 4 = intersection point
	 */
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
        this -> P = P;
        this -> event_type = event_type;
        this -> event_index = event_index;
    }


    bool operator > (const Event& E) const	
	{
		if(P.y != E.P.y)
			return P.y < E.P.y;
		else {
			if(P.x != E.P.x)
				return P.x > E.P.x;
			else {
				if(event_type != E.event_type)
					return event_type > E.event_type;
				else
					return event_index > E.event_index;
			}
		}
			
	}

    bool operator < (const Event& E) const	
	{
		if(P.y != E.P.y)
			return P.y > E.P.y;
		else {
			if(P.x != E.P.x)
				return P.x < E.P.x;
			else {
				if(event_type != E.event_type)
					return event_type < E.event_type;
				else
					return event_index < E.event_index;
			}
		}
			

	}

    bool operator == (Event &E) 
	{
		return (P == E.P && event_index == E.event_index && event_type == E.event_type);
	}

    bool operator != (Event &E) 
	{
		return !((P == E.P && event_index == E.event_index && event_type == E.event_type));
	}

    

};