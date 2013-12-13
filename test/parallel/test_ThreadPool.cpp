#include "ThreadPool.h"
#include <functional>
#include <iostream>
#include <unistd.h>

void test_func_c() {
    for (int i = 0; i < 10; i++) {
        std::cout << "hi" << std::endl;
        //usleep(50000);
    }
}

void test_func_g() {
    for (int i = 0; i < 10; i++) {
        std::cout << "low" << std::endl;
        //usleep(50000);
    }
}

int main() {
    ThreadPool tp(4);
    std::function<void()> f(test_func_c);
    //std::cout << tp.submit(f);
    tp.submit(test_func_g);
    std::cout << "gothere" <<std::endl;
    tp.submit(test_func_c);
    for (int i = 0; i < 10; i++) {
        std::cout << "test" << std::endl;
        //usleep(50000);
    }
    return 0;
}
