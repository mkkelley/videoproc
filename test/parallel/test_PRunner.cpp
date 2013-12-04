#include "PRunner.h"

#include <iostream>

int main() {
    PRunner p;
    p.add([](){
            std::cout << "test" << std::endl;
            });
}
