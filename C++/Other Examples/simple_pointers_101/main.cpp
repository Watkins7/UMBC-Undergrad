#include <iostream>

int main() {

    int a = 5;
    int b = 10;
    int* c = &a;
    c = &b;
    *c = 20;
    std::cout << a << b << std::endl;
    return 0;
}
