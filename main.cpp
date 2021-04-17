//
// Created by pc on 17.04.2021.
//

#include <iostream>
#include "tree.h"
int main(){

    std::cout<<"fuck u ";
    tree<int> first;
    std::vector<int> second = {11,2,4,3,10,7,14,5,0,1,6};

    for(int i=0;i<10;i++)
    first.append_or_replace(rand()%20);




    for(auto i:first) std::cout<<i.get_value()<<"\t";

    return 0;
}