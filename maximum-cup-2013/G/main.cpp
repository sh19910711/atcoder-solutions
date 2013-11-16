
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

// @snippet<sh19910711/contest:search/search_interface.cpp>
namespace search {
  template <class Node> class SearchInterface {
  public:
    virtual Node search() = 0;
  };
}

// @snippet<sh19910711/contest:search/breadth_first_search_interface.cpp>
namespace search {
  template <class Node> class BreadthFirstSearchInterface: public SearchInterface<Node> {
  public:
    virtual Node search()                            = 0;
  protected:
    virtual void init()                              = 0;
    virtual bool has_next_node()                     = 0;
    virtual void visit_next_node( const Node& node ) = 0;
    virtual void push_next_node( const Node& node )  = 0;
    virtual Node get_next_node()                     = 0;
    virtual Node get_none_node()                     = 0;
    virtual bool is_visited_node( const Node& node ) = 0;
    virtual void set_visited( const Node& node )     = 0;
    virtual bool is_goal_node( const Node& node )    = 0;
  };
}

// @snippet<sh19910711/contest:search/breadth_first_search_base.cpp>
namespace search {
  template <class Node> class BreadthFirstSearchBase: public BreadthFirstSearchInterface<Node> {
  public:
    Node search() {
      Node res = this->get_none_node();
      this->init();
      while ( this->has_next_node() ) {
        Node node = this->get_next_node();
        if ( this->is_goal_node(node) ) {
          res = std::min(res, node);
        }
        this->visit_next_node(node);
      }
      return res;
    }
  };
}

// @snippet<sh19910711/contest:search/breadth_first_search.cpp>
namespace search {
  template <class Node> class BreadthFirstSearch: public BreadthFirstSearchBase<Node> {
  protected:
    virtual void init() {}
    
    bool has_next_node() {
      return ! Q.empty();
    }
    
    Node get_next_node() {
      Node res = Q.front();
      Q.pop();
      return res;
    }
    
    void push_next_node( const Node& node ) {
      if ( this->is_visited_node(node) )
        return;
      Q.push(node);
      this->set_visited(node);
    }
    
  protected:
    std::queue <Node> Q;
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
  const int SIZE          = 10 + 1;
  const int NONE          = -1;
  const int NO_COST       = std::numeric_limits<int>::max();
  const int NO_MONSTER    = NONE;
  const int MAX_LEVEL     = 101 + 11;
  const string IMPOSSIBLE = "Impossible";
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  struct Cell {
    int pass_cost;
    int level; // has monster if level > 0
    bool has_up;
    bool has_down;
    
    Cell() {
      pass_cost = NO_COST;
      level     = NO_MONSTER;
      has_up    = false;
      has_down  = false;
    }

    friend ostream& operator <<( ostream& os, const Cell& cell ) {
      return os << "{" << cell.pass_cost << ", " << cell.level << ", " << cell.has_up << ", " << cell.has_down << "}";
    }
  };
  
  struct Map {
    Cell grid[SIZE][SIZE];
  };
  
  struct Position {
    int r;
    int c;
    int k; // floor id
    
    friend ostream& operator <<( ostream& os, const Position& pos ) {
      return os << "(" << pos.r << ", " << pos.c << ", " << pos.k << ")";
    }

    friend bool operator ==( const Position& a, const Position& b ) {
      return a.r == b.r && a.c == b.c && a.k == b.k;
    }
  };
  const Position POSITION_NONE = {NONE, NONE, NONE};
}

namespace solution {
  struct Node {
    int steps;
    Position pos;
    int level;

    friend ostream& operator <<( ostream& os, const Node& node ) {
      return os << "{" << node.steps << ", " << node.pos << ", " << node.level << "}";
    }

    friend bool operator <( const Node& a, const Node& b ) {
      return a.steps < b.steps;
    }
  };

  const int dr[4] = {0, 0, 1, -1};
  const int dc[4] = {1, -1, 0, 0};
  class BFS: public search::BreadthFirstSearch<Node> {
  public:
    void visit_next_node( const Node& node ) {
      // move
      for ( int k = 0; k < 4; ++ k ) {
        Node next_node = node;
        next_node.pos.r += dr[k];
        next_node.pos.c += dc[k];

        // check pos
        if ( this->is_invalid_pos(next_node.pos) )
          continue;

        // check cell
        Cell next_cell = M[next_node.pos.k].grid[next_node.pos.r][next_node.pos.c];
        int cost = next_cell.pass_cost;
        if ( cost == NO_COST )
          continue;
        int level = next_cell.level;
        if ( node.level < level )
          continue;
        if ( node.level == level )
          next_node.level += 1;

        next_node.steps += cost;

        this->push_next_node(next_node);
      }

      // stair
      Cell cur_cell = M[node.pos.k].grid[node.pos.r][node.pos.c];
      if ( node.pos.k < T && cur_cell.has_up ) {
        Node next_node = node;
        next_node.pos.k += 1;
        next_node.steps += 1;
        push_next_node(next_node);
      }
      if ( node.pos.k > 0 && cur_cell.has_down ) {
        Node next_node = node;
        next_node.pos.k -= 1;
        next_node.steps += 1;
        push_next_node(next_node);
      }
    }

