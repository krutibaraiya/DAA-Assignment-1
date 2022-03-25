#include <bits/stdc++.h>
#include "Bentley-Ottmann.h"
#define eps 0.000001
using namespace std;
using namespace std::chrono;

/**
 * Structure to measure the running time of algorithm
 */
struct Timer {
    string name{""};
    time_point<high_resolution_clock> end, start{high_resolution_clock::now()};
    std::chrono::duration<float, std::milli> duration;
    Timer() = default;
    Timer(string name) : name(name) {}
    ~Timer()
    {
        end = high_resolution_clock::now();
        duration = end - start;
        cout << "@" << name << "> " << duration.count() << " ms" << '\n';
    }
};

int32_t main() {
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    freopen("./Test/input_test.txt", "r", stdin);
    freopen("./Test/output_test.txt", "w", stdout);
    
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
        if(abs(A.y - B.y) > eps) {
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
        lineSegments.emplace_back(ls);
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
    Timer timer("Calling Bentley");
    bo.bentleyOttmann();
    this_thread::sleep_for(chrono::milliseconds(100));
    /**
     * @brief Printing output in a text file
     * 
     */
    vector <Output> finalOutput = bo.output;
    cout << bo.ans << endl;
    // for(auto i: finalOutput) {
    //     i.print();
    // }
    return 0;
}