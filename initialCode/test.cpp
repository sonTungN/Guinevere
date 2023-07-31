#include <iostream>
#include <vector>
using std::cout;
bool isPrime(int n) 
{ 
    // Corner case 
    if (n <= 1) 
        return false; 

    // Check from 2 to n-1 
    for (int i = 2; i < n; i++) 
        if (n % i == 0) 
            return false; 

    return true; 
} 
int main(){
    int n1 = ((1 + 0) % 5 + 1) * 3;
    int s1 = 0;
    for(int i {0}; i < n1; i++){
        s1 += (99 - 2 * i);
    }
    int a = 199;
    a += (s1 % 100);
    int nearestPrime {};
    int i = 0;

    while(true){
        if(isPrime(i)){
            if(i > a){
                break;
            }
        }
        i++;
    }
    cout << i;
}