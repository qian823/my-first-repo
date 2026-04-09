#include <iostream>
using namespace std;

int fun(int a, int b = 10, int c = 20)
{
    return a + a + b + c;
}

int main()
{
    int a = 8;
    int d = fun(a);
    cout << d << endl;
    return 0;
}