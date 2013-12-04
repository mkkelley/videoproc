#include "ThreadPool.h"
#include <functional>
#include <iostream>

void test_func_c() {
    while (1) {
        std::cout << "hi" << std::endl;
    }
}

void test_func_g() {
    while (1) {
        std::cout << "low" << std::endl;
    }
}

int main() {
    ThreadPool tp;
    std::function<void()> f(test_func_c);
    //std::cout << tp.submit(f);
    tp.submit(test_func_g);
    tp.submit(test_func_c);
    while (1) {
        std::cout << "test" << std::endl;
    }
    return 0;
}
