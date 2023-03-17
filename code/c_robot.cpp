
#include "c_robot.h"
#include <iostream>
#include <math.h>
#include <string.h>
double turn_toward(double bot_toward, double table_bot_toward);
back_command *robot::route_control(map1 &now_map)
{
    std::cerr << "robot:" << data.num << " control_flag " << data.control_flag << " ori" << data.ori << " des" << data.des << " type" << data.object << std::endl;
    const double pai = 3.1415926;
    table *now_table = now_map.gettable();
    int now_table_num = *now_map.gettable_num();
    int ori = data.ori;
    int des = data.des;
    double speed = 6;
    double turn_speed = 1;
    if (data.x < 1 || data.x > 49 || data.y < 1 || data.y > 49)
        speed = 2;

    if (data.control_flag == -1)
    {
        command *com = new command[3];
        back_command *back = new back_command;
        back->command_num = 3;
        back->back_command = com;

        strcpy(com[0].command, "forward");
        com[0].command_tpye = 0;
        com[0].arg1 = data.num;
        com[0].arg2 = 0;

        strcpy(com[1].command, "rotate");
        com[1].command_tpye = 0;
        com[1].arg1 = data.num;
        com[1].arg2 = 0;

        strcpy(com[2].command, "destroy");
        com[1].command_tpye = 1;
        com[1].arg1 = data.num;
        com[1].arg2 = 0;
        data.control_flag = 0;

        return back; // 没被调度的情况
    }
    if (data.control_flag == 0)
    {
        command *com = new command[2];
        back_command *back = new back_command;
        back->command_num = 2;
        back->back_command = com;

        strcpy(com[0].command, "forward");
        com[0].command_tpye = 0;
        com[0].arg1 = data.num;
        com[0].arg2 = 0;

        strcpy(com[1].command, "rotate");
        com[1].command_tpye = 0;
        com[1].arg1 = data.num;
        com[1].arg2 = 0;

        return back; // 没被调度的情况
    }
    else
    {

        double bot_toward = 0;
        if (data.toward < 0)
            bot_toward = 2 * pai + data.toward;
        else
            bot_toward = data.toward; // 将机器人朝向转换[0,2pai]

        if (data.control_flag == 1) // 到达ori
        {
            if (data.object > 0)
            {
                data.control_flag = 0;
            }
            if (data.ori < 0 && data.des < 0)
            {
                data.control_flag = 0;
            }
            if (data.ori < 0 && data.des >= 0)
            {

                data.control_flag = 2;
            }
            double angl = 0;
            angl = atan2(now_table[data.ori].y - data.y, now_table[data.ori].x - data.x); // 计算向量方位角
            double ori_toward = 0;                                                        // 目的地的方向向量
            if (angl < 0)
                ori_toward = 2 * pai + angl; // 换算成[0,2pai]
            else
                ori_toward = angl;
            if (data.ori == data.table)
            {
                //  data.ori = -11;
                std::cerr << "\nbuy\nset_2\n";
                if (now_table[data.ori].outstats == 0)
                    data.control_flag = 0;
                else
                    data.control_flag = 2;
                std::cerr << "robot_num " << data.num << " back_flag " << data.control_flag << std::endl;
                back_command *back = new back_command;
                data.object = now_table[data.ori].type;
                command *com = new command[3];
                back->command_num = 3;
                back->back_command = com; // #
                now_table[data.ori].out_control = 0;
                strcpy(com[0].command, "buy");
                com[0].arg1 = data.num;
                com[0].command_tpye = 1;
                com[1].arg1 = data.num;
                com[1].arg2 = 0;
                com[1].command_tpye = 0;
                strcpy(com[1].command, "forward");
                com[2].arg1 = data.num;
                com[2].arg2 = speed;
                com[2].command_tpye = 0;
                strcpy(com[2].command, "rotate");
                std::cerr << "robot_num " << data.num << " back_flag " << data.control_flag << std::endl;
                return back;
            }
            else
            {
                double turn = turn_toward(bot_toward, ori_toward);
                if (turn == 0)
                {
                    back_command *back = new back_command;
                    command *com = new command[2];
                    back->back_command = com;
                    back->command_num = 2;
                    strcpy(com[0].command, "rotate");
                    com[0].arg1 = data.num;
                    com[0].arg2 = 0;
                    com[0].command_tpye = 0;
                    strcpy(com[1].command, "forward");
                    com[1].arg1 = data.num;
                    com[1].arg2 = speed;
                    com[1].command_tpye = 0;
                    return back;
                }
                if (turn < 0)
                {
                    if (abs(turn) > 0.5)
                    {
                        speed = 1; // 钝角转弯减速
                        turn_speed = 3.14;
                    }
                    if (abs(turn) < 0.5)
                    {
                        speed = 5; // 钝角转弯减速
                        turn_speed = abs(turn) + 0.2;
                    }

                    back_command *back = new back_command;
                    command *com = new command[2];
                    back->back_command = com;
                    back->command_num = 2;
                    strcpy(com[0].command, "rotate");
                    com[0].arg1 = data.num;
                    com[0].arg2 = -turn_speed;
                    com[0].command_tpye = 0;
                    strcpy(com[1].command, "forward");
                    com[1].arg1 = data.num;
                    com[1].arg2 = speed;
                    com[1].command_tpye = 0;
                    return back;
                }
                if (turn > 0)
                {
                    if (abs(turn) > 0.5)
                    {
                        speed = 1; // 钝角转弯减速
                        turn_speed = 3.14;
                    }
                    if (abs(turn) < 0.5)
                    {
                        speed = 5; // 钝角转弯减速
                        turn_speed = abs(turn) + 0.2;
                    }
                    back_command *back = new back_command;
                    command *com = new command[2];
                    back->back_command = com;
                    back->command_num = 2;
                    strcpy(com[0].command, "rotate");
                    com[0].arg1 = data.num;
                    com[0].arg2 = turn_speed;
                    com[0].command_tpye = 0;
                    strcpy(com[1].command, "forward");
                    com[1].arg1 = data.num;
                    com[1].arg2 = speed;
                    com[1].command_tpye = 0;
                    return back;
                }
            }
        }
        if (data.control_flag == 2) // 到达目的地
        {
            std::cerr << "flag=2" << std::endl;
            if (data.object == 0)
            {
                data.control_flag = 1;
            }
            double angl = 0;
            angl = atan2(now_table[data.des].y - data.y, now_table[data.des].x - data.x); // 计算向量方位角
            double des_toward = 0;                                                        // 目的地的方向向量
            if (angl < 0)
                des_toward = 2 * pai + angl;
            else
                des_toward = angl;
            // 换算成[0,2pai]
            if (data.des == data.table) // 机器人到达终点
            {
                data.des = -11;
                data.control_flag = 0;
                back_command *back = new back_command;
                command *com = new command[3];
                back->command_num = 3;
                back->back_command = com; // #

                strcpy(com[0].command, "sell");
                com[0].arg1 = data.num;
                com[0].command_tpye = 1;
                com[1].arg1 = data.num;
                com[1].arg2 = 6;
                com[1].command_tpye = 0;
                strcpy(com[1].command, "forward");
                com[2].arg1 = data.num;
                com[2].arg2 = 2;
                com[2].command_tpye = 0;
                strcpy(com[2].command, "rotate");
                return back;
            }
            else
            {

                double turn = turn_toward(bot_toward, des_toward);
                if (turn == 0)
                {

                    back_command *back = new back_command;
                    command *com = new command[2];
                    back->back_command = com;
                    back->command_num = 2;
                    strcpy(com[0].command, "rotate");
                    com[0].arg1 = data.num;
                    com[0].arg2 = 0;
                    com[0].command_tpye = 0;
                    strcpy(com[1].command, "forward");
                    com[1].arg1 = data.num;
                    com[1].arg2 = speed;
                    com[1].command_tpye = 0;
                    return back;
                }
                if (turn < 0)
                {
                    if (abs(turn) > 0.5)
                    {
                        speed = 1; // 钝角转弯减速
                        turn_speed = 3.14;
                    }
                    if (abs(turn) < 0.5)
                    {
                        speed = 5; // 钝角转弯减速
                        turn_speed = abs(turn) + 0.2;
                    }
                    back_command *back = new back_command;
                    command *com = new command[2];
                    back->back_command = com;
                    back->command_num = 2;
                    strcpy(com[0].command, "rotate");
                    com[0].arg1 = data.num;
                    com[0].arg2 = -turn_speed;
                    com[0].command_tpye = 0;
                    strcpy(com[1].command, "forward");
                    com[1].arg1 = data.num;
                    com[1].arg2 = speed;
                    com[1].command_tpye = 0;
                    return back;
                }
                if (turn > 0)
                {
                    if (abs(turn) > 0.5)
                    {
                        speed = 1; // 钝角转弯减速
                        turn_speed = 3.14;
                    }
                    if (abs(turn) < 0.5)
                    {
                        speed = 5; // 钝角转弯减速
                        turn_speed = abs(turn) + 0.2;
                    }

                    back_command *back = new back_command;
                    command *com = new command[2];
                    back->back_command = com;
                    back->command_num = 2;
                    strcpy(com[0].command, "rotate");
                    com[0].arg1 = data.num;
                    com[0].arg2 = turn_speed;
                    com[0].command_tpye = 0;
                    strcpy(com[1].command, "forward");
                    com[1].arg1 = data.num;
                    com[1].arg2 = speed;
                    com[1].command_tpye = 0;
                    return back;
                }
            }
        }
    }
};

bool robot::avoid_crash(robot bot[])
{
    std::cerr << "avoid_crash " << std::endl;
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

back_command *robot::bot_avoid_crash(robot bot[])
{
    std::cerr << "bot_avoid_crash " << std::endl;
    const int pai = 3.14159;
    back_command *back = new back_command;
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
double turn_toward(double bot_toward, double table_bot_toward)
{

    double angl = bot_toward - table_bot_toward;
    if (angl < 0.2 && angl > -0.2)
        return 0;
    if (angl > 2.5 || angl < -2.5)
        return -3;
    else
        return -angl;

    //}

} // 1表示逆时针 -1表示顺时针 0 表示不用转