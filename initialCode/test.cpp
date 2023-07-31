#include <iostream>
#include <vector>
using std::cout;

int main(){
    int b = 5 % 10;
    int levelO = 5 > 6 ? (b > 5 ? b : 5) : b;
    cout << 9.5 * levelO * 10;
}