#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    int n;
    cin >> n;
    int yy;
    int mm;
    int dd;
    yy = n / 3600;
    mm = n % 3600 / 60;
    dd = n % 3600 % 60;
    printf("%02d:%02d:%02d\n", yy, mm, dd);
    return 0;
}