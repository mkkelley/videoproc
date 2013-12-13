#include "ThreadPool.h"
#include <functional>
#include <iostream>
#include <unistd.h>

void test_func_c() {
    for (int i = 0; i < 10; i++) {
        std::cout << "hi" << std::endl;
    }
}

void test_func_g() {
    for (int i = 0; i < 10; i++) {
        std::cout << "low" << std::endl;
    }
}

int main() {
    ThreadPool tp(4);
    std::function<void()> f(test_func_c);
    tp.submit(test_func_g);
    std::cout << "gothere" <<std::endl;
    tp.submit(test_func_c);
    for (int i = 0; i < 10; i++) {
        std::cout << "test" << std::endl;
    }
    tp.wait(0);
    return 0;
}
