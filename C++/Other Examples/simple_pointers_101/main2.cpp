#include <iostream>
using namespace std;

int main() {
    int  x = 5;
    int *ptr1 = &x;
    int *ptr2;
    ptr2 = &x;
    int *ptr3 = ptr1;

    int val = *ptr1;

    cout << val << " " << ptr1 << endl;
    val = 9;
    cout << val << " " << ptr1 << endl;

    cout << *ptr1 << " " << ptr2 << " " << ptr3 << endl;
    return 0;
}
