//
// Created by francisco on 02-10-15.
//

#ifndef ABBTHREAD_RANDOM_NUMBERS_H
#define ABBTHREAD_RANDOM_NUMBERS_H

#include <random>
#include <iostream>


int random(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000);

    for (int n=0; n<100; ++n)
        std::cout << dis(gen) << ' ';
    std::cout << '\n';
}

#endif //ABBTHREAD_RANDOM_NUMBERS_H
