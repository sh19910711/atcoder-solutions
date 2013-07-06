
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
  const int SIZE = 100 + 11;
  const int TASTE_SIZE = 3;
  const int TASTE_A = 0;
  const int TASTE_B = 1;
  const int TASTE_C = 2;
  // storages
  int H, W;
  int A[SIZE][SIZE];
  int result;
  int dp[SIZE][SIZE][TASTE_SIZE][TASTE_SIZE][TASTE_SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      result = calc();
    }

    void init_dp( int r, int c ) {
      for ( int i = 0; i < TASTE_SIZE; ++ i )
        for ( int j = 0; j < TASTE_SIZE; ++ j )
          for ( int k = 0; k < TASTE_SIZE; ++ k )
            dp[r][c][i][j][k] = 0;
    }

    void init_dp() {
      for ( int i = 0; i < SIZE; ++ i )
        for ( int j = 0; j < SIZE; ++ j )
          init_dp(i, j);
    }

    int get_max_from_dp( int r, int c ) {
      int res = 0;
      for ( int i = 0; i < TASTE_SIZE; ++ i )
        for ( int j = 0; j < TASTE_SIZE; ++ j )
          for ( int k = 0; k < TASTE_SIZE; ++ k )
            res = max(res, dp[r][c][i][j][k]);
      return res;
    }

    int get_max_from_dp() {
      int res = 0;
      for ( int i = 0; i <= H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          res = max(res, get_max_from_dp(i, j));
        }
      }
      return res;
    }

    void calc( int r, int c, int aa, int ab, int ac ) {
      int cur = dp[r][c][aa][ab][ac];
      if ( ab == 2 && ( aa == 2 || ac == 2 ) ) {
        int a = A[r][c];
        if ( aa == 2 )
          a ^= 1;
        if ( ab == 2 )
          a ^= 1;
        if ( ac == 2 )
          a ^= 1;
        printf("(%d, %d), [%d, %d, %d], A = %d => %d: max = %d\n", r, c, aa, ab, ac, A[r][c], a, cur);

        for ( int i = 0; i < TASTE_SIZE; ++ i ) {
          for ( int j = 0; j < TASTE_SIZE; ++ j ) {
            int& next_state = dp[r + 1][c][i][2][j];
            next_state = max(next_state, cur + a);
          }
        }
        if ( c + 1 < W ) {
          for ( int i = 0; i < TASTE_SIZE; ++ i ) {
            for ( int j = 0; j < TASTE_SIZE; ++ j ) {
              int& next_state = dp[r][c + 1][2][i][j];
              next_state = max(next_state, cur + a);
            }
          }
        }
        if ( c - 1 >= 0 ) {
          for ( int i = 0; i < TASTE_SIZE; ++ i ) {
            for ( int j = 0; j < TASTE_SIZE; ++ j ) {
              int& next_state = dp[r][c - 1][i][j][2];
              next_state = max(next_state, cur + a);
            }
          }
        }

      }
    }

    void calc( int r, int c ) {
      for ( int i = 0; i < TASTE_SIZE; ++ i ) {
        for ( int j = 0; j < TASTE_SIZE; ++ j ) {
          for ( int k = 0; k < TASTE_SIZE; ++ k ) {
            calc(r, c, i, j, k);
          }
        }
      }
    }

    int calc() {
      init_dp();

      for ( int i = 0; i + 1 <= H; ++ i )
        for ( int j = 0; j < W; ++ j )
          calc(i, j);

      return get_max_from_dp();
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
      if ( ! ( cin >> H >> W ) )
        return false;
      for ( int i = 0; i < H; ++ i )
        for ( int j = 0; j < W; ++ j )
          cin >> A[i][j];
      return true;
    }

    void output() {
      cout << result << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

