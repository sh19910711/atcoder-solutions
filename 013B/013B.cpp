
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

    typedef set<int> Set;

    const int SIZE = 10001;
    int C;
    int S[SIZE][3];
    Set V;

    class Solution: public ISolution {
    public:
        void init(){ 
            V.clear();
        }
        bool input() {
            if ( ! ( cin >> C ) )
                return false;
            for ( int i = 0; i < C; ++ i )
                cin >> S[i][0] >> S[i][1] >> S[i][2];
            return true;
        }
        int solve() {
            for ( int i = 0; i < C; ++ i )
                sort( S[i], S[i]+3 );
            int a = 0, b = 0, c = 0;
            for ( int i = 0; i < C; ++ i ) {
                a = max( a, S[i][0] );
                b = max( b, S[i][1] );
                c = max( c, S[i][2] );
            }
            return a * b * c;
        }
        void output( int result ) {
            cout << result << endl;
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



