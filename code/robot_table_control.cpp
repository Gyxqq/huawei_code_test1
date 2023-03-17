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
    std::cerr << "robot_table_control " << std::endl;
    table *table_now = now_map.gettable();
    int table_num_now = *now_map.gettable_num();
    std::cerr << "table_num_now" << table_num_now << std::endl;
    bot_control_command *final_bot_control = new bot_control_command[4]; // 存放机器人调度指令n
    for (int i = 0; i < 4; i++)
    {
        if (now_bot[i].data.control_flag == 0 && now_bot[i].data.object != 0)
        {
            int flag_1 = refind_des(table_now, now_bot[i].data.object, table_num_now);
            if (flag_1 == -1)
                continue;
            else
            {
                std::cerr << "bot_reset " << i << " table num " << flag_1 << " table_type " << table_now[flag_1].type << std::endl;
                now_bot[i].data.des = flag_1;
                now_bot[i].data.control_flag = 2; // 机器人重新调度
            }
        }
    }
    if (now_bot[0].data.control_flag > 0 && now_bot[1].data.control_flag > 0 && now_bot[2].data.control_flag > 0 && now_bot[3].data.control_flag > 0)
    {
        std::cerr << "gyx1 ";
        return 0; // 无机器人空闲返回0
    }

    else
    {
        std::cerr << "go1 ";
        int command_num = table_num_now * 2 + 7; // 可能的指令数目
        bot_control_command *now_command = new bot_control_command[command_num];
        int command_count = 0; // 目前指令数
        for (int i = 0; i < table_num_now; i++)
        {
            std::cerr << "& ";
            if (table_now[i].type == 1 || table_now[i].type == 2 || table_now[i].type == 3)
                continue; // 判断工作台是不是123号仅生产的工作台
            if (table_now[i].rest == 0)
                continue; // 判断工作台所否处于阻塞状态
            if (table_now[i].type == 4)
            {
                if (!table_now[i].instats[1]) // 判断相应原料槽有无原料
                {
                    int table1 = find_near_table(table_now, table_num_now, i, 1);

                    if (table1 != -1)
                    {
                        int flag = 0;
                        for (int i2 = 0; i2 < 4; i2++)
                        {
                            if (now_bot[i2].data.ori == table1)
                                flag = 1; // 判断该任务是否已被分配
                        }
                        if (flag == 1)
                            continue;

                        int bot_num1 = find_near_bot(table_now[i], now_bot);
                        now_command[command_count].ori = table1;
                        now_command[command_count].des = i;
                        now_command[command_count].robot_num = bot_num1;
                        now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table1);
                        command_count++;
                    }
                }
                if (!table_now[i].instats[2])
                {
                    int table2 = find_near_table(table_now, table_num_now, i, 2);
                    if (table2 != -1)
                    {
                        int flag = 0;
                        for (int i2 = 0; i2 < 4; i2++)
                        {
                            if (now_bot[i2].data.des == table2)
                                flag = 1; // 判断该任务是否已被分配
                        }
                        if (flag == 1)
                            continue;

                        int bot_num2 = find_near_bot(table_now[i], now_bot);
                        now_command[command_count].ori = table2;
                        now_command[command_count].des = i;
                        now_command[command_count].robot_num = bot_num2;
                        now_command[command_count].hash = value_hash(now_map, now_bot[bot_num2], i, table2);
                        command_count++;
                    }
                }
            }

            if (table_now[i].type == 5)
            {
                if (!table_now[i].instats[1])
                {
                    int table1 = find_near_table(table_now, table_num_now, i, 1);
                    if (table1 != -1)
                    {

                        int flag = 0;
                        for (int i2 = 0; i2 < 4; i2++)
                        {
                            if (now_bot[i2].data.ori == table1)
                                flag = 1; // 判断该任务是否已被分配
                        }
                        if (flag == 1)
                            continue;
                        int bot_num1 = find_near_bot(table_now[i], now_bot);
                        now_command[command_count].ori = table1;
                        now_command[command_count].des = i;
                        now_command[command_count].robot_num = bot_num1;
                        now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table1);
                        command_count++;
                    }
                }
                if (!table_now[i].instats[3])
                {
                    int table2 = find_near_table(table_now, table_num_now, i, 3);
                    if (table2 != -1)
                    {

                        int flag = 0;
                        for (int i2 = 0; i2 < 4; i2++)
                        {
                            if (now_bot[i2].data.des == table2)
                                flag = 1; // 判断该任务是否已被分配
                        }
                        if (flag == 1)
                            continue;
                        int bot_num2 = find_near_bot(table_now[i], now_bot);
                        now_command[command_count].ori = table2;
                        now_command[command_count].des = i;
                        now_command[command_count].robot_num = bot_num2;
                        now_command[command_count].hash = value_hash(now_map, now_bot[bot_num2], i, table2);
                        command_count++;
                    }
                }
            }

            if (table_now[i].type == 6)
            {
                if (!table_now[i].instats[2])
                {
                    int table1 = find_near_table(table_now, table_num_now, i, 2);
                    if (table1 != -1)
                    {
                        int flag = 0;
                        for (int i2 = 0; i2 < 4; i2++)
                        {
                            if (now_bot[i2].data.ori == table1)
                                flag = 1; // 判断该任务是否已被分配
                        }
                        if (flag == 1)
                            continue;

                        int bot_num1 = find_near_bot(table_now[i], now_bot);
                        now_command[command_count].ori = table1;
                        now_command[command_count].des = i;
                        now_command[command_count].robot_num = bot_num1;
                        now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table1);
                        command_count++;
                    }
                }
                if (!table_now[i].instats[3])
                {
                    int table2 = find_near_table(table_now, table_num_now, i, 3);
                    if (table2 != -1)
                    {
                        int flag = 0;
                        for (int i2 = 0; i2 < 4; i2++)
                        {
                            if (now_bot[i2].data.des == table2)
                                flag = 1; // 判断该任务是否已被分配
                        }
                        if (flag == 1)
                            continue;

                        int bot_num2 = find_near_bot(table_now[i], now_bot);
                        now_command[command_count].ori = table2;
                        now_command[command_count].des = i;
                        now_command[command_count].robot_num = bot_num2;
                        now_command[command_count].hash = value_hash(now_map, now_bot[bot_num2], i, table2);
                        command_count++;
                    }
                }
            }

            if (table_now[i].type == 7)
            {
                if (!table_now[i].instats[4])
                {
                    int table1 = find_near_table(table_now, table_num_now, i, 4);
                    if (table1 != -1)
                    {
                        int flag = 0;
                        for (int i2 = 0; i2 < 4; i2++)
                        {
                            if (now_bot[i2].data.ori == table1)
                                flag = 1; // 判断该任务是否已被分配
                        }
                        if (flag == 1)
                            continue;

                        int bot_num1 = find_near_bot(table_now[i], now_bot);
                        now_command[command_count].ori = table1;
                        now_command[command_count].des = i;
                        now_command[command_count].robot_num = bot_num1;
                        now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table1);
                        command_count++;
                    }
                }
                if (!table_now[i].instats[5])
                {
                    int table2 = find_near_table(table_now, table_num_now, i, 5);
                    if (table2 != -1)
                    {

                        int flag = 0;
                        for (int i2 = 0; i2 < 4; i2++)
                        {
                            if (now_bot[i2].data.des == table2)
                                flag = 1; // 判断该任务是否已被分配
                        }
                        if (flag == 1)
                            continue;
                        int bot_num2 = find_near_bot(table_now[i], now_bot);
                        now_command[command_count].ori = table2;
                        now_command[command_count].des = i;
                        now_command[command_count].robot_num = bot_num2;
                        now_command[command_count].hash = value_hash(now_map, now_bot[bot_num2], i, table2);
                        command_count++;
                    }
                }
                if (!table_now[i].instats[6])
                {
                    int table3 = find_near_table(table_now, table_num_now, i, 6);
                    if (table3 != -1)
                    {
                        int flag = 0;
                        for (int i2 = 0; i2 < 4; i2++)
                        {
                            if (now_bot[i2].data.des == table3)
                                flag = 1; // 判断该任务是否已被分配
                        }
                        if (flag == 1)
                            continue;

                        int bot_num3 = find_near_bot(table_now[i], now_bot);
                        now_command[command_count].ori = table3;
                        now_command[command_count].des = i;
                        now_command[command_count].robot_num = bot_num3;
                        now_command[command_count].hash = value_hash(now_map, now_bot[bot_num3], i, table3);
                        command_count++;
                    }
                }
            }

            if (table_now[i].type == 8)
            {
                if (!table_now[i].instats[7])
                {
                    int table1 = find_near_table(table_now, table_num_now, i, 7);
                    if (table1 != -1)
                    {
                        int flag = 0;
                        for (int i2 = 0; i2 < 4; i2++)
                        {
                            if (now_bot[i2].data.ori == table1)
                                flag = 1; // 判断该任务是否已被分配
                        }
                        if (flag == 1)
                            continue;

                        int bot_num1 = find_near_bot(table_now[i], now_bot);
                        now_command[command_count].ori = table1;
                        now_command[command_count].des = i;
                        now_command[command_count].robot_num = bot_num1;
                        now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table1);
                        command_count++;
                    }
                }
            }
            if (table_now[i].type == 9)
            {
                int table1 = find_near_table(table_now, table_num_now, i, 1);
                if (table1 != -1)
                {
                    int flag = 0;
                    for (int i2 = 0; i2 < 4; i2++)
                    {
                        if (now_bot[i2].data.ori == table1)
                            flag = 1; // 判断该任务是否已被分配
                    }
                    if (flag == 1)
                        continue;
                    int bot_num1 = find_near_bot(table_now[i], now_bot);
                    now_command[command_count].ori = table1;
                    now_command[command_count].des = i;
                    now_command[command_count].robot_num = bot_num1;
                    now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table1);
                    command_count++;
                }
                int table2 = find_near_table(table_now, table_num_now, i, 2);
                if (table2 != -1)
                {
                    int flag = 0;
                    for (int i2 = 0; i2 < 4; i2++)
                    {
                        if (now_bot[i2].data.ori == table1)
                            flag = 1; // 判断该任务是否已被分配
                    }
                    if (flag == 1)
                        continue;
                    int bot_num1 = find_near_bot(table_now[i], now_bot);
                    now_command[command_count].ori = table2;
                    now_command[command_count].des = i;
                    now_command[command_count].robot_num = bot_num1;
                    now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table2);
                    command_count++;
                }
                int table3 = find_near_table(table_now, table_num_now, i, 3);
                if (table3 != -1)
                {
                    int flag = 0;
                    for (int i2 = 0; i2 < 4; i2++)
                    {
                        if (now_bot[i2].data.ori == table1)
                            flag = 1; // 判断该任务是否已被分配
                    }
                    if (flag == 1)
                        continue;
                    int bot_num1 = find_near_bot(table_now[i], now_bot);
                    now_command[command_count].ori = table3;
                    now_command[command_count].des = i;
                    now_command[command_count].robot_num = bot_num1;
                    now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table3);
                    command_count++;
                }
                int table4 = find_near_table(table_now, table_num_now, i, 4);
                if (table4 != -1)
                {
                    int flag = 0;
                    for (int i2 = 0; i2 < 4; i2++)
                    {
                        if (now_bot[i2].data.ori == table1)
                            flag = 1; // 判断该任务是否已被分配
                    }
                    if (flag == 1)
                        continue;
                    int bot_num1 = find_near_bot(table_now[i], now_bot);
                    now_command[command_count].ori = table4;
                    now_command[command_count].des = i;
                    now_command[command_count].robot_num = bot_num1;
                    now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table4);
                    command_count++;
                }
                int table5 = find_near_table(table_now, table_num_now, i, 5);
                if (table5 != -1)
                {
                    int flag = 0;
                    for (int i2 = 0; i2 < 4; i2++)
                    {
                        if (now_bot[i2].data.ori == table1)
                            flag = 1; // 判断该任务是否已被分配
                    }
                    if (flag == 1)
                        continue;
                    int bot_num1 = find_near_bot(table_now[i], now_bot);
                    now_command[command_count].ori = table5;
                    now_command[command_count].des = i;
                    now_command[command_count].robot_num = bot_num1;
                    now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table5);
                    command_count++;
                }
                int table6 = find_near_table(table_now, table_num_now, i, 6);
                if (table6 != -1)
                {
                    int flag = 0;
                    for (int i2 = 0; i2 < 4; i2++)
                    {
                        if (now_bot[i2].data.ori == table1)
                            flag = 1; // 判断该任务是否已被分配
                    }
                    if (flag == 1)
                        continue;
                    int bot_num1 = find_near_bot(table_now[i], now_bot);
                    now_command[command_count].ori = table6;
                    now_command[command_count].des = i;
                    now_command[command_count].robot_num = bot_num1;
                    now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table6);
                    command_count++;
                }
                int table7 = find_near_table(table_now, table_num_now, i, 7);
                if (table7 != -1)
                {
                    int flag = 0;
                    for (int i2 = 0; i2 < 4; i2++)
                    {
                        if (now_bot[i2].data.ori == table1)
                            flag = 1; // 判断该任务是否已被分配
                    }
                    if (flag == 1)
                        continue;
                    int bot_num1 = find_near_bot(table_now[i], now_bot);
                    now_command[command_count].ori = table7;
                    now_command[command_count].des = i;
                    now_command[command_count].robot_num = bot_num1;
                    now_command[command_count].hash = value_hash(now_map, now_bot[bot_num1], i, table7);
                    command_count++;
                }
            }
        }
        // 生成调度指令
        std::cerr << "command_num= " << command_count << std::endl;
        if (command_count == 0)
            return 0;
        std::sort(now_command, now_command + command_count, sort1);
        std::sort(now_command, now_command + command_count, sort2); // 排序
        int now = -1;

        for (int i = 0; i < command_count; i++)
        {
            if (now_command[i].robot_num > now)
            {

                if (table_now[now_command[i].ori].out_control == 1)
                    continue;
                if (now_bot[now_command[i].robot_num].data.control_flag > 0)
                    continue;
                now = now_command[i].robot_num;
                now_bot[now_command[i].robot_num].data.ori = now_command[i].ori; // 设定起始地
                now_bot[now_command[i].robot_num].data.des = now_command[i].des; // 设定目的地
                now_bot[now_command[i].robot_num].data.control_flag = 1;         // 将机器人切换为正在接受调度的状态
                if (table_now[now_command[i].ori].type != 1 && table_now[now_command[i].ori].type != 2 && table_now[now_command[i].ori].type != 3)
                    table_now[now_command[i].ori].out_control = 1; // 工作台的输出切换为已接受调度
                std::cerr << "robot_control " << now << " " << now_command[i].ori << " " << now_command[i].des << std::endl;
            }
        }
        std::cerr << "robot_table_control_over" << std::endl;
        delete[] now_command;
        return 1;
    }
}

