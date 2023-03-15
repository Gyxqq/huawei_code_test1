#include"data_struct.h"
#include"c_map.h"
bool input(int& now_frame, int& now_money, table* table_in_map, int* table_num, robot* robot_in_map);
// 分别储存当前帧，当前资金，工作台数组，工作台数量，机器人数组，从标准输入读取数据并存放到对应位置

bool output(output_command* out_put_command); // 对储存的需要输出的数据进行输出

int value_hash(map now_map, robot now_bot, int ori, int des);
// 规划方案哈希值计算，哈希值越大规划方案的利润越大

bool robot_table_control(map& now_map, robot now_bot[]); // 对未接受调度的机器人进行调度，方式为在函数中对机器人的control_flag,ori和des进行设置,生成调度方案并利用value_hash选择最优方案
// 可以利用bot_control_command结构体储存调度指令（建议）

output_command* output_process(back_command com[], int frame);

bool process_control(map& now_map, robot now_bot[]);
/*
流程控制
在流程中调用input,robot_table_control,robot.route_control,output_process,output函数完成机器人控制
*/