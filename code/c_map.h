#include "data_struct.h"
#include"c_robot.h"
#ifndef c_map.h
#define c_map.h
class map

{ // 地图类

private:
  table *table_in_map; // 储存工作台信息的数组
  int table_num;       // 储存工作台数量

public:
   bool mapinit(robot robot[]); // 地图初始化函数 从stdin读入数据 并动态内存分配创建一个table数组赋值给table_in_map

  table *gettable(); // 返回工作台数组

  int gettable_num(); // 返回工作台数量
};



#endif