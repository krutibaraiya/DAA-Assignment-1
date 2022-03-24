#include <bits/stdc++.h>
#include "Bentley-Ottmann.h"

using namespace std;


int32_t main() {

    
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    

    int n; // number of line segments
    cin >> n;
    long double x1, x2, y1, y2;

    vector <LineSegment> lineSegments; // vector to store all line segments

    for(int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;

        /**
         * @brief constructing Point from coordinates 
         * 
         */
        Point A = Point(x1, y1); 
        Point B = Point(x2, y2);

        /**
         * @brief Assigning Point A as the starting point of line segment and Point B as the ending point of the line segment
         * 
         */
        if(abs(A.y - B.y) > EPS) {
            if(A.y < B.y) {
                swap(A,B);
            } 
        } else {
            if(A.x > B.x) {
                swap(A,B);
            }
        }
        /**
         * @brief Constructing line segment from two points
         * 
         */
        LineSegment ls = LineSegment(A, B, i);
        /**
         * @brief Adding the constructed line segment into the vector
         * 
         */
        lineSegments.push_back(ls);
    } 

    /**
     * @brief Creating object for class BentleyOttmann
     * 
     * @return BentleyOttmann 
     */
    BentleyOttmann bo(lineSegments);

    /**
     * @brief calling bentley-ottmann algorithm to find all intersection points
     * 
     */
    bo.bentleyOttmann();

    /**
     * @brief Printing output in a text file
     * 
     */
    vector <Output> finalOutput = bo.output;
    for(auto i: finalOutput) {
        i.print();
    }
    
    

    return 0;
}