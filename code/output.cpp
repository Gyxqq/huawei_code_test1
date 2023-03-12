/*
实现数据输出（不包括数据处理及初始化的OK）
输出完成后会释放out_command的内存
*/
#include"data_struct.h"
#include<iostream>
bool output(output_command* out_put_command)
{
    const int num=out_put_command->command_num;//num暂存输出命令数
    //输出当前帧数
    std::cout<<out_put_command->frame<<std::endl;
    //输出控制小车的命令
    for(int i=0;i<num;i++)
    {
        std::cout << out_put_command->out_command[i].command << " "
     << out_put_command->out_command[i].arg1 << " "
     << out_put_command->out_command[i].arg2 << std::endl;

    }
    std::cout<<"OK";
    delete[] out_put_command->out_command;
    return 1;
}