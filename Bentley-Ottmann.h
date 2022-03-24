#include "Tree.h"
#define INF 1e7
#define EPS 1e-6

long double LineSegment::sweep_line = 1000000000; /// sweep_line status

/**
 * @brief BentleyOttmann class
 * 
 */
class BentleyOttmann {
    public:
    vector <LineSegment> lineSegments, reinsertLS, concurrentLineSegments; /// vectors of line segment
    vector <Point> neighbours; /// vector to store points whose neighbours are to be checked for new events
    LineSegment* horizontal; /// pointer to the horizontal line segment
    LineSegment* secondHorizontal; /// pointer to the next horizontal line segment
    Tree <Event> eventQueue; /// AVL tree of Event class - Event Queue data structure
    Tree <LineSegment> statusQueue; /// AVL tree of Line - Status data structure
    vector <Output> output; /// vector to store the output
    
    /**
     * @brief Construct a new Bentley Ottmann object
     * 
     */
    BentleyOttmann() {

    }

    /**
     * @brief Construct a new Bentley Ottmann object
     * 
     * @param lineSegments 
     */
    BentleyOttmann(vector <LineSegment> lineSegments) {
        this -> lineSegments = lineSegments;
        this -> horizontal = NULL;
        this -> secondHorizontal = NULL;

        // for(auto i: lineSegments) {
        //     cout << i.A.x << " " << i.A.y << " " << i.B.x << " " << i.B.y << endl;
        // }
    }

    /**
     * @brief method to check if tree is empty or not
     * 
     * @return true if tree is empty
     * @return false if tree is not empty
     */
    bool isEmpty(Tree<Event>) {
        return eventQueue.no_of_nodes == 0;
    }
    
    /**
     * @brief method to find the intersection points with the horizontal line segment
     * 
     */
    void findIntersectionsWithHorizontalSegment() {
        LineSegment ls = LineSegment(*horizontal);
        ls.index = -1;
        LineSegment *intersectionPoint;
        while(intersectionPoint = statusQueue.right_neighbour(ls)) { /// finding the right neighbour in the status tree
            long double xIntersection = intersectionPoint -> intersection_of_sweep_line_with_linesegment();
            if(xIntersection < horizontal -> B.x - EPS) { /// if the intersection point exists with the horizontal line segment
                concurrentLineSegments.push_back(*intersectionPoint);
                printIntersectionPoint(xIntersection, ls.sweep_line); /// printing the intersection point
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

    /**
     * @brief method to find intersection point
     * 
     * @param p point p
     * @return int 
     */
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

    /**
     * @brief method to insert new line segment in status tree
     * 
     * @param ls line segment to be inserted in the status tree
     */
    void insertIntoStatusQueue(LineSegment &ls) {
        LineSegment ls1 = LineSegment(ls);
        ls1.index = 5;
        LineSegment *leftNeighbour = statusQueue.left_neighbour(ls1);
        ls1.index = -1;
        LineSegment *rightNeighbour = statusQueue.right_neighbour(ls1);

        pair <bool, Point> intersectionPoint; /// intersection point with the neighbours
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
        statusQueue.insert_node(ls); /// insert line segment into status tree

        return;
    }

    /**
     * @brief Get the New Event object
     * 
     * @param p point of the event
     * @param sl sweep line
     */
    void getNewEvent(Point p, LineSegment &sl) {

        auto makeQueryNode = [&sl](Point p) {
            sl.A.x = p.x - 0.05;
            sl.A.y = p.y + 0.05;
            sl.B.x = p.x + 0.05;
            sl.B.y = p.y - 0.05;
            return;
        };
        
        makeQueryNode(p);
        LineSegment* leftNeighbour = statusQueue.left_neighbour(sl);
        LineSegment* rightNeighbour = statusQueue.right_neighbour(sl);

        pair <bool, Point> intersectionPoint;

        if(leftNeighbour && rightNeighbour) { // if left and right neighbour exists
            intersectionPoint = leftNeighbour -> intersection_with_linesegment(*rightNeighbour);
            if(intersectionPoint.first && intersectionPoint.second.y < sl.sweep_line - EPS && findIntersectionPoint(intersectionPoint.second) == 0) {
                eventQueue.insert_node(Event(intersectionPoint.second, 4, INF)); 
            }
        }
    }

    /**
     * @brief method to print intersection point
     * 
     * @param x x coordinate of the intersection point
     * @param y y coordinate of the intersection point
     */
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

    /**
     * @brief method to insert new events in the eventQueue
     * 
     * @param sl sweep line
     */
    void insertNewEvents(LineSegment &sl) {
        while(neighbours.size()) {
            getNewEvent(neighbours.back(), sl);
            neighbours.pop_back();
        }
        return;
    }

    /**
     * @brief method to re insert line segments in status tree
     * 
     */
    void reinsertLineSegments() {
        while(reinsertLS.size()) {
            insertIntoStatusQueue(reinsertLS.back());
            reinsertLS.pop_back();
        }
        return;
    }

    /**
     * @brief method to remove duplicate event points
     * 
     * @param event event whose duplicates are to be removed
     */
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

    /**
     * @brief Get all Line Segments Passing Through This Event Point object
     * 
     * @param x x coordinate of the event point
     * @param sl sweep line
     */
    void getAllLineSegmentsPassingThroughThisEventPoint(long double x, LineSegment &sl) {
        LineSegment *currentUB;
        /**
         * @brief generating a query node for sweep line to find intersection
        * 
        * @param x x coordinate of the event point
        * @param sl sweep line
        */
        auto makeQueryNode = [&sl](int x) {
            long double newX = x;
            newX -= EPS;
            sl.A.x = newX - 1;
            sl.B.x = newX + 1;
            sl.A.y = sl.sweep_line + 1;
            sl.B.y = sl.sweep_line - 1;
            return;
        };
        makeQueryNode(x);
        while (currentUB = statusQueue.upperBound(sl))
        {

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

    /**
     * @brief method to process all the line segments at this event point
     * 
     * @param x x coordinate of the event point
     * @param y y coordinate of the event point
     */
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

    /**
     * @brief main algorithm
     * 
     */
    void bentleyOttmann() {
        cout << fixed << setprecision(10);
        // cout << "calling bentley" << endl;
        // for(auto i: lineSegments) {
        //     cout << i.A.x << " " << i.A.y << " " << i.B.x << " " << i.B.y << endl;
        // }
        LineSegment sl = LineSegment(1e10);
        for(int i = 0; i < lineSegments.size(); i++) {
            LineSegment current(lineSegments[i]);
            if(abs(current.A.y - current.B.y) < EPS) { /// if line segment is horizontal
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
