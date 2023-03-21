#include "data_struct.h"
#include "function.h"
#include <algorithm>
#include <math.h>
#include <string.h>
double go_time1(map now_map, robot now_bot, int ori, int des);
bool robot_table_control(map &now_map, robot now_bot[], int now_frame)
{

    table *now_table = now_map.gettable();
    int table_num_now = *now_map.gettable_num();
    int possible_command = 4;
    bot_control_command *com = new bot_control_command[4];
    srand(time(NULL));
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

                    if (now_bot[i4].data.control_flag != 0 && now_bot[i4].data.des == i && now_bot[i4].data.get == i2 && now_table[now_bot[i4].data.des].type != 8 && now_table[now_bot[i4].data.des].type != 9)
                    {
                        flag_1 = 1;
                    }
                }
                // 如果flag=1，则说明有机器人提供了这个原料
                if (flag_1 == 1)
                    continue;                              // 该原料不需要输入
                for (int i3 = 0; i3 < table_num_now; i3++) // 遍历找到能提供物品的工作台
                {
                    int flag_2 = 0;
                    if (i3 == i)
                        continue;

                    if (now_table[i3].type == i2)
                    {                                    // 有原料产出匹配
                        if (now_table[i3].outstats == 1) // 判断产品槽有无产品
                        {
                            if (now_table[i3].out_control == 0 || (now_table[i3].type <= 3 && now_table[i3].rest < 40))
                            { // 产出是否被分配
                                for (int i4 = 0; i4 < 4; i4++)
                                { // 寻找机器人

                                    if (now_bot[i4].data.control_flag != 0) // 确保机器人未被调度
                                        continue;
                                    std::cerr << "gyx_con "
                                              << " ori " << i3 << " type " << now_table[i3].type << " des " << i << std::endl;
                                    double hash = value_hash(now_map, now_bot[i4], i3, i, now_frame);
                                    if (hash > com[i4].hash)
                                    {
                                        com[i4].des = i;
                                        com[i4].ori = i3;
                                        com[i4].hash = hash; // 完成命令生成
                                        com[i4].type = i2;
                                        flag_2 = 1;
                                        break;
                                    }
                                }
                            }
                        }
                        if (now_table[i3].outstats == 0 && now_table[i3].rest > 0&&now_frame<8000)
                        {
                            if (now_table[i3].out_control == 0)
                            {
                                for (int i4 = 0; i4 < 4; i4++)
                                { // 寻找机器人

                                    if (now_bot[i4].data.control_flag != 0) // 确保机器人未被调度
                                        continue;
                                    if (go_time1(now_map, now_bot[i4], i3, i) * 10 < now_table[i3].rest)
                                        continue;
                                    double hash = value_hash(now_map, now_bot[i4], i3, i, now_frame);
                                    if (hash > com[i4].hash)
                                    {
                                        com[i4].des = i;
                                        com[i4].ori = i3;
                                        com[i4].hash = hash; // 完成命令生成
                                        com[i4].type = i2;
                                        flag_2 = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    if (flag_2 == 1) // 跳出多重循环
                        break;
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
    for (int i = 0; i < 4; i++)
    {
        if (now_frame > 8800 && now_bot[i].data.control_flag == 0)
        {
            now_bot[i].data.control_flag = 2;
            now_bot[i].data.des = rand() % table_num_now;
        }
    } // 机器人状态纠正
}
double go_time1(map now_map, robot now_bot, int ori, int des)
{
    table *tab = now_map.gettable();
    double des1 = pow(tab[ori].x - now_bot.data.x, 2) + pow(tab[ori].y - now_bot.data.y, 2);
    double des2 = pow(tab[ori].x - tab[des].x, 2) + pow(tab[ori].y - tab[des].y, 2);
    double time = (sqrt(des1) + sqrt(des2)) / 10;
    return time;
}