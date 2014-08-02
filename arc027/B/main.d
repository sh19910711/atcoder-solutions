import std.stdio;
import std.string;
import std.bigint;
import std.array;
import std.range;
import std.ascii;
import std.math;
import std.numeric;
import std.algorithm;
import std.container;
import std.conv;
import core.bitop;

alias Int = long;


mixin template Inputter() {
  int n;
  string a;
  string b;

  bool input(T)(T s) {
    if ( readf(" %s", &n) ) {
      readf(" %s\n", &a);
      readf(" %s\n", &b);
      return true;
    }
    return false;
  }
}

mixin template Outputter() {
  Int res;

  void output() {
    writeln(res);
  }
}

mixin template Solver() {
  void init() {
    
  }
  
  void solve() {
    debug writeln("debug, ", n);
    debug writeln("debug, ", a);
    debug writeln("debug, ", b);

    Int[dchar] t;
    foreach ( char c; 'A' .. 'Z' + 1 ) {
      t[c] = 10;
    }

    debug writeln("debug", a.front, a);
    debug writeln("debug", b.front, b);

    dchar[dchar] p;
    foreach ( char c; 'A' .. 'Z' + 1 ) {
      p[c] = c;
    }

    foreach ( x; zip(a, b) ) {
      if ( isAlpha(x[0]) && isAlpha(x[1]) ) {
        if ( p[x[0]] != p[x[1]] ) {
          p[x[1]] = p[x[0]];
        }
      }
    }

    writeln(a.map!(c => p[c]));
    writeln(b.map!(c => p[c]));
    writeln(a, a[1]);
    writeln(b, b[1]);

    if ( isAlpha(to!dchar(a.front)) ) t[p[a.front]] = 9;
    if ( isAlpha(to!dchar(b.front)) ) t[p[b.front]] = 9;
    debug writeln("debug", t);
    foreach ( char c; 'A' .. 'Z' + 1 ) {
      // debug writeln(c, ", ", a.count(c), ", ", b.count(c));
      if ( a.count(c) == 0 && b.count(c) == 0 ) t[c] = 1;
    }
    debug writeln("debug", t);
    foreach ( x; zip(a, b) ) {
      if ( isAlpha(x[0]) ^ isAlpha(x[1]) ) {
        debug writeln(x[0], " ^ ", x[1]);
        if ( isAlpha(x[0]) ) t[p[x[0]]] = 1;
        else if ( isAlpha(x[1]) ) t[p[x[1]]] = 1;
      }
    }
    debug writeln("debug", t);
    res = 0;
  }
}

// Runner {{{
mixin template Runner() {
  void run() {
    while ( input(stdin) ) {
      init();
      solve();
      output();
    }
  }
}
// }}}

// Solution {{{
struct Solution {
  mixin Solver;
  mixin Inputter;
  mixin Outputter;
  mixin Runner;
}
// }}}

// main() {{{
Solution s;
void main() {
  s.run();
}
// }}}
