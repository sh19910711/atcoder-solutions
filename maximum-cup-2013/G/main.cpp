
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

// @snippet<sh19910711/contest:solution/define_classes.cpp>
namespace solution {
  class Solution;
  class Solver;
  struct InputStorage;
  struct OutputStorage;
  struct DataStorage;
  class Storages;
}

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    
  protected:
    SolutionInterface() {}
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input( InputStorage& s ) { return false; };
    virtual void output( const OutputStorage& s ) const {};
    virtual void before_action( const int& test_no ) const {}
    virtual void after_action( const int& test_no ) const {}
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {}
    virtual int run() {
      this->pre_calc();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      return 0;
    }
  protected:
    SolutionBase() {}
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 10 + 1;
  const int NO_COST = -1;
  const int NO_MONSTER = -1;
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  struct Cell {
    int pass_cost;
    int level; // has monster if level > 0
    bool has_ring;
    bool has_up;
    bool has_down;

    Cell() {
      pass_cost = NO_COST;
      level     = NO_MONSTER;
      has_ring  = false;
      has_up    = false;
      has_down  = false;
    }
  };

  struct Map {
    Cell grid[SIZE][SIZE];
  };

}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    int T;
    int W;
    int H;
    int L;
    string M[SIZE][SIZE];
  };
  
  struct OutputStorage {
    int result;
  };
  
  struct DataStorage {
    Map map[SIZE];
  };
  
  struct Storages {
    InputStorage  in;
    OutputStorage out;
    DataStorage   data;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    const OutputStorage& solve( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      cout << "test" << endl;
      for ( int i = 0; i < in.T; ++ i )
        data.map[i] = normalize_map(in.M[i], in.W, in.H);
      return out;
    }
    
  protected:
    static Map normalize_map( const string M[SIZE], const int& W, const int& H ) {
      Map res;
      cout << "no" << endl;
      for ( int i = 0; i < H; ++ i ) {
        for ( int j = 0; j < W; ++ j ) {
          string cell_text = M[i].substr(j * 2, 2);
          Cell cell = get_cell(cell_text);
          res.grid[i][j] = cell;
        }
      }
      return res;
    }

    static Cell get_cell( const string& s ) {
      Cell cell;
      if ( s == "==" || s == "@@" || s == "KR" ) {
        cell.pass_cost = 1;
      } else if ( s == "  " || s == "##" ) {
        cell.pass_cost = NO_COST;
      } else if ( is_monster(s) ) {
        int level = get_monster_level(s);
        cell.pass_cost = level;
        cell.level = level;
      } else if ( s == "_-" ) {
        cell.pass_cost = 1;
        cell.has_up = true;
      } else if ( s == "-_" ) {
        cell.pass_cost = 1;
        cell.has_down = true;
      }
      return cell;
    }

    static int get_monster_level( const string& s ) {
      if ( s == "HC" )
        return 100;
      ISS iss(s);
      int level;
      iss >> level;
      return level;
    }

    static bool is_monster( const string& s ) {
      if ( s == "HC" )
        return true;
      return std::isdigit(s[0]) && std::isdigit(s[1]);
    }
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {}
    Solution(Storages* p): storages(p) {}
    
  protected:
    virtual bool action() {
      this->init();
      if ( ! this->input(this->storages->in) )
        return false;
      this->output(solver.solve(this->storages->in, this->storages->out, this->storages->data));
      return true;
    }

    bool input( InputStorage& in ) {
      if ( ! ( input_first_line(in) ) )
        return false;
      for ( int i = 0; i < in.T; ++ i )
        input_map(in, i);
      return true;
    }

    bool input_first_line( InputStorage& in ) {
      string line;
      if ( ! getline(std::cin, line) )
        return false;
      ISS iss(line);
      return iss >> in.T >> in.W >> in.H >> in.L;
    }

    bool input_map( InputStorage& in, const int& k ) {
      for ( int i = 0; i < in.H; ++ i ) {
        getline(std::cin, in.M[k][i]);
      }
      return true;
    }

    void output( const OutputStorage& out ) {
      std::cout << out.result << endl;
    }
    
  private:
    Solver solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  return solution::Solution(&solution::global_storages).run();
}
#endif

