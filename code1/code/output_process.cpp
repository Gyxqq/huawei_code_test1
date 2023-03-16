#include "data_struct.h"
#include <string.h>
#include <iostream>
output_command *output_process(back_command com[], int frame)
{
    std::cerr << "output_process" << std::endl;
    int all_num = 0;
    for (int i = 0; i < 4; i++)
    {
        all_num += com[i].command_num; // 计算命令数量
    }
    std::cerr << "all_num " << all_num << std::endl;
    output_command *this_out = new output_command; // 申请返回命令的空间
    this_out->out_command = new command[all_num];  // 申请命令存放空间
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int i2 = 0; i2 < com[i].command_num; i2++)
        {
            memcpy(&this_out->out_command[count], &com[i].back_command[i2], sizeof(command));
            count++;
        }
    }
    // memcpy(this_out->out_command, com, sizeof(com)); // 命令复制
    this_out->command_num = all_num;
    this_out->frame = frame;
    return this_out;
}