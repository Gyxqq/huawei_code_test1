
#include"c_robot.h"
#include<iostream>
#include<math.h>
#include<string.h>
back_command* robot::route_control(map1& now_map)
{
    std::cerr<<"route_control"<<std::endl;
    const double PI = 3.14159;                     // 圆周率π的值
    const double min_angle = 0.001;              // 机器人的朝向和机器人与目标工作台夹角的最小值
    const double max_tan_angle=100;
    const double max_speed = 6;                    // 机器人行驶的最大速度
    double delta_x, delta_y;                       // 机器人与所要去的工作台的坐标变化量
    double tan_angle, angle;                       // 计算机器人与工作台连线的角度
    double turn_angle=0;                             // 需要旋转的角度
    double turn_angle_positive=0;                    // 需要旋转的角度的绝对值
    table* goto_table;
                               // 定义地图上的工作台
    goto_table = now_map.gettable(); 
                  // 返回地图上的工作台
    back_command* command_need = new back_command; // 声明需要返回的指令
    std::cerr<<"gyx "<<std::endl;  
    command_need->command_num = 0;                 // 指令个数初始化
    command_need->back_command=new command[8];

    std::cerr<<"flag="<<data.control_flag<<std::endl;
    if (data.table == data.ori)
    {
        std::cerr<<"gyx1 ";
        strcpy(command_need->back_command[command_need->command_num].command, "buy");
        command_need->back_command[command_need->command_num].arg1 = data.num;
        command_need->back_command[command_need->command_num].command_tpye = 1;
        command_need->command_num++;
        data.control_flag = 2;
    } // 机器人到达起点
    else if (data.table == data.des)
    {
        std::cerr<<"gyx2 ";
        strcpy(command_need->back_command[command_need->command_num].command, "sell");
        command_need->back_command[command_need->command_num].arg1 = data.num;
        command_need->back_command[command_need->command_num].command_tpye = 1;
        command_need->command_num++;
        data.control_flag = 0;
    } // 机器人到达终点
    if (data.control_flag == 1)
    {
        std::cerr<<"gyx3 ";
        delta_x = goto_table[data.ori].x - data.x;
        delta_y = goto_table[data.ori].y - data.y;
        tan_angle = delta_y / delta_x;
        // if(tan_angle>=max_tan_angle||tan_angle<=-1*max_tan_angle){
        //     angle=PI/2;
        //     if(delta_y<0){
        //         angle*=(-1);
        //     }
        // }
        if (delta_x >= 0)
        {
            angle = atan(tan_angle);
        }
        else if (delta_y >= 0)
        {
            tan_angle *= -1;
            angle = atan(tan_angle);
            angle = PI - angle;
        }
        else if (delta_y < 0)
        {
            tan_angle *= -1;
            angle = atan(tan_angle);
            angle = -1 * PI - angle;
        }
    } // 机器人去往起点
    else if (data.control_flag == 2)
    {
        std::cerr<<"gyx4 ";
        delta_x = goto_table[data.des].x - data.x;
        delta_y = goto_table[data.des].y - data.y;
        tan_angle = delta_y / delta_x;
        if (delta_x >= 0)
        {
            angle = atan(tan_angle);
        }
        else if (delta_y >= 0)
        {
            tan_angle *= -1;
            angle = atan(tan_angle);
            angle = PI - angle;
        }
        else if (delta_y < 0)
        {
            tan_angle *= -1;
            angle = atan(tan_angle);
            angle = -1 * PI - angle;
        }
    }                                                                         // 机器人去往终点
    turn_angle = data.toward - angle;                                         // 机器人朝向与所要转到的朝向的角度的差值
    if(turn_angle>PI){
        turn_angle=turn_angle-2*PI;
    }
    else if(turn_angle<-1*PI){
        turn_angle=2*PI+turn_angle;
    }
    turn_angle_positive = (turn_angle >= 0) ? turn_angle : (-1 * turn_angle);
    std::cerr<<"\nangle="<<angle<<std::endl;
    std::cerr<<"\nturn_angle="<<turn_angle<<std::endl;
     // 计算角度差值的绝对值
    std::cerr<<"gyx5 controlflag"<<data.control_flag<<std::endl;
    if(data.control_flag==0){
        strcpy(command_need->back_command[command_need->command_num].command, "rotate");
        command_need->back_command[command_need->command_num].arg1 = data.num;
        command_need->back_command[command_need->command_num].arg2 = 0;
        command_need->back_command[command_need->command_num].command_tpye = 0;
        command_need->command_num++;
        
        return command_need;
    }
    else if (turn_angle_positive <= min_angle)
    {
        strcpy(command_need->back_command[command_need->command_num].command, "rotate");
        command_need->back_command[command_need->command_num].arg1 = data.num;
        command_need->back_command[command_need->command_num].arg2 = 0;
        command_need->back_command[command_need->command_num].command_tpye = 0;
        command_need->command_num++;
    } // 当差值角度小于最小角度时，角速度为0
    else
    {
        strcpy(command_need->back_command[command_need->command_num].command, "rotate");
        command_need->back_command[command_need->command_num].arg1 = data.num;
        if (turn_angle > 0)
        {
            command_need->back_command[command_need->command_num].arg2 = PI;
        }
        else
        {
            command_need->back_command[command_need->command_num].arg2 = -1 * PI;
        }
        command_need->back_command[command_need->command_num].command_tpye = 0;
        command_need->command_num++;
    } // 反之，角速度设为最大
    strcpy(command_need->back_command[command_need->command_num].command, "forward");
    command_need->back_command[command_need->command_num].arg1 = data.num;
    command_need->back_command[command_need->command_num].arg2 = max_speed;
    command_need->back_command[command_need->command_num].command_tpye = 0;
    command_need->command_num++;
    // 机器人以最大速度前进
     std::cerr<<"route_control"<<std::endl;
    return command_need; // 返回指令
};
bool robot::avoid_crash(robot bot[])
{
    std::cerr<<"avoid_crash "<<std::endl;
    bool crash = false;
    double time = 0.02; // 一帧在判题器中的时间
    robot_data temp_bot[4];
    for (int frame = 0; frame < 5; frame++)
    {
        for (int i = 0; i < 4; i++) // 计算所有机器人下一帧大概的位置
        {
            temp_bot[i] = bot[i].data;
            double v = sqrt(temp_bot[i].speed_x * temp_bot[i].speed_x + temp_bot[i].speed_y * temp_bot[i].speed_y);
            temp_bot[i].x = temp_bot[i].x + v * cos(temp_bot[i].toward) * time;
            temp_bot[i].y = temp_bot[i].y + v * sin(temp_bot[i].toward) * time;
            temp_bot[i].toward = temp_bot[i].toward + temp_bot[i].ang_speed * time;
        }
        for (int i = 0; i < 4; i++) // 分别判断各个机器人是否可能碰撞（已考虑体积变大的情况）
        {
            if (i != data.num)
            {
                double distance = sqrt((temp_bot[i].x - temp_bot[data.num].x) * (temp_bot[i].x - temp_bot[data.num].x) + (temp_bot[i].y - temp_bot[data.num].y) * (bot[i].data.y - bot[data.num].data.y));
                if (!(temp_bot[i].control_flag || temp_bot[data.num].control_flag) && distance <= 0.45)
                {
                    crash = true;
                }
                else if ((temp_bot[i].control_flag || temp_bot[data.num].control_flag) && distance <= 0.53)
                {
                    crash = true;
                }
            }
        }
    }
    return crash;
}

back_command* robot::bot_avoid_crash(robot bot[])
{
    std::cerr<<"bot_avoid_crash "<<std::endl;
    const int pai = 3.14159;
    back_command* back = new back_command;
    if (bot[data.num].data.ang_speed >= 0)
    {
        back->command_num = 2;
        back->back_command[0].command_tpye = 0;
        strcpy(back->back_command[0].command, "forward");
        back->back_command[0].arg1 = data.num;
        back->back_command[0].arg2 = 6;
        strcpy(back->back_command[1].command, "rotate");
        back->back_command[1].arg1 = data.num;
        back->back_command[1].arg2 = -pai;
    }
    else
    {
        back->command_num = 2;
        back->back_command[0].command_tpye = 0;
        strcpy(back->back_command[0].command, "forward");
        back->back_command[0].arg1 = data.num;
        back->back_command[0].arg2 = 6;
        strcpy(back->back_command[1].command, "rotate");
        back->back_command[1].arg1 = data.num;
        back->back_command[1].arg2 = pai;
    }
    return back;
}
