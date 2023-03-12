/*
实现数据输入功能(不包括初始化)
*/
#include"data_struct.h"
#include<iostream>
#include<cstdio>
using namespace std;
bool input(int& now_frame,int& now_money,table* table_in_map,int& table_num,robot* robot_in_map){
    int state_in_decimal;
    //十进制整数表示的原材料格状态
    cin>>now_frame>>now_money;
    //第一行：输入帧序号和当前金钱数
    cin>>table_num;
    //第二行：输入厂上的工作台数量
    for(int i=1; i<=table_num; i++){
        table_in_map[i].num=i;
        cin>>table_in_map[i].type;
        cin>>table_in_map[i].x>>table_in_map[i].y;
        cin>>table_in_map[i].rest;
        cin>>state_in_decimal;
        //输入原材料格状态
        for(int j=0; j<=7; j++){
            table_in_map[i].instats[j]=(bool) (state_in_decimal%2);
            state_in_decimal/=2;
        }
        cin>>table_in_map[i].outstats;
    }
    for(int i=0; i<4; i++){
        robot_in_map[i].get_num(i);
        robot_in_map[i].get_table();
        robot_in_map[i].get_object();
        robot_in_map[i].get_time_value();
        robot_in_map[i].get_col_value();
        robot_in_map[i].get_ang_speed();
        robot_in_map[i].get_line_speed();
        robot_in_map[i].get_toward();
        robot_in_map[i].get_x_y();
    }
    if(scanf("OK")){
        return true;
    }
    else{
        return false;
    }
}