#include "data_struct.h"
#include "c_map.h"
#include "c_robot.h"
#include "output_process.cpp"
#include "output.cpp"
#include "input.cpp"
#include "robot_table_control.cpp"
#include "function.h"
#include <string.h>
bool process_control(map &now_map, robot now_bot[])
{
    while (1)
    {
        int frame = 0;
        int money = 0;
        input(frame, money, now_map.gettable(), now_map.gettable_num(), now_bot); // 输入
        robot_table_control(now_map, now_bot);                                    // 机器人调度
        back_command *this_back_command = new back_command[4];                    // 为输出命令申请空间
        for (int i = 0; i < 4; i++)
        {
            back_command *com = now_bot[i].route_control(now_map);
            memcpy(this_back_command + i * sizeof(back_command), com, sizeof(back_command)); // 复制命令
        }
        output_command *this_output = output_process(this_back_command, frame);
        output(this_output);
    }
}