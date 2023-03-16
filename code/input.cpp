#include"data_struct.h"
#include<iostream>
#include"c_robot.h"
bool input(int& now_frame, int& now_money, table* table_in_map, int* table_num, robot* robot_in_map)
{
    int state_in_decimal;
    // 十进制整数表示的原材料格状态
    std::cin >> now_frame >> now_money;
    std::cerr << now_frame <<" "<< now_money<<std::endl;
    //std::cerr<<"frame="<<now_frame<<"money="<<now_money<<std::endl;
    // 第一行：输入帧序号和当前金钱数
    std::cin >> *table_num;
    // 第二行：输入厂上的工作台数量
    std::cerr <<*table_num<<std::endl;
    for (int i = 0; i < *table_num; i++)
    {
      std::cerr<<"table_id "<<table_in_map[i].num<<" table_type"<<table_in_map[i].type<<std::endl;
        table_in_map[i].num = i;
        std::cin >> table_in_map[i].type;
        std::cerr << table_in_map[i].type<<" ";
        std::cin >> table_in_map[i].x >> table_in_map[i].y;
        std::cerr << table_in_map[i].x <<" "<< table_in_map[i].y<<" ";
        std::cin >> table_in_map[i].rest;
        std::cerr << table_in_map[i].rest<<" ";
        std::cin >> state_in_decimal;
         std::cerr << state_in_decimal<<" ";
        // 输入原材料格状态
        for (int j = 0; j <= 7; j++)
        {
            table_in_map[i].instats[j] = (bool)(state_in_decimal % 2);
            state_in_decimal /= 2;
        }
        std::cin >> table_in_map[i].outstats;
           std::cerr << table_in_map[i].outstats<<std::endl;
    }
    // 输入工作台的相关数据
    for (int i = 0; i < 4; i++)
    {
        robot_in_map[i].data.num = i;
        std::cin >> robot_in_map[i].data.table;
         std::cerr << robot_in_map[i].data.table<<" ";
        std::cin >> robot_in_map[i].data.object;
          std::cerr << robot_in_map[i].data.object<<" ";
        std::cin >> robot_in_map[i].data.time_value;
        std::cerr << robot_in_map[i].data.time_value<<" ";
        std::cin >> robot_in_map[i].data.col_value;
          std::cerr << robot_in_map[i].data.col_value<<" ";
        std::cin >> robot_in_map[i].data.ang_speed;
         std::cerr << robot_in_map[i].data.ang_speed<<" ";
        std::cin >> robot_in_map[i].data.speed_x >> robot_in_map[i].data.speed_y;
        std::cerr << robot_in_map[i].data.speed_x << " "<<robot_in_map[i].data.speed_y<<" ";
        std::cin >> robot_in_map[i].data.toward;
         std::cerr<< robot_in_map[i].data.toward<<" ";
        std::cin >> robot_in_map[i].data.x >> robot_in_map[i].data.y;
        std::cerr<< robot_in_map[i].data.x <<" "<< robot_in_map[i].data.y<<std::endl;;
    }
    // 输入4个机器人的相关数据
   char gyx[2]={};
   std::cin>>gyx;
   std::cerr<<gyx<<std::endl;
    // 最后一行输入"OK",则为true,反之则为false
}
