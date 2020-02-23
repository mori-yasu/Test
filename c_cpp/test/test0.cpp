//#include "header/test.h"
#include <vector>
#include <math.h>
#include <iostream>

using namespace std;

int main ()
{
    float a = 1,b = 9;
    float b2 = sqrt(b);
    std::vector<float> vec;
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(b2);

    cout << a << b << b2 << endl;
    for(int i = 0; i < vec.size();i++)
    {
        cout << vec.at(i) << endl;
    }

    return 0;
}