#include "c_map.h"

bool map::mapinit(robot bot[])
{
    char map[100][100] = {};
    int count_bot = 0;
    int count_table = 0;
    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            std::cin >> map[y][x];
            if (map[y][x] == 'A')
            {
                bot[count_bot].data.x = x;
                bot[count_bot].data.y = y; // 机器人位置数据储存
                bot[count_bot].data.control_flag = 0;
                bot[count_bot].data.num = count_bot;

                count_bot++;
            }
            if (map[y][x] <= '9' && map[y][x] >= '0')
            {

                count_table++; // 工作台计数
            }
        }
    } // 数据读入
    table_num = count_table;
    std::cerr << "tablenum=" << table_num << std::endl;
    table_in_map = new table[table_num]; // 申请工作台数组储存空间
    count_table = 0;
    for (int y = 0; y < 50; y++)
    {
        for (int x = 0; x < 50; x++)
        {
            if (map[y][x] <= '9' && map[y][x] >= '0')
            {
                table_in_map[count_table].type = map[y][x] - '0';
                table_in_map[count_table].num = count_table;
                table_in_map[count_table].x = x;
                table_in_map[count_table].y = y;
                table_in_map[count_table].outstats = 0;
                for (int i1 = 0; i1 < 8; i1++)
                {
                    table_in_map[count_table].instats[i1] = 0;
                } // 初始化工作台
                count_table++;
            }
        }
    }
    char ok[4];
    std::cin >> ok;
    std::cout << "OK" << std::endl;
    return 1;
};
table *map::gettable()
{

    return table_in_map;
};
int *map::gettable_num()
{
    return &table_num;
};
