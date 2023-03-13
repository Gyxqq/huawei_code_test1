#include"data_struct.h"
#ifndef c_robot.h
#define c_robot.h
class robot
{ // 机器人类


 

public:

struct robot_data data; //储存机器人数据
  /*
  int num;           // 机器人编号
  double x, y;       // 机器人位置
  int table;         // 机器人所处的工作台ID -1表示当前没有处于任何工作台周围 从0开始
  int object;        // 携带物品种类 0表示未携带
  double time_value; // 时间价值系数
  double col_value;  // 碰撞价值系数
  double ang_speed   // 角速度
      double speed_x,
      speed_y;   // 线速度
  double toward; // 朝向 与平面直角坐标系的单位圆射线方向相同 toward=0时向右
   bool control_flag; //标志位，1表示机器人正在接受调度，0表示机器人处于空闲状态
  */
back_command* route_control(map& now_map);
//从源地址取物品送到目的地址的路线控制
bool avoid_crash(robot bot[]);
//返回五帧后是否有碰撞风险 有返回1 无返回0


};

#endif