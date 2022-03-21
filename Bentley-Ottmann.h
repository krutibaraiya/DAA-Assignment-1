#include "Tree.h"
#include "Event.h"
// use template classes (todo)

//Event Queue : Tree<Event>    
//Status Data Str: Tree<LineSegment>   

class BentleyOttmann {
    public:
    Tree<Event> eventQueue;
    Tree<LineSegment> statusQueue;
    BentleyOttmann() {

    }
    Point find_intersection_point(Node<LineSegment*> ls1, Node<LineSegment*> ls2) {
        Point ip = Point();

        return ip;
    }
    void bentleyOttmann(vector<LineSegment> ls) {
        for(int i = 0; i < ls.size(); i++) {
            Event start = Event(ls[i].A, 0, i);
            Event end = Event(ls[i].B, 2, i);
            eventQueue.insert_node(start);
            eventQueue.insert_node(end);
            
        }
        while(eventQueue.no_of_nodes) {
            Node<Event*> temp = eventQueue.extract_min();
            int type = temp.data->event_type;

            if(type == 0) {
                int cur = temp.data->event_index;
                statusQueue.insert_node(ls[cur]);
                Node<LineSegment*> left_neighbour = statusQueue.left_neighbour(ls[cur]);
                Node<LineSegment*> right_neighbour = statusQueue.right_neighbour(ls[cur]);
                Point left_intersection = find_intersection_point(left_neighbour, &ls[cur]);
                Point right_intersection = find_intersection_point(right_neighbour, &ls[cur]);
                Point intersection = find_intersection_point(left_neighbour, right_neighbour);
                if(intersection.x != INT_MIN && intersection.y != INT_MAX) {
                    //Event e = Event(left_intersection, 1, )
                }
                
            } else if(type == 2) {
                int cur = temp.data->event_index;
                statusQueue.delete_node(ls[cur]);
            }
        }
    }
};
