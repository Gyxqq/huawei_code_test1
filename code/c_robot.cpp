
#include "c_robot.h"
#include <iostream>
#include <math.h>
#include <string.h>
#include <math.h>
double turn_toward(double bot_toward, double table_bot_toward);
double bot_table_des(robot bot, table *now_table);
back_command *robot::route_control(map1 &now_map)
{
    std::cerr << "robot:" << data.num << " control_flag " << data.control_flag << " ori" << data.ori << " des" << data.des << " type" << data.object << std::endl;
    const double pai = 3.1415926;
    table *now_table = now_map.gettable();
    int now_table_num = *now_map.gettable_num();
    int ori = data.ori;
    int des = data.des;
    double speed = 6;
    double turn_speed = 3.14;
    double min_angl = 1;

    if ((data.x < 1 || data.x > 49 || data.y < 1 || data.y > 49) && data.toward > 0.1 && data.toward < 3.13)
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
            // if (data.object > 0)
            // {
            //     data.control_flag = 0;
            // }
            // if(data.ori<0&&data.des<0){
            //     data.control_flag=0;
            // }
            // if(data.ori<0&&data.des>=0){

            //         data.control_flag=2;
            // }
            double angl = 0;
            angl = atan2(now_table[data.ori].y - data.y, now_table[data.ori].x - data.x); // 计算向量方位角
            double ori_toward = 0;                                                        // 目的地的方向向量
            if (angl < 0)
                ori_toward = 2 * pai + angl; // 换算成[0,2pai]
            else
                ori_toward = angl;
            if (data.ori == data.table)
            {

                std::cerr << "\nbuy\nset_2\n";
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
                    double des_now = bot_table_des(*this, now_table);
                    if (des_now >= 25)
                    {
                        speed = 6;
                        turn_speed = 1;
                    }
                    if (des_now < 4)
                    {
                        speed = 2;
                        turn_speed = 3;
                    }

                    if (abs(turn) > min_angl)
                    {
                        speed = 2; // 钝角转弯减速
                        turn_speed = 3;
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
                    double des_now = bot_table_des(*this, now_table);
                    if (des_now >= 9)
                    {
                        speed = 6;
                        turn_speed = 1;
                    }
                    if (des_now < 4)
                    {
                        speed = 2;
                        turn_speed = 3;
                    }
                    if (abs(turn) > min_angl)
                    {
                        speed = 2; // 钝角转弯减速
                        turn_speed = 3;
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
            if (data.object <= 0 && data.get > 3)
                data.control_flag = 0;
            if (data.object <= 0 && data.get <= 3)
                data.control_flag = 1;
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
                    double des_now = bot_table_des(*this, now_table);
                    if (des_now >= 9)
                    {
                        speed = 6;
                        turn_speed = 1;
                    }
                    if (des_now < 4)
                    {
                        speed = 2;
                        turn_speed = 3;
                    }
                    if (abs(turn) > min_angl)
                    {
                        speed = 2; // 钝角转弯减速
                        turn_speed = 3;
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
                    double des_now = bot_table_des(*this, now_table);
                    if (des_now >= 9)
                    {
                        speed = 6;
                        turn_speed = 1;
                    }
                    if (des_now < 4)
                    {
                        speed = 2;
                        turn_speed = 3;
                    }
                    if (abs(turn) > min_angl)
                    {
                        speed = 2; // 钝角转弯减速
                        turn_speed = 3;
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
    double next_x, next_y;
    next_x = data.x;
    next_y = data.y;
    int flag = 0;
    double angl1 = data.toward < 0 ? 2 * 3.1416 - data.toward : data.toward;

    for (int i = 0; i < 4; i++)
    {
        if (i == data.num)
            continue;
        double x = bot[i].data.x;
        double y = bot[i].data.y;
        double angl2 = bot[i].data.toward < 0 ? 2 * 3.1416 - bot[i].data.toward : bot[i].data.toward;
        double angl3 = angl1 - angl2 < 0 ? 2 * 3.1416 - (angl1 - angl2) : angl1 - angl2;
        if (angl3 < 3.5 && angl3 > 2.8)
        {
            if (pow(next_x - x, 2) + pow(next_y - y, 2) < 0.4)
            {
                std::cerr << "\ncrash\n";
                flag = 1;
                data.rest_crash = 40;
                break;
            }
        }
    }
    return flag;
}

back_command *robot::bot_avoid_crash(robot bot[])
{
    data.rest_crash--;
    const int pai = 3.14;
    back_command *back = new back_command;
    back->back_command = new command[2];
    if (data.rest_crash > 30)
    {
        back->command_num = 2;
        back->back_command[0].command_tpye = 0;
        strcpy(back->back_command[0].command, "forward");
        back->back_command[0].arg1 = data.num;
        back->back_command[0].arg2 = -2;
        strcpy(back->back_command[1].command, "rotate");
        back->back_command[1].arg1 = data.num;
        back->back_command[1].arg2 = 0;
    }

    if (data.rest_crash <= 30)
    {
        back->command_num = 2;
        back->back_command[0].command_tpye = 0;
        strcpy(back->back_command[0].command, "forward");
        back->back_command[0].arg1 = data.num;
        back->back_command[0].arg2 = 0;
        strcpy(back->back_command[1].command, "rotate");
        back->back_command[1].arg1 = data.num;
        back->back_command[1].arg2 = pai;
    }

    // if (abs(data.toward) > 0.5 * 3.14159)
    // {
    //     if (data.toward > 0)
    //         back->back_command[1].arg2 = -pai;
    //     else
    // back->back_command[1].arg2 = pai;
    // }
    // else
    // {
    //     if (data.toward > 0)
    //         back->back_command[1].arg2 = pai;
    //         else  back->back_command[1].arg2 = -pai;
    // }

    return back;
}
double turn_toward(double bot_toward, double table_bot_toward)
{

    double angl = bot_toward - table_bot_toward;
    if (angl <= 0)
        angl = 2 * 3.142 + angl;
    // if(angl<0.1||angl>2*3.14)return 0;
    if (angl < 0.2 || angl > 2 * 3.14159 - 0.2)
        return 0;
    if (angl > 3.14159)
        return 2 * 3.15 - angl;
    else
        return -angl;

    //}

} // 1表示逆时针 -1表示顺时针 0 表示不用转
double bot_table_des(robot bot, table *now_table)
{

    if (bot.data.control_flag == 1)
    {

        return abs(pow(bot.data.x - now_table[bot.data.ori].x, 2) + pow(bot.data.y - now_table[bot.data.ori].y, 2));
    }
    else
        return abs(pow(bot.data.x - now_table[bot.data.des].x, 2) + pow(bot.data.y - now_table[bot.data.des].y, 2));
}