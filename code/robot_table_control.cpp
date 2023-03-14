#include "data_struct.h"
#include "c_map.h"
#include "c_robot.h"
#include "function.h"
#include <algorithm>
#include <math.h>
inline int find_near_bot(table &this_table, robot bot[]);
inline int find_near_table(table *tab, int table_num, int now_table, int object_type);
bool robot_table_control(map &now_map, robot now_bot[])
{
  table *table_now = now_map.gettable();
  int table_num_now = now_map.gettable_num();
  bot_control_command *final_bot_control = new bot_control_command[4]; // 存放机器人调度指令
  if (now_bot[0].data.control_flag > 0 && now_bot[1].data.control_flag > 0 && now_bot[2].data.control_flag > 0 && now_bot[3].data.control_flag > 0)
    return 0; // 无机器人空闲返回0
  else
  {
    int command_num = table_num_now * 2 + 7; // 可能的指令数目
    bot_control_command *now_command = new bot_control_command[command_num];
    int command_count; // 目前指令数
    for (int i = 0; i < table_num_now; i++)
    {
      if (table_now[i].type == 1 || table_now[i].type == 2 || table_now[i].type == 3)
        continue;
      if (table_now[i].type == 4)
      {
        int table1 = find_near_table(table_now, table_num_now, i, 1);
        if (table1 != -1)
        {

          int bot_num1 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table1;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num1;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table1);
          command_count++;
        }
         int table2 = find_near_table(table_now, table_num_now, i, 2);
        if (table2 != -1)
        {

          int bot_num2 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table2;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num2;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table2);
          command_count++;
        }
      }
    }
  }
}
inline int find_near_bot(table &this_table, robot bot[])
{
  int num = 0;
  double des = 0;
  for (int i = 0; i < 3; i++)
  {

    if (bot[i].data.control_flag > 0)
      continue;
    else
    {
      double now_des = pow(this_table.x - bot[i].data.x, 2) + pow(this_table.y - bot[i].data.y, 2);
      if (now_des >= des)
      {
        num = i;
        des = now_des;
      }
    }
  }
  return num; // 返回最近机器人的编号
}

inline int find_near_table(table *tab, int table_num, int now_table, int object_type)
{
  double num = -1;
  double des = 0;
  for (int i = 0; i < table_num; i++)
  {
    if (i == now_table)
      continue;
    if (tab[i].type != object_type)
      continue;
    double now_des = pow(tab[now_table].x - tab[i].x, 2) + pow(tab[now_table].y - tab[i].y, 2);
    if (now_des >= des)
      num = i;
  }

  return num; // 返回最近的有所请求物品的工作台的编号
}