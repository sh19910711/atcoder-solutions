
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

    const int INF = std::numeric_limits<int>::max();
    const int NONE = -1;
    int n, m, l;
    int p, q, r;

    int calc( int n, int m, int l, int p, int q, int r ) {
        if ( n < p || m < q || l < r )
            return NONE;
        int a = n / p;
        int b = m / q;
        int c = l / r;
        return a * b * c;
    }

    class Solution: public ISolution {
    public:
        bool input() {
            return cin >> n >> m >> l >> p >> q >> r;
        }
        int solve() {
            int a[3] = { n, m, l };
            int b[3] = { p, q, r };
            sort( a, a+3 );
            sort( b, b+3 );
            int res = 0;
            do {
                do {
                    res = max( res, calc( a[0], a[1], a[2], b[0], b[1], b[2] ) );
                } while ( next_permutation( b, b+3 ) );
            } while ( next_permutation( a, a+3 ) );
            return res;
        }
        int run() {
            while ( init(), input() ) {
                cout << solve() << endl;
            }
            return 0;
        }
    };
}

// @snippet<sh19910711/contest:main.cpp>

int main() {
    return solution::Solution().run();
}



