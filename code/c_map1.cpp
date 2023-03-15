#include"c_map1.h"
#include<iostream>
table* map1::gettable()
{

    return table_in_map;
}
int* map1::gettable_num()
{
    std::cerr<<"map1"<<std::endl;
    return &table_num;
}