
// @snippet<sh19910711/contest-base-simple:header.cpp>
#define __THIS_IS_CPP11__
/* default headers {{{ */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cstdio>
#include <cmath>

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif
/* }}} */


// @snippet<sh19910711/contest-base-simple:solution/template-typedef.cpp>
namespace solution {
  using namespace std;
  /* primitives {{{ */
  typedef long long Int;
  typedef long double Double;
  /* }}} */
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const Int MAX_N = 1000 + 11;
  const Int INF = std::numeric_limits<Int>::max() / 3;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N[2];
    Int M[2];
    Int A[2][MAX_N];
    Int B[2][MAX_N];
  };
  
  struct Output {
    Int min_d;
    Int max_d;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution-io.cpp>
namespace solution {
  struct SolutionIO {
    Input in;
    Output out;
    
    template <class Stream> bool input( Stream& s ) {
      for ( auto i = 0; i < 2; ++ i ) {
        if ( ! ( s >> in.N[i] >> in.M[i] ) ) return false;
        for ( auto j = 0; j < in.M[i]; ++ j ) {
          if ( ! ( s >> in.A[i][j] >> in.B[i][j] ) ) return false;
        }
      }
      return true;
    }
    
    template <class Stream> bool output( Stream& s ) {
      return s << out.min_d << " " << out.max_d << endl;
    }
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionIO {
    //
    // Implement here
    //
    
    Solution() {}
    
    Int dist[MAX_N][MAX_N];

    bool solve() {
      for ( auto i = 0; i < MAX_N; ++ i ) {
        for ( auto j = 0; j < MAX_N; ++ j ) {
          dist[i][j] = INF;
        }
      }
      for ( auto i = 0; i < 2; ++ i ) {
        for ( auto j = 0; j < in.M[i]; ++ j ) {
          int a = in.A[i][j];
          int b = in.B[i][j];
          dist[a][b] = dist[b][a] = 1;
        }
        update_dist();
      }
      return true;
    }

    void update_dist() {
      for ( auto k = 0; k < MAX_N; ++ k ) {
        for ( auto i = 0; i < MAX_N; ++ i ) {
          for ( auto j = 0; j < MAX_N; ++ j ) {
            dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
          }
        }
      }
    }
    
    /* action methods {{{ */
    void before_action( const int& t_id ) {}
    
    void after_action( const int& t_id ) {}
    
    bool action( const int& t_id = -1 ) {
      before_action(t_id);
      bool res = input(std::cin) && solve() && output(std::cout);
      after_action(t_id);
      return res;
    }
    /* }}} */
  };
}

// @snippet<sh19910711/contest-base-simple:solution/runner-normal.cpp>
namespace solution {
  /* Runner Class {{{ */
  struct Runner {
    static int run() {
      bool f = false;
      while ( ! f ) {
        Solution* sol = new Solution;
        f = ! sol->action();
        delete sol;
      };
      return 0;
    }
  };
  /* }}} */
}

// @snippet<sh19910711/contest-base-simple:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  return solution::Runner::run();
}

// @snippet<sh19910711/contest-base-simple:main.cpp>

