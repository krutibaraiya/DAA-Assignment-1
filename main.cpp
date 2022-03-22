#include <bits/stdc++.h>
#include "Bentley-Ottmann.h"


using namespace std;


int32_t main() {

    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int n;
    cin >> n;
    long double x1, x2, y1, y2;

    vector <LineSegment> lineSegments;
    Tree<LineSegment> tls;
    for(int i = 0; i < n; i++) {
        cin >> x1 >> y1 >> x2 >> y2;

        Point A = Point(x1, y1);
        Point B = Point(x2, y2);

        if(abs(A.y - B.y) > EPS) {
            if(A.y < B.y) {
                swap(A,B);
            } 
        } else {
            if(A.x > B.x) {
                swap(A,B);
            }
        }
        LineSegment ls = LineSegment(A, B, i);
        lineSegments.push_back(ls);
    } 

    BentleyOttmann bo(lineSegments);

    vector <Output> finalOuptut = bo.output;
    for(auto i: finalOuptut) {
        i.print();
    }
    
    

    return 0;
}