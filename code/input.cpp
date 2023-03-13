/*
实现数据输入功能(不包括初始化)
*/
#include"c_robot.h"
#include <iostream>
#include <cstdio>
bool input(int &now_frame, int &now_money, table *table_in_map, int &table_num, robot *robot_in_map)
{
    int state_in_decimal;
    // 十进制整数表示的原材料格状态
    std::cin >> now_frame >> now_money;
    // 第一行：输入帧序号和当前金钱数
    std::cin >> table_num;
    // 第二行：输入厂上的工作台数量
    for (int i = 0; i < table_num; i++)
    {
        table_in_map[i].num = i;
        std::cin >> table_in_map[i].type;
        std::cin >> table_in_map[i].x >> table_in_map[i].y;
        std::cin >> table_in_map[i].rest;
        std::cin >> state_in_decimal;
        // 输入原材料格状态
        for (int j = 0; j <= 7; j++)
        {
            table_in_map[i].instats[j] = (bool)(state_in_decimal % 2);
            state_in_decimal /= 2;
        }
        std::cin >> table_in_map[i].outstats;
    }
    // 输入工作台的相关数据
    for (int i = 0; i < 4; i++)
    {
        robot_in_map[i].data.num= i;
        std::cin >> robot_in_map[i].data.table;
        std::cin >> robot_in_map[i].data.object;
        std::cin >> robot_in_map[i].data.time_value;
        std::cin >> robot_in_map[i].data.col_value;
        std::cin >> robot_in_map[i].data.ang_speed;
        std::cin >> robot_in_map[i].data.speed_x >> robot_in_map[i].data.speed_y;
        std::cin >> robot_in_map[i].data.toward;
        std::cin >> robot_in_map[i].data.x >> robot_in_map[i].data.y;
    }
    // 输入4个机器人的相关数据
    if (scanf("OK"))
    {
        return true;
    }
    else
    {
        return false;
    }
    // 最后一行输入"OK",则为true,反之则为false
}