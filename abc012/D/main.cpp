
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
  const Int N_MAX = 300 + 11;
  const Int M_MAX = 50000 + 11;
  const Int INF = std::numeric_limits<Int>::max();
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    Int A[M_MAX];
    Int B[M_MAX];
    Int T[M_MAX];
  };
  
  struct Output {
    Int res;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution-io.cpp>
namespace solution {
  struct SolutionIO {
    Input in;
    Output out;
    
    template <class Stream> bool input( Stream& s ) {
      if ( s >> in.N >> in.M ) {
        for ( int i = 0; i < in.M; ++ i ) {
          s >> in.A[i] >> in.B[i] >> in.T[i];
        }
        return true;
      }
      return false;
    }
    
    template <class Stream> bool output( Stream& s ) {
      return s << out.res << endl;
    }
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionIO {
    //
    // Implement here
    //
    
    Int G[N_MAX][N_MAX];
    
    Solution() {}
    
    bool solve() {
      out.res = find_max();
      return true;
    }
    
    Int find_max() {
      for ( int i = 0; i < in.N; ++ i ) {
        for ( int j = 0; j < in.N; ++ j ) {
          G[i][j] = INF;
        }
      }
      for ( int i = 0; i < in.M; ++ i ) {
        G[in.A[i] - 1][in.B[i] - 1] = in.T[i];
        G[in.B[i] - 1][in.A[i] - 1] = in.T[i];
      }
      for ( int k = 0; k < in.N; ++ k ) {
        for ( int i = 0; i < in.N; ++ i ) {
          for ( int j = 0; j < in.N; ++ j ) {
            if ( i != j && G[i][k] != INF && G[k][j] != INF ) {
              G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
            }
          }
        }
      }
      
      Int res = INF;
      for ( int i = 0; i < in.N; ++ i ) {
        Int tmp = 0;
        for ( int j = 0; j < in.N; ++ j ) {
          if ( i == j ) continue;
          tmp = max(tmp, G[i][j]);
        }
        res = min(res, tmp);
      }
      return res;
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

