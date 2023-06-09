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
                bot[count_bot].data.object = 0;
                bot[count_bot].data.get = 0;
                bot[count_bot].data.rest_crash = 0;
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
    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            if (map[y][x] <= '9' && map[y][x] >= '0')
            {
                table_in_map[count_table].usable = 1;
                table_in_map[count_table].type = map[y][x] - '0';
                table_in_map[count_table].num = count_table;
                table_in_map[count_table].x = 0.25 + 0.5 * x;
                table_in_map[count_table].y = 0.25 + 0.5 * y;
                table_in_map[count_table].outstats = 0;
                table_in_map[count_table].out_control = 0;
                for (int i2 = 0; i2 < 8; i2++)
                    table_in_map[count_table].bot_inttats[i2] = 0;
                if (table_in_map[count_table].type == 9)
                {
                    for (int i2 = 0; i2 < 8; i2++)
                        table_in_map[count_table].bot_inttats[i2] = 1;
                }
                if (table_in_map[count_table].type == 8)
                {

                    table_in_map[count_table].bot_inttats[7] = 1;
                }
                if (table_in_map[count_table].type == 7)
                {

                    table_in_map[count_table].bot_inttats[6] = 1;
                    table_in_map[count_table].bot_inttats[5] = 1;
                    table_in_map[count_table].bot_inttats[4] = 1;
                }
                if (table_in_map[count_table].type == 6)
                {

                    table_in_map[count_table].bot_inttats[3] = 1;
                    table_in_map[count_table].bot_inttats[2] = 1;
                }
                if (table_in_map[count_table].type == 5)
                {

                    table_in_map[count_table].bot_inttats[3] = 1;
                    table_in_map[count_table].bot_inttats[1] = 1;
                }
                if (table_in_map[count_table].type == 4)
                {

                    table_in_map[count_table].bot_inttats[2] = 1;
                    table_in_map[count_table].bot_inttats[1] = 1;
                }
                for (int i1 = 0; i1 < 8; i1++)
                {
                    table_in_map[count_table].instats[i1] = 0;
                } // 初始化工作台
                count_table++;
            }
        }
    }
    if(table_num==43)
    {
        for(int i=1;i<=40;i++)
        {
            table_in_map[i].usable=0;
        }
        table_in_map[13].usable=1;
        table_in_map[10].usable=1;
        table_in_map[16].usable=1;
        table_in_map[20].usable=1;
        //table_in_map[21].usable=1;
        table_in_map[23].usable=1;
        table_in_map[31].usable=1;
        
    }
    else if (table_num == 25)
    {
        for (int i = 0; i < table_num; i++)
        {
            if (table_in_map[i].type == 5 || table_in_map[i].type == 6)
                table_in_map[i].usable = 0;
        }
        table_in_map[1].usable = 1;
        table_in_map[22].usable = 1;
        table_in_map[23].usable = 1;
        table_in_map[0].usable = 1;
        table_in_map[6].usable = 0;
        table_in_map[8].usable = 0;
        table_in_map[13].usable = 0;
        table_in_map[17].usable = 0;
        table_in_map[19].usable = 0;
          table_in_map[14].usable = 0;
        // table_in_map[3].usable=0;
    }
    else if(table_num==50){
        // // table_in_map[6].usable=0;
        // table_in_map[15].usable=0;
        // // table_in_map[21].usable=0;
        // // table_in_map[36].usable=0;
        // table_in_map[49].usable=0;

        // // table_in_map[7].usable=0;
        // // table_in_map[16].usable=0;
        // table_in_map[31].usable=0;
        // table_in_map[35].usable=0;
        // // table_in_map[37].usable=0;

        // // table_in_map[0].usable=0;
        // table_in_map[19].usable=0;
        // // table_in_map[28].usable=0;
        // table_in_map[39].usable=0;
        // // table_in_map[42].usable=0;
        // table_in_map[43].usable=0;

        // table_in_map[8].usable=0;
        // table_in_map[9].usable=0;
        // table_in_map[10].usable=0;
        // table_in_map[17].usable=0;
        // table_in_map[18].usable=0;
        // table_in_map[26].usable=0;
        // table_in_map[27].usable=0;
        // table_in_map[30].usable=0;
        // table_in_map[38].usable=0;
        // table_in_map[40].usable=0;
        // table_in_map[46].usable=0;

        // table_in_map[1].usable=0;
        // table_in_map[2].usable=0;
        // table_in_map[3].usable=0;
        // table_in_map[4].usable=0;
        // table_in_map[5].usable=0;
        // table_in_map[44].usable=0;
        // table_in_map[41].usable=0;
        // table_in_map[45].usable=0;
        // table_in_map[47].usable=0;
        // table_in_map[48].usable=0;

        // // table_in_map[8].usable=0;
        // table_in_map[12].usable=0;
        // table_in_map[13].usable=0;
        // table_in_map[14].usable=0;
        // table_in_map[20].usable=0;
        // // table_in_map[22].usable=0;
        // // table_in_map[23].usable=0;
        // table_in_map[25].usable=0;
        // table_in_map[29].usable=0;
        // table_in_map[32].usable=0;
        // table_in_map[33].usable=0;
        // table_in_map[34].usable=0;

        // table_in_map[24].bot_inttats[0]=0;
        table_in_map[24].bot_inttats[1]=0;
        table_in_map[24].bot_inttats[2]=0;
        table_in_map[24].bot_inttats[3]=0;
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
