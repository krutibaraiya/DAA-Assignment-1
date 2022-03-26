#include <bits/stdc++.h>
#include "Output.h"

using namespace std;


/**
 * @brief Event class
 * 
 */
class Event
{
    public:
    Point P; /// Event point
	/**
	 * 0 = horizontal line segment start
	 * 1 = horizontal line segment end
	 * 2 = line segment start
	 * 3 = line segment end
	 * 4 = intersection point
	 */
    int event_type;
    int event_index; /// index of the line segment containing event point


    public:
	/**
	 * @brief Construct a new Event object
	 * 
	 */
    Event()
    {
        event_type = -1;
        event_index = 0;
    }

	/**
	 * @brief Construct a new Event object
	 * 
	 * @param P Event point
	 * @param event_type type of the event
	 * @param event_index index of the line segment 
	 */
    Event(Point P, int event_type, int event_index)
    {
        this -> P = P;
        this -> event_type = event_type;
        this -> event_index = event_index;
    }

	/**
	 * @brief operator overloading for >
	 * 
	 * @param E event to be compared
	 * @return true if the event is greater than the compared event
	 * @return false if the event is smaller than the compared event
	 */
    bool operator > (const Event& E) const	
	{
		return ({
			(P.y != E.P.y) ? (P.y < E.P.y) : ({
				(P.x != E.P.x) ? (P.x > E.P.x) : ({
					(event_type != E.event_type) ? (event_type > E.event_type) : (event_index > E.event_index);
				});
			});
		});
			
	}

	
	/**
	 * @brief 	
	 * 
	 * @param E event to be compared with
	 * @return true if this event is smaller than the compared event
	 * @return false otherwise
	 */
    bool operator < (const Event& E) const	
	{
		return ({
			(P.y != E.P.y) ? (P.y > E.P.y) : ({
				(P.x != E.P.x) ? (P.x < E.P.x) : ({
					(event_type != E.event_type) ? (event_type < E.event_type) : (event_index < E.event_index);
				});
			});
		});
			

	}
		
	/**
	 * @brief operator overloading for ==
	 * 
	 * @param E event to be compared
	 * @return true if both events are equal
	 * @return false if both events are not equal
	 */
    bool operator == (Event &E) 
	{
		return (P == E.P && event_index == E.event_index && event_type == E.event_type);
	}
	
	/**
	 * @brief operator overloading for !=
	 * 
	 * @param E event to be compared with
	 * @return true if both events are not equal
	 * @return false if both events are equal
	 */
    bool operator != (Event &E) 
	{
		return !((P == E.P && event_index == E.event_index && event_type == E.event_type));
	}

    

};