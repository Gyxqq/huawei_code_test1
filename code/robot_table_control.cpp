#include "data_struct.h"
#include "function.h"
#include <algorithm>
#include <math.h>
#include <string.h>
bool sort2(bot_control_command a, bot_control_command b);
bool sort1(bot_control_command a, bot_control_command b);
inline int find_near_bot(table &this_table, robot bot[]);

int refind_des(table *tab_now, int obj_type, int table_num);
inline int find_near_table(table *tab, int table_num, int now_table, int object_type);
bool robot_table_control(map &now_map, robot now_bot[])
{

    table *now_table = now_map.gettable();
    int table_num_now = *now_map.gettable_num();
    int possible_command = 4;
    bot_control_command *com = new bot_control_command[4];
    for (int i = 0; i < 4; i++)
    {

    } // 机器人状态纠正
    for (int i = 0; i < 4; i++)
    {
        com[i].robot_num = i;
        com[i].hash = -1; // 初始化机器人
    }
    for (int i = 0; i < table_num_now; i++) // 工作台编号
    {

        for (int i2 = 1; i2 < 8; i2++) // 需要的物品
        {

            if (now_table[i].instats[i2] == 0 && now_table[i].bot_inttats[i2] == 1)
            {
                int flag_1 = 0;
                for (int i4 = 0; i4 < 4; i4++) // 确保一个原料槽由一个机器人提供
                {

                    if (now_bot[i4].data.control_flag != 0 && now_bot[i4].data.des == i && now_bot[i4].data.get == i2)
                    {
                        flag_1 = 1;
                    }
                }
                // 如果flag=1，则说明有机器人提供了这个原料
                if (flag_1 == 1)
                    continue;                              // 该原料不需要输入
                for (int i3 = 0; i3 < table_num_now; i3++) // 遍历找到能提供物品的工作台
                {
                    int flag_2=0;
                    if (i3 == i)
                        continue;

                    if (now_table[i3].type == i2)
                    { // 有原料产出匹配
                        if (now_table[i3].outstats == 0)
                            continue; // 判断产品槽有无产品
                        if (now_table[i3].out_control == 0)
                        { // 产出是否被分配

                            for (int i4 = 0; i4 < 4; i4++)
                            { // 寻找机器人

                                if (now_bot[i4].data.control_flag != 0) // 确保机器人未被调度
                                    continue;
                                double hash = value_hash(now_map, now_bot[i4], i, i3);
                                if (hash > com[i4].hash)
                                {
                                    com[i4].des = i;
                                    com[i4].ori = i3;
                                    com[i4].hash = hash; // 完成命令生成
                                    com[i4].type = i2;
                                    flag_2=1;
                                    break;
                                }
                            }
                        }
                    }
                    if(flag_2==1)break;
                }
            }
        }
    }
    for (int i = 0; i < 4; i++)
    {

        if (com[i].hash < 0)
            continue;
        now_bot[i].data.control_flag = 1;
        now_table[com[i].ori].out_control = 1;
        now_bot[i].data.des = com[i].des;
        now_bot[i].data.ori = com[i].ori;
        now_bot[i].data.get = com[i].type; // 调度执行
        
    }
}
