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
        continue; // 判断工作台是不是123号仅生产的工作台
      if (table_now[i].rest == 0)
        continue; // 判断工作台所否处于阻塞状态
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
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num2], i, table2);
          command_count++;
        }
      }

      if (table_now[i].type == 5)
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
        int table2 = find_near_table(table_now, table_num_now, i, 3);
        if (table2 != -1)
        {

          int bot_num2 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table2;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num2;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num2], i, table2);
          command_count++;
        }
      }

      if (table_now[i].type == 6)
      {
        int table1 = find_near_table(table_now, table_num_now, i, 2);
        if (table1 != -1)
        {

          int bot_num1 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table1;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num1;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table1);
          command_count++;
        }
        int table2 = find_near_table(table_now, table_num_now, i, 3);
        if (table2 != -1)
        {

          int bot_num2 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table2;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num2;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num2], i, table2);
          command_count++;
        }
      }

      if (table_now[i].type == 7)
      {
        int table1 = find_near_table(table_now, table_num_now, i, 4);
        if (table1 != -1)
        {

          int bot_num1 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table1;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num1;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table1);
          command_count++;
        }
        int table2 = find_near_table(table_now, table_num_now, i, 5);
        if (table2 != -1)
        {

          int bot_num2 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table2;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num2;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num2], i, table2);
          command_count++;
        }

        int table3 = find_near_table(table_now, table_num_now, i, 6);
        if (table3 != -1)
        {

          int bot_num3 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table3;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num3;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num3], i, table3);
          command_count++;
        }
      }

      if (table_now[i].type == 8)
      {
        int table1 = find_near_table(table_now, table_num_now, i, 7);
        if (table1 != -1)
        {

          int bot_num1 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table1;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num1;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table1);
          command_count++;
        }
      }
      if (table_now[i].type == 9)
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

          int bot_num1 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table2;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num1;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table2);
          command_count++;
        }
        int table3 = find_near_table(table_now, table_num_now, i, 3);
        if (table3 != -1)
        {

          int bot_num1 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table3;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num1;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table3);
          command_count++;
        }
        int table4 = find_near_table(table_now, table_num_now, i, 4);
        if (table4 != -1)
        {

          int bot_num1 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table4;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num1;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table4);
          command_count++;
        }
        int table5 = find_near_table(table_now, table_num_now, i, 5);
        if (table5 != -1)
        {

          int bot_num1 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table5;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num1;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table5);
          command_count++;
        }
        int table6 = find_near_table(table_now, table_num_now, i, 6);
        if (table6 != -1)
        {

          int bot_num1 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table6;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num1;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table6);
          command_count++;
        }
        int table7 = find_near_table(table_now, table_num_now, i, 7);
        if (table7 != -1)
        {

          int bot_num1 = find_near_bot(table_now[i], now_bot);
          now_command[command_count].des = table7;
          now_command[command_count].ori = i;
          now_command[command_count].robot_num = bot_num1;
          now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table7);
          command_count++;
        }
      }
    }
    // 生成调度指令
    std::sort(now_command, now_command + command_count, sort1);
    std::sort(now_command, now_command + command_count, sort2); // 排序
    int now = -1;

    for (int i = 0; i < command_count; i++)
    {
      if (now_command[i].robot_num != now)
      {
        now = now_command[i].robot_num;
        now_bot[now_command[i].robot_num].data.ori = now_command[i].ori; // 设定起始地
        now_bot[now_command[i].robot_num].data.des = now_command[i].des; // 设定目的地
        now_bot[now_command[i].robot_num].data.control_flag = 1;         // 将机器人切换为正在接受调度的状态
      }
      if (now_command[i].robot_num == now)
        continue;
    }
    return 1;
  }
}
inline int find_near_bot(table &this_table, robot bot[])
{
  int num = 0;
  double des = 0;
  for (int i = 0; i < 3; i++)
  {

    if (bot[i].data.control_flag > 0) // 判断机器人所否被调度
      continue;
    else
    {
      double now_des = pow(this_table.x - bot[i].data.x, 2) + pow(this_table.y - bot[i].data.y, 2); // 计算距离
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
    if (i == now_table) // 判断是否是当前工作台
      continue;
    if (tab[i].type != object_type) // 判断产物的类型是否和请求类型相同
      continue;
    if (tab[i].out_control == 1) // 判断产物是否已被调度
      continue;
    if (tab[i].outstats == 0) // 判断输出格所否有产物
      continue;
    double now_des = pow(tab[now_table].x - tab[i].x, 2) + pow(tab[now_table].y - tab[i].y, 2); // 计算距离
    if (now_des >= des)
      num = i;
  }

  return num; // 返回最近的有所请求物品的工作台的编号
}
bool sort1(bot_control_command a, bot_control_command b)
{
  return a.robot_num < b.robot_num;
}
bool sort2(bot_control_command a, bot_control_command b)
{
  return a.robot_num <= b.robot_num && a.hash > b.hash; // 排序
}