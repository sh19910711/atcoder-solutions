
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

// @snippet<sh19910711/contest:setlib/disjoints_set.cpp>
namespace setlib {
  // @desc 素集合データ構造
  class DisjointSets {
  public:
    std::vector<int> data;
    DisjointSets( int size ): data(size, -1) {};
    void init( int size ) { data.resize(size); std::fill( data.begin(), data.end(), -1 ); }
    bool merge( int x, int y ) {
      x = root(x), y = root(y);
      if ( x != y ) {
        if ( data[y] < data[x] ) std::swap( x, y );
        data[x] += data[y], data[y] = x;
      }
      return x != y;
    }
    bool same( int x, int y ) { return root(x) == root(y); }
    int root( int x ) { return data[x] < 0 ? x : data[x] = root(data[x]); }
  };
}

// @snippet<sh19910711/contest:graph/get_minimum_spanning_forest.cpp>
namespace graph {
  template <typename GraphType> const typename std::vector<typename GraphType::Edge> get_minimum_spanning_forest( const GraphType& G ) {
    typedef typename std::vector<typename GraphType::Edge> Edges;
    typedef typename GraphType::Edge GraphEdge;
    typedef typename GraphType::Edges GraphEdges;
    typedef std::priority_queue<GraphEdge, Edges, std::greater<GraphEdge> > PriorityQueue;
    typedef setlib::DisjointSets UnionFind;
    
    Edges res;
    PriorityQueue E;
    UnionFind uf(G.num_vertices);
    
    for ( int i = 0; i < G.num_vertices; ++ i ) {
      for ( typename GraphEdges::const_iterator it_i = G.vertex_edges[i].begin(); it_i != G.vertex_edges[i].end(); ++ it_i ) {
        const GraphEdge& e = **it_i;
        E.push(GraphEdge(e.from, e.to, e.weight));
      }
    }
    
    while ( ! E.empty() ) {
      GraphEdge e = E.top();
      E.pop();
      if ( ! uf.same(e.from, e.to) ) {
        res.push_back(e);
        uf.merge(e.from, e.to);
      }
    }
    
    return res;
  }
}

// @snippet<sh19910711/contest:misc/smart_pointer_reference_count.cpp>
namespace misc {
  class SmartPointerReferenceCount {
  public:
    void add() { count ++; }
    int release() { return -- count; }
  private:
    int count;
  };
}

// @snippet<sh19910711/contest:misc/smart_pointer.cpp>
namespace misc {
  template <typename Type> class SmartPointer {
  public:
    SmartPointer(): pointer(0), reference(0) {
      reference = new misc::SmartPointerReferenceCount();
      reference->add();
    }
    SmartPointer(Type* value): pointer(value) {
      reference = new misc::SmartPointerReferenceCount();
      reference->add();
    }
    SmartPointer(const SmartPointer<Type>& sp): pointer(sp.pointer), reference(sp.reference) {
      reference->add();
    }
    ~SmartPointer() {
      if ( reference->release() == 0 ) {
        delete[] pointer;
        delete[] reference;
      }
    }
    Type& operator *() { return *pointer; }
    const Type& operator *() const { return *pointer; }
    Type* operator +( const int& x ) { return pointer + x; }
    const Type* operator +( const int& x ) const { return pointer + x; }
    Type* operator ->() { return pointer; }
    SmartPointer<Type>& operator = ( const SmartPointer<Type>& sp ) {
      if ( this != &sp ) {
        if ( reference->release() == 0 ) {
          delete[] pointer;
          delete[] reference;
        }
        pointer = sp.pointer;
        reference = sp.reference;
        reference->add();
      }
      return *this;
    }
  private:
    Type* pointer;
    misc::SmartPointerReferenceCount* reference;
  };
}

// @snippet<sh19910711/contest:graph/interface.cpp>
namespace graph {
  template <typename WeightType, typename EdgeType> class GraphInterface {
  public:
    typedef WeightType Weight;
    typedef EdgeType Edge;
    typedef typename misc::SmartPointer<EdgeType> EdgePointer;
    virtual void init( const int& num_vertices ) = 0;
    virtual void add_edge( EdgePointer edge )    = 0;
    virtual ~GraphInterface() {}
  };
}