inline int find_near_bot(table &this_table, robot bot[])
{
    int num = -1;
    double des = 10000;
    for (int i = 0; i < 4; i++)
    {

        if (bot[i].data.control_flag > 0) // 判断机器人所否被调度
            continue;
        else
        {
            double now_des = pow(this_table.x - bot[i].data.x, 2) + pow(this_table.y - bot[i].data.y, 2); // 计算距离
            if (now_des < des)
            {
                num = i;
                des = now_des;
            }
        }
    }
    return num; // 返回最近机器人的编号
}

inline int find_near_table(table *tab, int table_num, int now_table, int object_type)
{
    int num = -1;
    double des = 50000;
    for (int i = 0; i < table_num; i++)
    {

        if (i == now_table) // 判断是否是当前工作台
            continue;
        if (tab[i].type != object_type) // 判断产物的类型是否和请求类型相同
            continue;
        if (tab[i].out_control == 1) // 判断产物是否已被调度
            continue;
        if (tab[i].outstats == 0) // 判断输出格所否有产物
            continue;
        double now_des = pow(tab[now_table].x - tab[i].x, 2) + pow(tab[now_table].y - tab[i].y, 2); // 计算距离
        if (now_des <= des)
        {
            num = i;
            des = now_des;
        }
    }
    std::cerr << "now_table " << now_table << "now_table_type=" << tab[now_table].type << " table_found " << num << "goto_table_type " << tab[num].type << std::endl;
    return num; // 返回最近的有所请求物品的工作台的编号
}

