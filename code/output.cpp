#include"data_struct.h"
#include<iostream>
bool output(output_command* out_put_command)
{
    std::cerr<<"output"<<std::endl<<"\n\n\n\n";
   int num = out_put_command->command_num; // num暂存输出命令数
    // 输出当前帧数
    std::cout << out_put_command->frame << std::endl;
    std::cerr <<"out_frame= " <<out_put_command->frame << std::endl;
    // 输出控制小车的命令
    for (int i = 0; i < num; i++)
    {
        std::cout << out_put_command->out_command[i].command << " "

            << out_put_command->out_command[i].arg1 << " ";
            if(out_put_command->out_command[i].command_tpye==0)std::cout<< out_put_command->out_command[i].arg2;
            std::cout<< std::endl;

            std::cerr << out_put_command->out_command[i].command << " "
        
            << out_put_command->out_command[i].arg1 << " "
            << out_put_command->out_command[i].arg2 << std::endl;
    }
    std::cout << "OK"<<std::endl;
    std::cerr << "OK"<<std::endl;

    delete[] out_put_command->out_command;
        std::cerr<<"output_over"<<std::endl;
    return 1;
}