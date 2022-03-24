#include "LineSegment.h"

/**
 * @brief Output class
 * 
 */
class Output {
    public:

    Point p; /// point p
    vector <LineSegment> ls; /// vector of line segments    

    /**
     * @brief Construct a new Output object
     * 
     */
    Output() {

    }

    /**
     * @brief Construct a new Output object
     * 
     * @param p intersection point
     * @param ls line segment containing the point
     */
    Output(Point p, vector <LineSegment> ls) {
        this -> p = p;
        this -> ls = ls;
    }

    /**
     * @brief method to print the output
     * 
     */
    void print() {
        //freopen("output.txt", "w", stdout);
        cout << fixed << setprecision(6);
        cout << "------------------------------------------------------------" << endl;
        cout <<  "Intersection Point: (" << p.x << ", " << p.y << ") " << endl;
        for(auto l: ls) {
            cout << "Index of line segment " << l.index + 1 << " " << endl;
            cout << "Point A: (" << l.A.x << ", " << l.A.y << ") Point B: (" << l.B.x << ", " << l.B.y << ") " << endl;  
        }
        cout << "-----------------------------------------------------------" << endl;
    }

};