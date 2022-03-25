#include <bits/stdc++.h>

using namespace std;

int32_t main() {
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    srand(static_cast<unsigned>(time(0)));
    int n = 300;
    cout << n << "\n";
    const long double LO = 0;
    const long double HI = 1e2;
    long double cur = LO + static_cast<long double>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
    for (int i = 0; i < n; ++i) {
        long double x1 = LO + static_cast<long double>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
        long double y1 = LO + static_cast<long double>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
        long double x2 = LO + static_cast<long double>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
        long double y2 = LO + static_cast<long double>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
        x1 = rand() % 100;
        y1 = rand() % 100;
        x2 = rand() % 100;
        y2 = rand() % 100;
        cout << fixed << setprecision(4) << x1 << " " << y1 << " " << x2 << " " << y2;
        cout << '\n';
    }
    return 0;
}
