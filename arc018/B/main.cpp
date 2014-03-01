
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
  const Int MAX_N = 100 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int X[MAX_N];
    Int Y[MAX_N];
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
      if ( ! ( s >> in.N ) ) return false;
      for ( auto i = 0; i < in.N; ++ i )
        if ( ! ( s >> in.X[i] >> in.Y[i] ) ) return false;
      return true;
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
    
    Solution() {}
    
    bool solve() {
      out.res = count();
      return true;
    }

    Int count() {
      Int res = 0;
      for ( auto i = 0; i < in.N; ++ i ) {
        for ( auto j = i + 1; j < in.N; ++ j ) {
          for ( auto k = j + 1; k < in.N; ++ k ) {
            if ( i == j || j == k || k == i ) continue;
            if ( check(i, j, k) ) res ++;
          }
        }
      }
      return res;
    }

    bool check( const Int& a, const Int& b, const Int& c ) {
      Double A = get_len(a, b);
      Double B = get_len(b, c);
      Double C = get_len(c, a);
      Double s = 0.5 * ( A + B + C );
      Double S = sqrt(s * ( s - A ) * ( s - B ) * ( s - C ));
      return is_integer(S) && abs(S) > 1e-9;
    }

    bool is_integer( const Double& x ) {
      return abs(x - floor(x)) < 1e-9 || abs(x - ceil(x)) < 1e-9;
    }

    Double get_len( const Int& a, const Int& b ) {
      Double X = in.X[a] - in.X[b];
      Double Y = in.Y[a] - in.Y[b];
      return sqrt(X * X + Y * Y);
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

