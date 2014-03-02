
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
  const Int MAX_INF = std::numeric_limits<Int>::max() / 3;
  const Int MIN_INF = std::numeric_limits<Int>::min() / 3;
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

    typedef std::queue <Int> Queue;
    
    Int n;
    Int m;
    Int A[MAX_N];
    Int B[MAX_N];
    Int GC[MAX_N];
    Int G[MAX_N][MAX_N];

    Int dist[MAX_N];
    Int min_dist[2][MAX_N];
    Int max_dist[2][MAX_N];
    Int super_dist[2];

    bool solve() {
      for ( auto i = 0; i < 2; ++ i ) {
        fill(GC, GC + MAX_N, 0);
        n = in.N[i];
        m = in.M[i];
        copy(in.A[i], in.A[i] + m, A);
        copy(in.B[i], in.B[i] + m, B);
        generate_graph();
        super_dist[i] = 0;
        for ( auto t = 0; t < n; ++ t ) {
          fill(dist, dist + n, MAX_INF);
          update_dist(t);
          Int maxd = MIN_INF;
          Int mind = MAX_INF;
          for ( auto j = 0; j < n; ++ j ) {
            if ( t != j ) {
              maxd = max(maxd, dist[j]);
              mind = min(mind, dist[j]);
              super_dist[i] = max(super_dist[i], dist[j]);
            }
          }
          max_dist[i][t] = maxd;
          min_dist[i][t] = mind;
        }
      }
      out.max_d = MIN_INF;
      out.min_d = MAX_INF;
      for ( auto i = 0; i < in.N[0]; ++ i ) {
        for ( auto j = 0; j < in.N[1]; ++ j ) {
          if ( max_dist[0][i] == MIN_INF || max_dist[1][j] == MIN_INF ) continue;
          out.max_d = max(out.max_d, max_dist[0][i] + max_dist[1][j] + 1);
          out.min_d = min(out.min_d, max_dist[0][i] + max_dist[1][j] + 1);
        }
      }
      if ( in.M[0] == 0 || in.M[1] == 0 ) {
        if ( in.M[0] == 0 ) {
          out.max_d = in.N[1];
          out.min_d = min(in.N[1], in.N[1] / 2 + 1);
        } else {
          out.max_d = in.N[0];
          out.min_d = min(in.N[0], in.N[0] / 2 + 1);
        }
      } else {
        Int super = max(super_dist[0], super_dist[1]);
        out.max_d = max(out.max_d, super);
        out.min_d = max(out.min_d, super);
      }
      return true;
    }

    void generate_graph() {
      for ( auto i = 0; i < m; ++ i ) {
        const auto& a = A[i];
        const auto& b = B[i];
        G[a][GC[a] ++] = b;
        G[b][GC[b] ++] = a;
      }
    }

    void update_dist( const Int& s ) {
      Queue Q;
      Q.push(s);
      dist[s] = 0;
      while ( ! Q.empty() ) {
        const auto& cur = Q.front(); Q.pop();
        for ( auto i = 0; i < GC[cur]; ++ i ) {
          const auto& to = G[cur][i];
          if ( dist[cur] + 1 >= dist[to] ) continue;
          dist[to] = dist[cur] + 1;
          Q.push(to);
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

