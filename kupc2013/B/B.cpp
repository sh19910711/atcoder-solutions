
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
    virtual int run() = 0;
    
  protected:
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public ISolution {
  public:
    virtual int run() {
      while ( action() );
      return 0;
    }
    
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

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 10 + 11;
  // storages
  int n, x, m;
  int L[SIZE];
  int R[SIZE];
  int S[SIZE];

  int AC;
  int A[SIZE];
  int B[SIZE];
  int max_sum;
  int max_b[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      for ( int i = 0; i < m; ++ i ) {
        L[i] --;
        R[i] --;
      }
      AC = -1;
      max_sum = -1;
      fill(B, B + SIZE, 0);
      search(0, 0);
    }

    bool check() {
      for ( int i = 0; i < m; ++ i ) {
        int len = R[i] - L[i] + 1;
        if ( accumulate(B + L[i], B + L[i] + len, 0) != S[i] )
          return false;
      }
      return true;
    }

    void search( int k, int sum ) {
      if ( k >= n ) {
        if ( sum >= max_sum && check() ) {
          max_sum = sum;
          AC = n;
          for ( int i = 0; i < n; ++ i )
            A[i] = B[i];
        }
        return;
      }

      for ( int i = 0; i <= x; ++ i ) {
        B[k] = i;
        search(k + 1, sum + i);
      }
    }
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      init();
      if ( ! input() )
        return false;
      solver.solve();
      output();
      return true;
    }

    bool input() {
      if ( ! ( cin >> n >> x >> m ) )
        return false;
      for ( int i = 0; i < m; ++ i )
        cin >> L[i] >> R[i] >> S[i];
      return true;
    }

    void output() {
      if ( AC <= 0 ) {
        cout << -1 << endl;
      } else {
        for ( int i = 0; i < AC; ++ i ) {
          cout << A[i];
          if ( i + 1 < AC )
            cout << " ";
        }
        cout << endl;
      }
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