    Node get_none_node() {
      Node none = {NO_COST, POSITION_NONE, NONE};
      return none;
    }

    bool is_visited_node( const Node& node ) {
      return visited[node.pos.r][node.pos.c][node.pos.k][node.level];
    }

    void set_visited( const Node& node ) {
      visited[node.pos.r][node.pos.c][node.pos.k][node.level] = true;
    }

    bool is_goal_node( const Node& node ) {
      return node.pos == goal_pos;
    }

    void init_problem( const int& in_l, const int& in_t, const int& in_w, const int& in_h, const Map in_m[SIZE], const Position& in_start_pos, const Position& in_goal_pos ) {
      for ( int i = 0; i < SIZE; ++ i )
        for ( int j = 0; j < SIZE; ++ j )
          for ( int k = 0; k < SIZE; ++ k )
            for ( int l = 0; l < MAX_LEVEL; ++ l )
              visited[i][j][k][l] = false;
      L         = in_l;
      T         = in_t;
      W         = in_w;
      H         = in_h;
      start_pos = in_start_pos;
      goal_pos  = in_goal_pos;
      std::copy(in_m, in_m + SIZE, M);

      Node start_node;
      start_node.steps = 0;
      start_node.pos = start_pos;
      start_node.level = std::min(101, L);
      push_next_node(start_node);
    }

  private:
    int        T;
    int        W;
    int        H;
    int        L;
    Map        M[SIZE];
    bool       visited[SIZE][SIZE][SIZE][MAX_LEVEL];
    Position   start_pos;
    Position   goal_pos;

    bool is_invalid_pos( const Position& pos ) {
      return pos.r < 0 || pos.r >= H || pos.c < 0 || pos.c >= W;
    }
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
      Position start_pos = find_start_position(in.M, in.T, in.W, in.H);
      Position goal_pos = find_goal_position(in.M, in.T, in.W, in.H);
      for ( int i = 0; i < in.T; ++ i )
        data.map[i] = normalize_map(in.M[i], in.W, in.H);
      out.result = find_minimum_steps(in.L, in.T, in.W, in.H, data.map, start_pos, goal_pos);
      return out;
    }
    
  protected:
    static int find_minimum_steps( const int& L, const int& T, const int& W, const int& H, const Map M[SIZE], const Position& start_pos, const Position& goal_pos ) {
      BFS bfs;
      bfs.init_problem(L, T, W, H, M, start_pos, goal_pos);
      Node ret = bfs.search();
      return ret.steps;
    }
    
    static Position find_goal_position( const string M[SIZE][SIZE], const int& T, const int& W, const int& H ) {
      for ( int k = 0; k < T; ++ k ) {
        for ( int i = 0; i < H; ++ i ) {
          for ( int j = 0; j < W; ++ j ) {
            string cell_text = M[k][i].substr(j * 2, 2);
            if ( cell_text == "$$" ) {
              Position pos = {i, j, k};
              return pos;
            }
          }
        }
      }
      return POSITION_NONE;
    }
    
    static Position find_start_position( const string M[SIZE][SIZE], const int& T, const int& W, const int& H ) {
      for ( int k = 0; k < T; ++ k ) {
        for ( int i = 0; i < H; ++ i ) {
          for ( int j = 0; j < W; ++ j ) {
            string cell_text = M[k][i].substr(j * 2, 2);
            if ( cell_text == "KR" ) {
              Position pos = {i, j, k};
              return pos;
            }
          }
        }
      }
      return POSITION_NONE;
    }
    
    static Map normalize_map( const string M[SIZE], const int& W, const int& H ) {
      Map res;
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
      if ( s == "==" || s == "@@" || s == "KR" || s == "$$" ) {
        cell.pass_cost = 1;
      } else if ( s == "  " || s == "##" ) {
        cell.pass_cost = NO_COST;
      } else if ( is_monster(s) ) {
        int level = get_monster_level(s);
        cell.pass_cost = level + 1;
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
      if ( out.result == NONE ) {
        std::cout << IMPOSSIBLE << endl;
      } else {
        std::cout << out.result << endl;
      }
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


