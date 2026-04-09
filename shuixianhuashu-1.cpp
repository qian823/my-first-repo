#include <iostream>
using namespace std;

int main() {
    int i = 100;
    while (i < 1000)
    {
        int a = i%10;
        int b = (i%100 - a)/10;
        int c = (i-a-b*10)/100;
        if(i == a*a*a + b*b*b + c*c*c)
        cout << i <<endl;
        i++;
    }
    system("pause");
    return 0;
}