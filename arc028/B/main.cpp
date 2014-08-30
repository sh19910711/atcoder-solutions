#include <iostream>
#include <set>
using namespace std;

typedef long long Int;

const int N_MAX = 100000 + 11;

Int N;
Int K;
Int X[N_MAX];

bool input() {
  if ( cin >> N >> K ) {
    for ( int i = 0; i < N; ++ i ) cin >> X[i];
    return true;
  }
  return false;
}

Int A[N_MAX];
Int B[N_MAX];
bool U[N_MAX];

int main() {
  while ( input() ) {
    fill(U, U + N_MAX, false);
    for ( int i = 0; i < N; ++ i ) A[X[i]] = i + 1;
    int bc = 0;
    int cur = K;
    for ( int i = N - 1; i >= K - 1; -- i ) {
      B[bc ++] = A[cur];
      U[X[i]] = true;
      if ( X[i] <= cur ) {
        cur ++;
      }
      while ( U[cur] ) cur ++;
    }
    for ( int i = bc - 1; i >= 0; -- i ) cout << B[i] << endl;
  }
  return 0;
}
