//
// Created by pc on 17.04.2021.
//

#include <iostream>
#include "tree.h"

int main() {
    srand(time(NULL));
    std::cout << "fuck u ";
    tree<int> first;

    for (int i = 0; i < 15; i++)
        first.append_or_replace(rand() % 200);


    printf("\ndepth: %zu\n", first.size_depth());


    first.show_left_to_right();


    //  for(auto i:first) std::cout<<i.get_value()<<"\t";

    return 0;
}