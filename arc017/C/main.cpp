
// @snippet<sh19910711/contest-base:headers.cpp>
#define __THIS_IS_CPP11__
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

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif


// @snippet<sh19910711/contest:utils/collection_prototype.cpp>
namespace utils {
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class Iterator, class Value> void fill( Iterator, const int&, const Value& );
  
  // copy(from, num, to)
  template <class Iterator> void copy( Iterator from, const int& num, Iterator to );
  
  // sort(begin, num)
  template <class Iterator> void sort( Iterator begin, const int& n );
  
  // reverse(begin, num)
  template <class Iterator> void reverse( Iterator begin, const int& n );
  
#endif
}

// @snippet<sh19910711/contest:utils/misc_prototype.cpp>
namespace utils {
  // max(a, b), min(a, b)
  template <class T> void max( T& a, const T& b );
  template <class T> void min( T& a, const T& b );
  // to_s(v), ret = to_type(str)
  template <class T> std::string to_string( const T& v );
  template <class T> T to_type( const std::string& s );
  
}

// @snippet<sh19910711/contest:utils_prototypes.cpp>

// @snippet<sh19910711/contest-base:solution/template-class.cpp>
namespace solution {
  struct Input;
  struct Output;
  struct Storages {
    Input* in;
    Output* out;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-interface.cpp>
namespace solution {
  struct SolverInterface {
    virtual ~SolverInterface() {}
    virtual const Output* solve( const Input* in, Output* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-interface.cpp>
namespace solution {
  struct SolutionInterface {
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    virtual bool action() = 0;
    virtual bool input( Input* s ) = 0;
    virtual void output( const Output* s ) = 0;
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    SolverInterface* solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    virtual ~SolutionBase() {};
    
    int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
    
    bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-primitive-types.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base:solution/template-constants.cpp>
namespace solution {
  // constants
  const Int SIZE = 32;
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace utils;
  typedef std::array<Int, SIZE> IntArray;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct Input {
    Int N;
    Int X;
    IntArray A;
  };
  
  struct Output {
    Int result;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  struct Counter {
    typedef std::map <Int, Int> Map;
    typedef std::array <Map, SIZE> MapArray;
    typedef std::set <Int> Set;

    Int N;
    IntArray A;
    MapArray memo;
    Set S;

    void init() {
      // std::cout << "@Counter#init" << std::endl;
      for ( auto& m : memo )
        m.clear();
      // std::fill(std::begin(memo), std::end(memo), -1);
      N = in->N;
      std::copy(std::begin(in->A), std::begin(in->A) + in->N, std::begin(A));
      std::sort(std::begin(A), std::begin(A) + N, std::greater<Int>());
      init_set();
    }

    void rec2( const Int& k, const Int& s, const Int& x ) {
      if ( k >= N )
        return;
      if ( k >= std::min(N, Int(5)) )
        return;
      S.insert(x);
      for ( Int i = 0; i < N; ++ i ) {
        Int bi = Int(1) << i;
        if ( s & bi )
          continue;
        rec2(k + 1, s | bi, x + A[i]);
      }
    }

    void init_set() {
      S.clear();
      rec2(0, 0, 0);
    }

    Int rec( const Int& k, const Int& rem, const Int& x ) {
      if ( N - k <= std::min(in->N, Int(5)) ) {
        if ( ! S.count(x) )
          return 0;
      }
      if ( x < 0 || x - rem > 0 )
        return 0;
      if ( k >= N ) {
        return x == 0 ? 1 : 0;
      }
      if ( memo[k].count(x) )
        return memo[k][x];
      Int& res = memo[k][x];
      res = 0;
      res += rec(k + 1, rem - A[k], x);
      res += rec(k + 1, rem - A[k], x - A[k]);
      return res;
    }

    Int count() {
      return rec(0, std::accumulate(std::begin(A), std::begin(A) + N, Int(0)), in->X);
    }

    const Input* in;
    Counter( const Input* in ): in(in) { init(); }
    typedef std::unique_ptr<Counter> Pointer;
    static Pointer create( const Input* in ) { return Pointer(new Counter(in)); }
  };

  struct Solver: SolverInterface {
    const Output* solve( const Input* in, Output* out ) {
      auto counter = Counter::create(in);
      out->result = counter->count();
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( Input* in ) {
      if ( ! ( std::cin >> in->N >> in->X ) )
        return false;
      for ( auto i = 0; i < in->N; ++ i )
        if ( ! ( std::cin >> in->A[i] ) )
          return false;
      return true;
    }
    void output( const Output* out ) {
      std::cout << out->result << std::endl;
    }
  };
}

// @snippet<sh19910711/contest-base:main_func.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  // desc: http://meme.biology.tohoku.ac.jp/students/iwasaki/cxx/speed.html#id18
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  // 
  using namespace solution;
  static Input      in;
  static Output     out;
  static Storages   storages;
  static Solution   solution;
  static Solver     solver;
  storages.in       = &in;
  storages.out      = &out;
  solution.storages = &storages;
  solution.solver   = &solver;
  return solution.run();
}
#endif

// @snippet<sh19910711/contest:utils/collection.cpp>
namespace utils {
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class Iterator, class V> void fill( Iterator begin, const int& num, const V& value ) {
    std::fill(begin, begin + num, value);
  }
  
  // copy(from, num, to)
  template <class Iterator> void copy( Iterator from, const int& num, Iterator to ) {
    std::copy(from, from + num, to);
  }
  
  // sort(begin, num)
  template <class Iterator> void sort( Iterator begin, const int& num ) {
    std::sort(begin, begin + num);
  }
  
  // reverse(begin, num)
  template <class Iterator> void reverse( Iterator begin, const int& num ) {
    std::reverse(begin, begin + num);
  }
  
#endif
}

// @snippet<sh19910711/contest:utils/misc.cpp>
namespace utils {
  // max(a, b), min(a, b)
  template <class T> void max( T& a, const T& b ) { a = std::max(a, b); }
  template <class T> void min( T& a, const T& b ) { a = std::min(a, b); }
  // to_s(v), ret = to_type(str)
  template <class T> std::string to_string( const T& v ) { std::ostringstream oss; oss << v; return oss.str(); }
  template <class T> T to_type( const std::string& s ) { std::istringstream iss(s); T res; iss >> res; return res; }
  
}

// @snippet<sh19910711/contest:utils.cpp>

// @snippet<sh19910711/contest-base:main.cpp>

