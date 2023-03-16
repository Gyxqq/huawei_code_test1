#ifndef c_robot.h
#define c_robot.h
#include"c_map1.h"
#include"data_struct.h"
class robot
{ // 机器人类
public:

 struct robot_data data; // 储存机器人数据

    back_command* route_control(map1& now_map);
    // 从源地址取物品送到目的地址的路线控制
    bool avoid_crash(robot bot[]);
    
    
    // 返回五帧后是否有碰撞风险 有返回1 无返回0
    back_command* bot_avoid_crash(robot bot[]);

    // 生成小车避障时需要的指令集
};
#endif