#include "LineSegment.h"

class Output {
    public:

    Point p;
    vector <LineSegment> ls;

    Output() {

    }
    Output(Point p, vector <LineSegment> ls) {
        this -> p = p;
        this -> ls = ls;
    }

    void print() {
        //freopen("output.txt", "w", stdout);
        cout << fixed << setprecision(6);
        cout << "------------------------------------------------------------" << endl;
        cout <<  "Intersection Point: (" << p.x << ") (" << p.y << ") " << endl;
        for(auto l: ls) {
            cout << "Index of line segment " << l.index + 1 << " " << endl;
            cout << "Point A: (" << l.A.x << ", " << l.A.y << ") Point B: (" << l.B.x << ", " << l.B.y << ") " << endl;  
        }
        cout << "-----------------------------------------------------------" << endl;
    }

};