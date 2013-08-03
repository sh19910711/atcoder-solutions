
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
  class SolutionInterface {
  public:
    virtual int run() = 0;
    
  protected:
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
    SolutionInterface() {}
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual int run() {
      pre_calc();
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
  const int SIZE = 12 + 1;
  const int P_MAX = SIZE * SIZE / 4 + 11;
  const int NONE = -1;
  // storages
  int h, w;
  string S[SIZE];
  int n;
  int P[P_MAX];

  int result;
  int p;
  int R[P_MAX];
  int C[P_MAX];
  int D[P_MAX];

}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      normalize();
      result = arrange();
    }

    void normalize() {
      for ( int i = 0; i < n; ++ i ) {
        P[i] --;
      }
    }

    int arrange() {
      LL used = 0;
      p = 0;
      for ( int i = 0; i < h / 4; ++ i ) {
        for ( int j = 0; j < w / 4; ++ j ) {
          int sr = i * 4, sc = j * 4;
          if ( ! check_4x4(sr, sc, used) ) {
            return NONE;
          }
        }
      }
      return n;
    }

    bool check_4x4( int sr, int sc, LL& used ) {
      LL backup = used;
      if ( check_4x4_pattern_a(sr, sc, used) )
        return true;
      used = backup;
      if ( check_4x4_pattern_b(sr, sc, used) )
        return true;
      return false;
    }

    bool check_4x4_pattern_a( int sr, int sc, LL& used ) {
      for ( int i = 0; i < 4; ++ i ) {
        if ( ! find_piece_a(i, sr, sc, used) )
          return false;
      }
      return true;
    }

    bool find_piece_a( int k, int sr, int sc, LL& used ) {
      if ( k == 0 ) {
        for ( int i = 0; i < n; ++ i ) {
          LL bi = 1LL << i;
          if ( used & bi )
            continue;
        }
      }
      return false;
    }

    bool check_4x4_pattern_b( int sr, int sc, LL& used ) {
      for ( int i = 0; i < 4; ++ i ) {
        bool ok = false;
        if ( ! ok )
          return false;
      }
      return true;
    }

    bool find_piece_b( int sr, int sc, LL& used ) {
      return false;
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

    void init() {
      result = NONE;
      for ( int i = 0; i < n; ++ i ) {
        R[i] = C[i] = D[i] = NONE;
      }
    }

    bool input() {
      if ( ! ( cin >> h >> w ) )
        return false;
      for ( int i = 0; i < h; ++ i )
        cin >> S[i];
      cin >> n;
      for ( int i = 0; i < n; ++ i ) {
        cin >> P[i];
      }
      return true;
    }

    void output() {
      if ( result == NONE ) {
        cout << -1 << endl;
      } else {
        for ( int i = 0; i < n; ++ i ) {
          cout << C[i] << " " << R[i] << " " << D[i] << endl;
        }
      }
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif

