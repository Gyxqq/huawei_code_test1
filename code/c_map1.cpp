#include"c_map1.h"
table* map1::gettable()
{

    return table_in_map;
}
int* map1::gettable_num()
{
    return &table_num;
}