// @snippet<sh19910711/contest:graph/adjacent_list.cpp>
namespace graph {
  template <typename WeightType, typename EdgeType> class AdjacentList: public GraphInterface<WeightType, EdgeType> {
  public:
    typedef misc::SmartPointer<EdgeType> EdgePointer;
    typedef std::vector<EdgePointer> Edges;
    typedef std::vector<Edges> VertexEdges;
    
    void init( const int& num_vertices ) {
      this->num_vertices = num_vertices;
      this->vertex_edges = VertexEdges(this->num_vertices);
    }
    
    void add_edge( EdgePointer edge ) {
      this->vertex_edges[edge->from].push_back(edge);
    }
    
    int num_vertices;
    VertexEdges vertex_edges;
    
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
  const int SIZE = 16;
  const int COST_NONE = -1;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
  struct Edge {
    int from;
    int to;
    int cost;
    int weight;

    Edge( int from, int to, int cost ): from(from), to(to), cost(cost), weight(cost) {}

    friend ostream& operator << ( ostream& os, const Edge& e ) {
      os << e.from << " <-> " << e.to << " (" << e.cost << ")";
      return os;
    }

    friend bool operator < ( const Edge& a, const Edge& b ) {
      return a.cost < b.cost;
    }

    friend bool operator > ( const Edge& a, const Edge& b ) {
      return a.cost > b.cost;
    }

    friend bool operator == ( const Edge& a, const Edge& b ) {
      return std::min(a.from, a.to) == std::min(b.from, b.to) &&
        std::max(a.from, a.to) == std::max(b.from, b.to);
    }
  };
  typedef std::vector<Edge> Edges;

  typedef graph::AdjacentList<int, Edge> Graph;

  ostream& operator << ( ostream& os, const Graph& G ) {
    for ( int i = 0; i < G.num_vertices; ++ i ) {
      os << "from: " << i << endl;
      for ( Graph::Edges::const_iterator it_i = G.vertex_edges[i].begin(); it_i != G.vertex_edges[i].end(); ++ it_i ) {
        os << **it_i << endl;
      }
    }
    return os;
  }
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    int N;
    int T[SIZE][SIZE];
  };
  
  struct OutputStorage {
    int roads;
    int minimum_cost;
  };
  
  struct DataStorage {
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
      Edges e;
      for ( int i = 0; i < in.N; ++ i ) {
        Graph g = generate_graph(in.N, in.T, i);
        Edges ret = graph::get_minimum_spanning_forest(g);
        for ( Edges::iterator it_i = ret.begin(); it_i != ret.end(); ++ it_i ) {
          e.push_back(*it_i);
        }
      }

      typedef std::pair<int, int> P;
      typedef std::set<P> Set;

      Set s;
      for ( Edges::iterator it_i = e.begin(); it_i != e.end(); ++ it_i ) {
        Edge& edge = *it_i;
        s.insert(P(std::min(edge.from, edge.to), std::max(edge.from, edge.to)));
      }

      out.roads = s.size();
      out.minimum_cost = 0;
      for ( Set::iterator it_i = s.begin(); it_i != s.end(); ++ it_i ) {
        const P& p = *it_i;
        out.minimum_cost += in.T[p.first][p.second];
      }

      return out;
    }
    
  protected:
    static Graph generate_graph( const int& n, const int t[SIZE][SIZE], const int ignore ) {
      Graph g;
      g.init(n);
      for ( int i = 0; i < n; ++ i ) {
        for ( int j = 0; j < n; ++ j ) {
          if ( t[i][j] == COST_NONE )
            continue;
          if ( i == ignore || j == ignore )
            continue;
          g.add_edge(new Edge(i, j, t[i][j]));
        }
      }
      return g;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {}
    Solution(Storages* p): storages(p) {
      for ( int i = 0; i < SIZE; ++ i )
        for ( int j = 0; j < SIZE; ++ j )
          p->in.T[i][j] = COST_NONE;
    }
    
  protected:
    virtual bool action() {
      this->init();
      if ( ! this->input(this->storages->in) )
        return false;
      this->output(solver.solve(this->storages->in, this->storages->out, this->storages->data));
      return true;
    }

    bool input( InputStorage& in ) {
      if ( ! ( std::cin >> in.N ) )
        return false;
      for ( int i = 0; i < in.N; ++ i ) {
        for ( int j = i + 1; j < in.N; ++ j ) {
          std::cin >> in.T[i][j];
          in.T[j][i] = in.T[i][j];
        }
      }
      return true;
    }

    void output( const OutputStorage& out ) {
      std::cout << out.roads << " " << out.minimum_cost << endl;
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



