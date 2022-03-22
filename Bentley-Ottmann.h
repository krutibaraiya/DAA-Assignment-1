#include "Tree.h"
#include "Event.h"
#define INF 1e9
// use template classes (todo)

//Event Queue : Tree<Event>    
//Status Data Str: Tree<LineSegment>   

class BentleyOttmann {
    public:
    vector <LineSegment> lineSegments, reinsertLS, concurrentLineSegments;
    vector <Point> neighbours;
    LineSegment* horizontal;
    LineSegment* secondHorizontal;
    vector < pair < long double, long double > > output_intersections;
    Tree <Event> eventQueue;
    Tree <LineSegment> statusQueue;

    BentleyOttmann() {

    }
    BentleyOttmann(vector <LineSegment> lineSegments) {
        this -> lineSegments = lineSegments;
        this -> horizontal = NULL;
        this -> secondHorizontal = NULL;
    }

    bool isEmpty(Tree<Event>) {
        return eventQueue.no_of_nodes == 0;
    }
    void findIntersectionsWithHorizontalSegment() {


        return;
    }
    void insertIntoStatusQueue(LineSegment &ls) {

    }
    void getNewEvent(Point p, LineSegment &sl) {

    }
    void printIntersectionPoint(long double x, long double y) {

        return;
    }
    void insertNewEvents(LineSegment &sl) {
        while(neighbours.size()) {
            getNewEvent(neighbours.back(), sl);
            neighbours.pop_back();
        }
        return;
    }
    void reinsertLineSegments() {
        while(reinsertLS.size()) {
            insertIntoStatusQueue(reinsertLS.back());
            reinsertLS.pop_back();
        }
        return;
    }
    void removeDuplicateEventPoints(Event event) {
        event.event_index = -INF;
        event.event_type = -INF;
        Event *currentUB;

        while(currentUB = eventQueue.upperBound(event)) {

            if(abs(currentUB -> P.x - event.P.x) > EPS || abs(currentUB -> P.y - event.P.y) > EPS) {
                break;
            } else {
                if(currentUB -> event_type == 0) {
                    secondHorizontal = &lineSegments[currentUB -> event_index];
                } else if(currentUB -> event_type == 2) {
                    statusQueue.insert_node(lineSegments[currentUB -> event_index]);
                }
                eventQueue.delete_node(*currentUB);
            }
        }
        return;
    }

    void getAllLineSegmentsPassingThroughThisEventPoint(long double x, LineSegment &sl) {
        LineSegment *currentUB;

        long double newX = x;
        newX -= EPS;
        sl.A.x = newX - 1;
        sl.B.x = newX + 1;
        sl.A.y = sl.sweep_line + 1;
        sl.B.y = sl.sweep_line - 1;

        while(currentUB = statusQueue.upperBound(sl)) {

            long double xIntersection = currentUB -> intersection_of_sweep_line_with_linesegment();

            if(abs(x - xIntersection) > EPS) {
                return;
            }

            LineSegment ls = LineSegment(*currentUB);
            statusQueue.deleteUpperBound(sl);
            concurrentLineSegments.emplace_back(ls);

        }
        return;
    }
    void processAllSegmentsAtThisEventPoint(long double x, long double y) {

        int doHorizontalExist = (horizontal != NULL);
        doHorizontalExist += (secondHorizontal != NULL);

        int noOfIntersections = concurrentLineSegments.size() + doHorizontalExist;
        if(noOfIntersections > 1) {
            printIntersectionPoint(x,y);
        }

        bool ifLowerExist = true;
        for(auto ls: concurrentLineSegments) {
            if(abs(ls.B.y - ls.sweep_line) > EPS) {
                reinsertLS.emplace_back(ls);
                ifLowerExist = false;
            }
        }
        concurrentLineSegments.clear();
        if(ifLowerExist) {
            neighbours.emplace_back(Point(x,y));
        }


        
        return;
    }
    void bentleyOttmann() {
        LineSegment sl = LineSegment(1e10);

        for(int i = 0; i < lineSegments.size(); i++) {
            LineSegment current(lineSegments[i]);
            if(abs(current.A.y - current.B.y) < EPS) { // if line segment is horizontal
                Event e1(current.A, 0, i);
                Event e2(current.B, 1, i);
                eventQueue.insert_node(e1);
                eventQueue.insert_node(e2);
            } else {
                Event e1(current.A, 2, i);
                Event e2(current.B, 3, i);
                eventQueue.insert_node(e1);
                eventQueue.insert_node(e2);     
            }
        }

        while(!isEmpty(eventQueue)) {

            Event current = *eventQueue.extract_min();
            if(abs(current.P.y - sl.sweep_line) > EPS) {
                sl.sweep_line  = sl.sweep_line - EPS;
                reinsertLineSegments();
                insertNewEvents(sl);
            }

            current = *eventQueue.extract_min();
            current = Event(current);
            sl.sweep_line = current.P.y;

            bool horizontalStatus = false;

            if(current.event_type == 0 || current.event_type == 1) {
                if(horizontal) {
                    findIntersectionsWithHorizontalSegment();
                    horizontalStatus = true;
                }
            } else {
                horizontal = &lineSegments[current.event_index];
                eventQueue.delete_node(current);
                continue;
            }

            removeDuplicateEventPoints(current);
            getAllLineSegmentsPassingThroughThisEventPoint(current.P.x, sl);
            processAllSegmentsAtThisEventPoint(current.P.x, sl.sweep_line);

            if(horizontalStatus) {
                horizontal = NULL;
                if(secondHorizontal) {
                    horizontal = &(*secondHorizontal);
                }
                secondHorizontal = NULL;
            }

        }

        return;
    }
};
