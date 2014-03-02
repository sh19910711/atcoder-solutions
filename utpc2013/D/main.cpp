
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
  const Int SIZE = 10000;
  const Int NONE = -1;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int A[MAX_N];
  };
  
  struct Output {
    Int result;
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
        if ( ! ( s >> in.A[i] ) ) return false;
      return true;
    }
    
    template <class Stream> bool output( Stream& s ) {
      return s << out.result << endl;
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

    Int A[SIZE];
    
    bool solve() {
      out.result = find();
      return true;
    }

    Int find() {
      for ( auto i = 0; i < SIZE - 100; ++ i ) {
        if ( check(i) ) return i + in.N;
      }
      return -1;
    }

    bool check( const Int& offset ) {
      Int len = offset + in.N;
      fill(A, A + SIZE, NONE);
      copy(in.A, in.A + in.N, A + offset);
      for ( auto i = len - in.N - 1; i >= 0; -- i ) {
        if ( i * 2 > len ) return false;
        if ( A[i * 2 + 1] >= A[i * 2 + 2] ) return false;
        A[i] = min(A[i * 2 + 1], A[i * 2 + 2]) - 1;
        if ( A[i] < 0 ) return false;
      }
      cout << "@check: offset = " << offset << " / ";
      for ( auto i = 0; i < len; ++ i ) {
        cout << A[i] << ", ";
        if ( ( i * 2 + 1 < len && A[i] >= A[i * 2 + 1] ) || ( i * 2 + 2 < len && A[i] >= A[i * 2 + 2] ) ) {
          cout << endl;
          return false;
        }
      }
      cout << endl;
      return true;
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

