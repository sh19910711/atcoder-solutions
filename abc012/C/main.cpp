#include <iostream>
using namespace std;

typedef long long Int;

Int S;
Int N;

void init() {
    S = 0;
    for ( int i = 1; i <= 9; ++ i ) {
        for ( int j = 1; j <= 9; ++ j ) {
            S += i * j;
        }
    }
}

void solve() {
    Int E = S - N;
    for ( int i = 1; i <= 9; ++ i ) {
        for ( int j = 1; j <= 9; ++ j ) {
            if ( i * j == E ) {
                cout << i << " x " << j << endl;
            }
        }
    }
}

int main() {
    init();
    while ( cin >> N ) {
        solve();
    }
    return 0;
}