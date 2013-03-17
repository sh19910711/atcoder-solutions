
// @snippet<sh19910711/contest:headers.cpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <complex>
#include <functional>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
    class ISolution {
    public:
        virtual void init() {};
        virtual bool input() { return false; };
        virtual void output() {};
        virtual int run() = 0;
    };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
    typedef std::istringstream ISS;
    typedef std::ostringstream OSS;
    typedef std::vector<std::string> VS;
    typedef long long LL;
    typedef int INT;
    typedef std::vector<INT> VI;
    typedef std::vector<VI> VVI;
    typedef std::pair<INT,INT> II;
    typedef std::vector<II> VII;
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
    using namespace std;

    typedef set<II> Set;

    const int INF = std::numeric_limits<int>::max();
    const int SIZE = 1011;
    const string YES = "WIN";
    const string NO = "LOSE";
    int N;
    int TX[SIZE], TY[SIZE], TZ[SIZE];
    int M[SIZE];
    int HX[SIZE][SIZE], HY[SIZE][SIZE], HZ[SIZE][SIZE];

    class Solution: public ISolution {
    public:
        bool input() {
            if ( ! ( cin >> N ) )
                return false;
            for ( int i = 0; i < N; ++ i ) {
                cin >> TX[i] >> TY[i] >> TZ[i];
                cin >> M[i];
                for ( int j = 0; j < M[i]; ++ j ) {
                    cin >> HX[i][j] >> HY[i][j] >> HZ[i][j];
                }
            }
            return true;
        }
        bool solve() {
            LL sum = 0;
            for ( int i = 0; i < N; ++ i ) {
                int x = TX[i], y = TY[i], z = TZ[i];
                int hxl = INF, hxr = -1, hyl = INF, hyr = -1, hzl = INF, hzr = -1;
                for ( int j = 0; j < M[i]; ++ j ) {
                    int hx = HX[i][j];
                    int hy = HY[i][j];
                    int hz = HZ[i][j];
                    hxl = min( hxl, hx );
                    hxr = max( hxr, hx );
                    hyl = min( hyl, hy );
                    hyr = max( hyr, hy );
                    hzl = min( hzl, hz );
                    hzr = max( hzr, hz );
                }
                sum ^= hxl;
                sum ^= x - hxr - 1;
                sum ^= hyl;
                sum ^= y - hyr - 1;
                sum ^= hzl;
                sum ^= z - hzr - 1;
            }
            return sum != 0;
        }
        void output( bool result ) {
            cout << ( result ? YES : NO ) << endl;
        }
        int run() {
            while ( init(), input() ) {
                output(solve());
            }
            return 0;
        }
    };
}

// @snippet<sh19910711/contest:main.cpp>

int main() {
    return solution::Solution().run();
}



