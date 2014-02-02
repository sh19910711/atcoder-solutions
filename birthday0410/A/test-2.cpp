#include <iostream>

using namespace std;

int myAbs(int n)
{
  if(n < 0) return -n;
  else return n;
}

int main()
{
  int A, B;

  while(cin >> A >> B, (A|B) != 0) {
    while(myAbs(A) >= 100000) {
      if(A > 0) {
        B += 100000;
        A -= 100000;
      } else {
        B -= 100000;
        A += 100000;
      }
    }

    if(A > 0) {
      for(int i=0; i<A; ++i) {
        B++;
      }
    } else {
      for(int i=0; i<-A; ++i) {
        B--;
      }
    }

    cout << B << endl;
  }

  return 0;
}
