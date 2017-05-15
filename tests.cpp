#include "args.hpp"
#include <iostream>

int foo (int a , int b, int c) {
     std::cout << arg_in<1>{}(a, b, c) << std::endl;
}

int bar (int& a , int& b, int& c) {
     std::cout << arg_in<1>{}(a, b, c) << std::endl;
}

int main() {
    int a = 233;
    int b = 234;
    int& a_ref = a;
    int& b_ref = b;
    int& c_ref = b;
    bar(a_ref, b_ref, c_ref);
}
