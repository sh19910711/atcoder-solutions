
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
  class SolutionInterface {
  public:
    virtual int run() = 0;
    
  protected:
    SolutionInterface() {}
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() const {};
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual int run() {
      this->pre_calc();
      while ( this->action() );
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class VectorClass {
  public:
    typedef ValueType Type;
    VectorClass() { data.resize(SIZE); }
    Type& operator [] ( const int& index ) { return data[index]; }
    const Type& operator [] ( const int& index ) const { return data[index]; }
  private:
    std::vector<Type> data;
  };
}

// @snippet<sh19910711/contest:storage/vector_types.cpp>
namespace storage {
  const int VECTOR_NONE = -1;
  template <typename ValueType, int SIZE_X = VECTOR_NONE, int SIZE_Y = VECTOR_NONE, int SIZE_Z = VECTOR_NONE> struct Vector {
    typedef storage::VectorClass<ValueType, SIZE_X> Type__;
    typedef storage::VectorClass<Type__, SIZE_Y> Type_;
    typedef storage::VectorClass<Type_, SIZE_Z> Type;
  };
  template <typename ValueType, int SIZE_X, int SIZE_Y> struct Vector<ValueType, SIZE_X, SIZE_Y, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type_;
    typedef storage::VectorClass<Type_, SIZE_X> Type;
  };
  template <typename ValueType, int SIZE_X> struct Vector<ValueType, SIZE_X, VECTOR_NONE, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type;
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  typedef std::pair <Int, Int> Element;
  typedef std::stack <Element> Stack;

  enum ErrorType {
    OK, FULL, EMPTY
  };
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const Int SIZE          = 100000 + 11;
  const String TEXT_PUSH  = "Push";
  const String TEXT_POP   = "Pop";
  const String TEXT_TOP   = "Top";
  const String TEXT_SIZE  = "Size";
  const String TEXT_FULL  = "FULL";
  const String TEXT_EMPTY = "EMPTY";
  const String TEXT_SAFE  = "SAFE";
}

namespace solution {
  struct QueryInfo {
    String type;
    Int x;
    Int y;
  };

  std::istream& operator >> ( std::istream& is, QueryInfo& q ) {
    is >> q.type;
    if ( q.type == TEXT_PUSH ) {
      is >> q.x >> q.y;
    } else if ( q.type == TEXT_POP ) {
      is >> q.x;
    }
    return is;
  }

  std::ostream& operator << ( std::ostream& os, const QueryInfo& q ) {
    return os << q.type << ", " << q.x << ", " << q.y;
  }
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  typedef storage::Vector<QueryInfo, SIZE>::Type Queries;
  typedef storage::Vector<String, SIZE>::Type Results;

  Int queries;
  Int stack_size;
  Queries Q;

  Stack S;
  Int S_sum;

  Results results;
  Int results_num;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      proc_queries(S, S_sum, queries, stack_size, Q);
    }

    static const void add_result( String s ) {
      results[results_num ++] = s;
    }

    static const void proc_queries( Stack& S, Int& S_sum, const Int& queries, const Int& stack_size, const Queries& Q ) {
      S = Stack();
      S_sum = 0;
      results_num = 0;
      for ( int i = 0; i < queries; ++ i ) {
        ErrorType ret = proc_query(S, S_sum, stack_size, Q[i]);
        if ( ret == FULL ) {
          add_result(TEXT_FULL);
          return;
        } else if ( ret == EMPTY ) {
          add_result(TEXT_EMPTY);
          return;
        }
      }
      add_result(TEXT_SAFE);
    }

    static const String to_string( const Int& x ) {
      OSS oss;
      oss << x;
      return oss.str();
    }

    static const ErrorType proc_query( Stack& S, Int& S_sum, const Int& stack_size, const QueryInfo& query ) {
      // cout << query << endl;
      // Element(種類, 個数)
      if ( query.type == TEXT_PUSH ) {
        const Int& n = query.x;
        const Int& m = query.y;
        S_sum += n;
        if ( S_sum > stack_size )
          return FULL;
        S.push(Element(m, n));
      } else if ( query.type == TEXT_POP ) {
        Int remains = query.x;
        while ( remains > 0 ) {
          if ( S.empty() )
            return EMPTY;
          Element e  = S.top();
          Int& value = e.first;
          Int& num   = e.second;
          Int diff   = std::min(remains, num);
          remains   -= diff;
          num       -= diff;
          S_sum     -= diff;
          S.pop();
          if ( e.second > 0 ) {
            S.push(Element(value, num));
          }
        }
      } else if ( query.type == TEXT_TOP ) {
        if ( S.empty() )
          return EMPTY;
        add_result(to_string(S.top().first));
      } else if ( query.type == TEXT_SIZE ) {
        add_result(to_string(S_sum));
      }
      return OK;
    }

  protected:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      this->init();
      if ( ! this->input() )
        return false;
      solver.solve();
      this->output();
      return true;
    }

    bool input() {
      if ( ! ( std::cin >> queries >> stack_size ) )
        return false;
      for ( int i = 0; i < queries; ++ i )
        std::cin >> Q[i];
      return true;
    }

    void output() {
      for ( int i = 0; i < results_num; ++ i ) {
        std::cout << results[i] << std::endl;
      }
    }
    
    Solver solver;
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  return solution::Solution().run();
}
#endif


