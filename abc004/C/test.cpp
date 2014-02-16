#include <iostream>
using namespace std;

int A[6];

void print() {
  for ( int i = 0; i < 6; ++ i ) {
    std::cout << A[i] << ", ";
  }
  std::cout << std::endl;
}

int main() {
  for ( int i = 0; i < 6; ++ i )
    A[i] = i;
  std::cout << "start: ";
  print();
  for ( int i = 0; i < 1000; ++ i ) {
    std::swap(A[i % 5], A[i % 5 + 1]);
    std::cout << i << ": ";
    print();
  }
}
