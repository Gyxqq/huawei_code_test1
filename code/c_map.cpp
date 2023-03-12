#include "c_map.h"
#include "c_robot.h"
#include <iostream>
bool map::mapinit(robot bot[])
{
  char map[100][100] = {};
  int count_bot = 0;
  int count_table = 0;
  for (int y = 0; y < 50; y++)
  {
    for (int x = 0; x < 50; x++)
    {
      std::cin >> map[y][x];
      if (map[y][x] == 'A')
      {
        bot[count_bot].data.x = x;
        bot[count_bot].data.y = y; // 机器人位置数据储存
        count_bot++;
      }
      if (map[y][x] <= '9' && map[y][x] >= '0')
      {

        count_table++; //工作台计数
      }
    }
  } // 数据读入
  table_num = count_table;
  table_in_map = new table[table_num];//申请工作台数组储存空间
  count_table = 0;
  for (int y = 0; y < 50; y++)
  {
    for (int x = 0; x < 50; x++)
    {
      if (map[y][x] <= '9' && map[y][x] >= '0')
      {
        table_in_map[count_table].type = map[y][x] - '0';
        table_in_map[count_table].num = count_table;
        table_in_map[count_table].x = x;
        table_in_map[count_table].y = y; // 初始化工作台
        count_table++;
      }
    }
  }
  return 1;
}
table *map::gettable()
{

  return table_in_map;
}
int map::gettable_num()
{
  return table_num;
}
