#include "ThreadPool.h"

#include <functional>
#include <iostream>

std::mutex _cout_lock;

void test_func_c() {
    for (int i = 0; i < 10; i++) {
        std::unique_lock<std::mutex> l(_cout_lock);
        std::cout << "hi" << std::endl;
    }
}

void test_func_g() {
    for (int i = 0; i < 10; i++) {
        std::unique_lock<std::mutex> l(_cout_lock);
        std::cout << "low" << std::endl;
    }
}

int main() {
    std::shared_ptr<ThreadPool> tp(new ThreadPool(4));
    std::function<void()> f(test_func_c);

    tp->submit(test_func_g);
    tp->submit(test_func_c);

    for (int i = 0; i < 10; i++) {
        std::unique_lock<std::mutex> l(_cout_lock);
        std::cout << "test" << std::endl;
    }
    tp->wait(0);
    tp->terminate_all_workers();
    return 0;
}
