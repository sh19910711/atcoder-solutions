
// @snippet<sh19910711/contest-base-simple:header.cpp>
#define __THIS_IS_CPP11__
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

// @snippet<sh19910711/contest-base-simple:solution/template-typedef.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int R;
    Int G;
    Int B;
  };
  struct Output {
    Int result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution {
    //
    // Implement here
    //
    
    Int get_ways( Int len ) {
      return len * ( len + 1 ) / 2;
    }

    Int get_rb_ways( const Int& rem, const Int& g ) {
      Int l = 0;
      Int r = 0;
      while ( l + r + 1 != rem ) {
        if ( l > r && r < g ) {
          r ++;
        } else {
          l ++;
        }
      }
      Int res = get_ways(l) + get_ways(r);
      return res;
    }

    Int count_ways( const Int& R, const Int& G, const Int& B ) {
      Int best = std::numeric_limits<Int>::max();
      for ( Int gl = 0; gl <= G; ++ gl ) {
        Int ways = 0;
        Int gr = G - gl - 1;
        if ( gl < 0 || gr < 0 )
          continue;
        ways += get_ways(gl) + get_ways(gr);

        // r
        if ( gl >= 100 ) {
          Int diff = gl - 100;
          Int r_ways = diff * R + get_ways(R);
          ways += r_ways;
        } else {
          ways += get_rb_ways(R, 100 - gl);
        }

        // b
        if ( gr >= 100 ) {
          Int diff = gr - 100;
          Int b_ways = diff * B + get_ways(B);
          ways += b_ways;
        } else {
          ways += get_rb_ways(B, 100 - gr);
        }

        best = std::min(best, ways);
      }
      return best;
    }

    Int count_ways_r( const Int& R, const Int& G, const Int& B ) {
      Int ways = 0;
      for ( Int l = 0; l < 160; ++ l ) {
        Int r = R - l - 1;
        if ( l < 0 || r < 0 )
          continue;
        ways += get_ways(l) + get_ways(r);
        if ( l >= 100 ) {
          Int diff = l - 100;
          Int g_ways = diff * G + get_ways(G);
          ways += g_ways;
        }
      }
      return ways;
    }

    Int count_ways_b( const Int& R, const Int& G, const Int& B ) {
      Int ways = 0;
      for ( Int l = 0; l < 160; ++ l ) {
        Int r = B - l - 1;
        if ( l < 0 || r < 0 )
          continue;
        ways += get_ways(l) + get_ways(r);
        if ( l >= 100 ) {
          Int diff = l - 100;
          Int g_ways = diff * G + get_ways(G);
          ways += g_ways;
        }
      }
      return ways;
    }

    void solve() {
      out->result = std::min(
        std::min(count_ways_r(in->R, in->G, in->B), count_ways_b(in->R, in->G, in->B)),
        count_ways(in->R, in->G, in->B)
      );
    }
    
    bool input() {
      return std::cin >> in->R >> in->G >> in->B;
    }
    
    void output() {
      std::cout << out->result << std::endl;
    }
    
    //
    //
    //
    Solution( Input* in, Output* out ): in(in), out(out) {
      // pre calc
    }
    
    int run() {
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      return 0;
    }
    
    bool action() {
      if ( ! this->input() ) return false;
      this->solve();
      this->output();
      return true;
    }
    
    void before_action( const int& t_id ) {}
    
    void after_action( const int& t_id ) {}
    
    Input* in;
    Output* out;
  };
}

// @snippet<sh19910711/contest-base-simple:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using namespace solution;
  static Input in;
  static Output out;
  static Solution sol(&in, &out);
  return sol.run();
}

// @snippet<sh19910711/contest-base-simple:main.cpp>

