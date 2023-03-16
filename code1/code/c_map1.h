#ifndef c_map1.h
#define c_map1.h
#include "data_struct.h"
class map1
{

public:
    table *table_in_map; // 储存工作台信息的数组
    int table_num;       // 储存工作台数量

    table *gettable(); // 返回工作台数组

    int *gettable_num(); // 返回工作台数量
};
#endif