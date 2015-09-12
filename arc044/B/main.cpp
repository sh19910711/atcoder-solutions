#include <bits/stdc++.h>
using namespace std;

typedef long long Int;

const int SIZE = 100000 + 11;
const Int MOD = 1000000000 + 7;

int n;
int a[SIZE];
int level[SIZE];
Int fact[SIZE];
Int pow2[SIZE];

void init() {
  fill(level, level + SIZE, 0);
}

Int extgcd(const Int a, const Int b, Int &x, Int &y) {
  Int g = a;
  x = 1;
  y = 0;
  if (b) {
    g = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  }
  return g;
}

Int mod_inv(const Int a, const Int m) {
  Int x, y;
  if (extgcd(a, m, x, y) == 1)
    return (x + m) % m;
  return -1;
}

Int mod_comb(const Int n, const Int k, const Int m) {
  if (n < 0 || k < 0 || n < k) {
    return 0;
  } else {
    return fact[n] * mod_inv(fact[k] * fact[n - k] % m, m) % m;
  }
}

void gen_fact(const Int m) {
  fact[0] = 1;
  for (int i = 0; i < SIZE - 1; ++i) {
    fact[i + 1] = ((i + 1) * fact[i] % m);
  }
}

bool input() {
  if (cin >> n) {
    for (int i = 0; i < n; ++i) cin >> a[i];
    return true;
  }
  return false;
}

void gen_level() {
  for (int i = 0; i < n; ++i) {
    ++level[a[i]];
  }
}

void gen_pow2() {
  pow2[0] = 1;
  for (int i = 0; i < n; ++i) {
    pow2[i+1] = (2 * pow2[i]) % MOD;
  }
}

template <class T>
void print(int n, T* a) { // to debug
  for (int i = 0; i < n; ++i) {
    cout << a[i] << ", ";
  }
  cout << endl;
}

bool impossible() {
  if (a[0]) return true;
  for (int i = 1; i < n; ++i)
    if (!a[i]) return true;
  return false;
}

Int solve() {
  init();
  gen_level();
  gen_pow2();
  print(n, level);
  if (impossible()) return 0;
  Int res = 1;
  for (int i = 1; i < n; ++i) {
    if (!level[i]) break;
  }
  return res;
}

int main() {
  gen_fact(MOD);
  while (input()) {
    cout << "res: " << solve() << endl;
  }
  return 0;
}