bool sort1(bot_control_command a, bot_control_command b)
{
    return a.robot_num < b.robot_num;
}
bool sort2(bot_control_command a, bot_control_command b)
{
    return a.robot_num <= b.robot_num && a.hash > b.hash; // 排序
}
// bool sort3(bot_control_command a, bot_control_command b,table tab[]){
//     return a.robot_num <= b.robot_num &&tab[a.des].type>=tab[b.des].type;
// }
bool sort_1(table a, table b)
{
    return a.type > b.type;
}

int refind_des(table *tab_now, int obj_type, int table_num)
{

    int i2 = -1;
    table *tab = new table[table_num];
    memcpy(tab, tab_now, table_num * sizeof(table));
    std::sort(tab, tab + table_num, sort_1);
    for (i2 = 0; i2 < table_num; i2++)
    {

        if (tab[i2].type == 9)
        {
            if (tab[i2].instats[obj_type] == 0)
            {
                break;
            }
        }
        if (tab[i2].type == 8)
        {
            if (obj_type == 7 && tab[i2].instats[7] == 0)
            {
                break;
            }
        }
        if (tab[i2].type == 7)
        {

            if (obj_type == 6 && tab[i2].instats[6] == 0)
            {
                break;
            }
            if (obj_type == 5 && tab[i2].instats[5] == 0)
            {
                break;
            }
            if (obj_type == 4 && tab[i2].instats[4] == 0)
            {
                break;
            }
        }
        if (tab[i2].type == 6)
        {
            if (obj_type == 3 && tab[i2].instats[3] == 0)
            {
                break;
            }
            if (obj_type == 2 && tab[i2].instats[2] == 0)
            {
                break;
            }
        }
        if (tab[i2].type == 5)
        {
            if (obj_type == 3 && tab[i2].instats[3] == 0)
            {
                break;
            }
            if (obj_type == 1 && tab[i2].instats[1] == 0)
            {
                break;
            }
        }
        if (tab[i2].type == 4)
        {
            if (obj_type == 2 && tab[i2].instats[2] == 0)
            {
                break;
            }
            if (obj_type == 1 && tab[i2].instats[1] == 0)
            {
                break;
            }
        }
        if (i2 == table_num - 1)
        {
            i2 = -1;
            break;
        }
    }
    i2 = tab[i2].num;
    delete[] tab;
    return i2;
}
