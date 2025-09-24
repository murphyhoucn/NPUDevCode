#include <iostream>
#include <climits>

using namespace std;

int main()
{
    short n_short = SHRT_MAX;
    int n_int = INT_MAX;
    long n_long = LONG_MAX;
    long long n_llong = LLONG_MAX;

    cout << "short is " << sizeof(short) << " bytes" << endl;
    cout << "int is " << sizeof(int) << " bytes" << endl;
    cout << "long is " << sizeof(long) << " bytes" << endl;
    cout << "long long is " << sizeof(long long) << " bytes" << endl;

    cout << "max short is " << n_short << endl;
    cout << "max int is " << n_int << endl;
    cout << "max long is " << n_long << endl;
    cout << "max long long is " << n_llong << endl;
    
    cout << "min int is " << INT_MIN << endl;
    cout << "bits per byte is " << CHAR_BIT << endl;

    return 0;
}