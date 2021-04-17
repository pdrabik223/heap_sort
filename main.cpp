//
// Created by pc on 17.04.2021.
//

#include <iostream>
#include "tree.h"
int main(){

    std::cout<<"fuck u ";
    tree<int> first;
    first.append(12);
    first.append(1);
    for(auto i:first) std::cout<<i.get_value();
    return 0;
}