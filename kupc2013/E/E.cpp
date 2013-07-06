
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
  const int MAX_DICE = 6;
  const int SIZE = 300 + 11;
  const int OPERATIONS = 3000 + 11;
  const int NONE = std::numeric_limits<int>::max();
  // storages
  int M;
  int A[MAX_DICE];
  int s, g;
  int B[SIZE];
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      s --;
      g --;
      calc_path( s, g );
    }

    void calc_path( int s, int g ) {
      typedef pair <int, int> Node;
      typedef priority_queue <Node, vector<Node>, greater<Node> > Queue;

      Queue Q;
      Q.push(Node(0, s));
      int MC[SIZE][2];
      for ( int i = 0; i < SIZE; ++ i )
        MC[i][0] = MC[i][1] = NONE;
      MC[s][0] = 0;
      MC[s][1] = 0;
      int prev[SIZE];
      fill(prev, prev + SIZE, NONE);
      int expect_dice[SIZE];
      int expect_dir[SIZE];

      while ( ! Q.empty() ) {
        Node node = Q.top();
        Q.pop();

        int cost = node.first;
        int pos = node.second;

        if ( cost >= OPERATIONS )
          return;
        
        if ( pos == g ) {
          int len = 0;
          int cur_pos = pos;
          int dice[OPERATIONS];
          int dir[OPERATIONS];
          while ( prev[cur_pos] != NONE ) {
            dice[len] = expect_dice[cur_pos] + 1;
            dir[len] = expect_dir[cur_pos];
            len ++;
            cur_pos = prev[cur_pos];
          }

          for ( int i = 0; i < len; ++ i ) {
            cout << dice[i] << ", " << dir[i] << endl;
          }

          return;

          int cur = 0;
          for ( int i = 0; i < len; ++ i ) {
            int type;
            cin >> type;
            while ( type != dice[i] ) {
              cout << 0 << endl;
              cin >> type;
            }
            cout << ( dir[i] ? 1 : -1 ) << endl;
          }

          return;
        }

        const int dr[2] = {1, -1};
        for ( int i = 0; i < MAX_DICE; ++ i ) {
          for ( int j = 0; j < 2; ++ j ) {
            int ncost = cost + 1;
            int npos = pos + A[i] * dr[j];
            npos += B[npos];
            if ( npos < 0 || npos >= M )
              continue;
            if ( ncost >= MC[npos][j] )
              continue;
            MC[npos][j] = ncost;
            prev[npos] = pos;
            expect_dice[npos] = i;
            expect_dir[npos] = j;
            Q.push(Node(ncost, npos));
          }
        }
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
      if ( ! ( cin >> M ) )
        return false;
      for ( int i = 0; i < MAX_DICE; ++ i )
        cin >> A[i];
      cin >> s >> g;
      for ( int i = 0; i < M; ++ i )
        cin >> B[i];
      return true;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
int main() {
  return solution::Solution().run();
}

