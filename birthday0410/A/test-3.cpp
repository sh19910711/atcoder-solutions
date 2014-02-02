#include<iostream>

using namespace std;

int C[3][32];

int main()
{
  int A, B;

  while(cin >> A >> B, A!=0 || B!=0) {
    for(int i=0; i<32; ++i) {
      C[0][i] = (A >> i) & 1;
      C[1][i] = (B >> i) & 1;
    }

    for(int i=0; i<32; ++i) {
      if(C[0][i] + C[1][i] >= 2) {
        C[C[1][i-1] & 1][i+1]++;
        C[0][i]--;
        C[1][i]--;
      }
      C[2][i] = C[0][i] + C[1][i];
    }

    int R = 0;
    for(int i=0; i<32; ++i) {
      R |= C[2][i] << i;
    }

    cout << R << endl;
  }

  return 0;
}
