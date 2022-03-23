#include "Tree.h"
#define INF 1e7
#define EPS 1e-6
// use template classes (todo)

//Event Queue : Tree<Event>    
//Status Data Str: Tree<LineSegment>   
long double LineSegment::sweep_line = 1000000000;
class BentleyOttmann {
    public:
    vector <LineSegment> lineSegments, reinsertLS, concurrentLineSegments;
    vector <Point> neighbours;
    LineSegment* horizontal;
    LineSegment* secondHorizontal;
    Tree <Event> eventQueue;
    Tree <LineSegment> statusQueue;
    vector <Output> output;
    
    BentleyOttmann() {

    }
    BentleyOttmann(vector <LineSegment> lineSegments) {
        this -> lineSegments = lineSegments;
        this -> horizontal = NULL;
        this -> secondHorizontal = NULL;

        // for(auto i: lineSegments) {
        //     cout << i.A.x << " " << i.A.y << " " << i.B.x << " " << i.B.y << endl;
        // }
    }

    bool isEmpty(Tree<Event>) {
        return eventQueue.no_of_nodes == 0;
    }
    void findIntersectionsWithHorizontalSegment() {
        LineSegment ls = LineSegment(*horizontal);
        ls.index = -1;
        LineSegment *intersectionPoint;
        while(intersectionPoint = statusQueue.right_neighbour(ls)) {
            long double xIntersection = intersectionPoint -> intersection_of_sweep_line_with_linesegment();
            if(xIntersection < horizontal -> B.x - EPS) {
                concurrentLineSegments.push_back(*intersectionPoint);
                printIntersectionPoint(xIntersection, ls.sweep_line);
                concurrentLineSegments.clear();
                ls.A.x = intersectionPoint -> A.x;
                ls.B.x = intersectionPoint -> B.x;
                ls.A.y = intersectionPoint -> A.y;
                ls.B.y = intersectionPoint -> B.y;
            } else {
                break;
            }
        }

        return;
    }
    int findIntersectionPoint(Point p) {
        p.x = p.x + EPS;
        Event event = Event(p, 4, INF);
        p.x = p.x - EPS;

        Event *intersection;
        intersection = eventQueue.left_neighbour(event);
        if(intersection) {
            if(abs(p.x - intersection -> P.x) < EPS && abs(p.y - intersection -> P.y) < EPS && intersection -> event_type == 4) {
                return 1;
            }
        }
        return 0;
    }
    void insertIntoStatusQueue(LineSegment &ls) {
        LineSegment ls1 = LineSegment(ls);
        ls1.index = 5;
        LineSegment *leftNeighbour = statusQueue.left_neighbour(ls1);
        ls1.index = -1;
        LineSegment *rightNeighbour = statusQueue.right_neighbour(ls1);

        pair <bool, Point> intersectionPoint;
        if(leftNeighbour) {
            intersectionPoint = ls.intersection_with_linesegment(*leftNeighbour);
            if(intersectionPoint.first && intersectionPoint.second.y < ls.sweep_line - EPS && findIntersectionPoint(intersectionPoint.second) == 0) {
                eventQueue.insert_node(Event(intersectionPoint.second, 4, INF));
            }
        }
        if(rightNeighbour) {
            intersectionPoint = ls.intersection_with_linesegment(*rightNeighbour);
            if(intersectionPoint.first && intersectionPoint.second.y < ls.sweep_line - EPS && findIntersectionPoint(intersectionPoint.second) == 0) {
                eventQueue.insert_node(Event(intersectionPoint.second, 4, INF));
            }
        }
        statusQueue.insert_node(ls);

        return;
    }
    void getNewEvent(Point p, LineSegment &sl) {
        
        sl.A.x = p.x - 0.1;
        sl.A.y = p.y + 0.1;
        sl.B.x = p.x + 0.1;
        sl.B.y = p.y - 0.1;

        LineSegment* leftNeighbour = statusQueue.left_neighbour(sl);
        LineSegment* rightNeighbour = statusQueue.right_neighbour(sl);

        pair <bool, Point> intersectionPoint;

        if(leftNeighbour && rightNeighbour) {
            intersectionPoint = leftNeighbour -> intersection_with_linesegment(*rightNeighbour);
            if(intersectionPoint.first && intersectionPoint.second.y < sl.sweep_line - EPS && findIntersectionPoint(intersectionPoint.second) == 0) {
                eventQueue.insert_node(Event(intersectionPoint.second, 4, INF)); 
            }
        }

    }
    void printIntersectionPoint(long double x, long double y) {
        // cout << "in intersection " << x << " " << y << endl;
        Point p(x,y);
        vector <LineSegment> ls(concurrentLineSegments.begin(), concurrentLineSegments.end());
        if(horizontal) {
            ls.push_back(*horizontal);
        }
        if(secondHorizontal) {
            ls.push_back(*secondHorizontal);
        }
        Output out(p, ls);
        output.push_back(out);
        
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
        event.event_index = -1;
        event.event_type = -1;
        Event *currentUB;
        while(currentUB = eventQueue.upperBound(event)) {
            //cout << "event " << event.P.x << " " << event.P.y << endl;
            //cout << "current upper bound " << currentUB -> P.x << " " << currentUB -> P.y << endl;
            if(abs(currentUB -> P.x - event.P.x) > EPS || abs(currentUB -> P.y - event.P.y) > EPS) {
                break;
            } else {
                if(currentUB -> event_type == 0) {
                    secondHorizontal = &lineSegments[currentUB -> event_index];
                } else if(currentUB -> event_type == 2) {
                    statusQueue.insert_node(lineSegments[currentUB -> event_index]);
                    // cout << "after removing" << endl;
                    // statusQueue.display();
                }
                // cout << "before removing" << endl;
                //     eventQueue.display();
                eventQueue.delete_node(*currentUB);
                // cout << "after removing" << endl;
                //     eventQueue.display();
            
            }
        }
        //statusQueue.display();
        //eventQueue.display();
        return;
    }
    void makeQueryNode(long double x, LineSegment &sl) {
        long double newX = x;
        newX -= EPS;
        sl.A.x = newX - 1;
        sl.B.x = newX + 1;
        sl.A.y = sl.sweep_line + 1;
        sl.B.y = sl.sweep_line - 1;
        return ;
    }
    void getAllLineSegmentsPassingThroughThisEventPoint(long double x, LineSegment &sl) {
        LineSegment *currentUB;
        // long double newX = x;
        // newX -= EPS;
        // sl.A.x = newX - 1;
        // sl.B.x = newX + 1;
        // sl.A.y = sl.sweep_line + 1;
        // sl.B.y = sl.sweep_line - 1;
        makeQueryNode(x, sl);

        while(currentUB = statusQueue.upperBound(sl)) {

            long double xIntersection = currentUB -> intersection_of_sweep_line_with_linesegment();

            if(abs(x - xIntersection) > EPS) {
                return;
            }

            LineSegment ls = LineSegment(*currentUB);
            // cout << "before deleting" << endl;
            // statusQueue.display();
            statusQueue.deleteUpperBound(sl);
            // cout << "after deleting" << endl;
            // statusQueue.display();
            concurrentLineSegments.push_back(ls);
            // for(auto i: concurrentLineSegments) {
            //     cout << i.A.x << " " << i.A.y << " " << i.B.x << " " << i.B.y << endl;
            // }

        }
        // cout << "after finding" << endl;
        // statusQueue.display();
        return;
    }
    void processAllSegmentsAtThisEventPoint(long double x, long double y) {

        int doHorizontalExist = (horizontal != NULL);
        doHorizontalExist += (secondHorizontal != NULL);

        int noOfIntersections = concurrentLineSegments.size() + doHorizontalExist;
        // cout << "no. of intersecctions " << noOfIntersections << endl;
        if(noOfIntersections > 1) {
            printIntersectionPoint(x,y);
        }

        bool ifLowerExist = true;
        for(auto ls: concurrentLineSegments) {
            if(abs(ls.B.y - ls.sweep_line) < EPS) {
                
            } else {
                reinsertLS.push_back(ls);
                ifLowerExist = false;
            }
        }
        concurrentLineSegments.clear();
        if(ifLowerExist) {
            neighbours.push_back(Point(x,y));
        }


        
        return;
    }
    void bentleyOttmann() {
        cout << fixed << setprecision(10);
        // cout << "calling bentley" << endl;
        // for(auto i: lineSegments) {
        //     cout << i.A.x << " " << i.A.y << " " << i.B.x << " " << i.B.y << endl;
        // }
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
        // eventQueue.display();
        // cout << "Event queue over" << endl;
        while(!isEmpty(eventQueue)) {

            Event current = *eventQueue.extract_min();
            //cout << "current.Point " << current.P.x << " " << current.P.y << endl;
            if(abs(current.P.y - sl.sweep_line) > EPS) {
                sl.sweep_line  = sl.sweep_line - EPS;
                // cout << sl.sweep_line << endl;
                reinsertLineSegments();
                insertNewEvents(sl);
            }
            current = *eventQueue.extract_min();
            current = Event(current);
            sl.sweep_line = current.P.y;
            // cout << sl.sweep_line << endl;
            bool horizontalStatus = false;
            if(current.event_type == 0 || current.event_type == 1) {
                if(horizontal) {
                    // cout << "before finding horizontal intersection" << endl;
                    findIntersectionsWithHorizontalSegment();
                    // cout << "after finding horizontal intersection" << endl;
                    horizontalStatus = true;
                } else {
                horizontal = &lineSegments[current.event_index];
            //     cout << "before deleting" << endl;
            // eventQueue.display();
                eventQueue.delete_node(current);
            //     cout << "after deleting" << endl;
            // eventQueue.display();
                continue;
                }
            } 
            removeDuplicateEventPoints(current);
            // cout << sl.sweep_line << endl;
            getAllLineSegmentsPassingThroughThisEventPoint(current.P.x, sl);
            // cout << sl.sweep_line << endl;
            processAllSegmentsAtThisEventPoint(current.P.x, sl.sweep_line);
            // cout << sl.sweep_line << endl;

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
