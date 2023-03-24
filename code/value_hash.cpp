#include "data_struct.h"
#include <math.h>
#include "c_map.h"
#include <time.h>
double go_time(map now_map, robot now_bot, int ori, int des);
double time_xs = 1;
double money_xs = 1;
double yx_xs = 1;
double f(double x, double maxX, double minRate); // 官方文档中的f函数，用以计算时间系数和碰撞系数
double value_hash(map now_map, robot now_bot, int ori, int des, int now_frame)
{

    table *tab = now_map.gettable();
    int table_num = *now_map.gettable_num();
    double time = go_time(now_map, now_bot, ori, des);
    if ((9000 - now_frame) * 0.2 < time)
        return -1;
    // if (now_frame > 8500 && tab[now_bot.data.ori].type > 3)
    // {
    //     now_bot.data.control_flag = 2;
    //     now_bot.data.object = 1;
    //     now_bot.data.des = rand() % table_num;
    //     return -1;
    // }
    if (table_num == 25)
    {
        double val = 0;
        double money = 0;
        if (tab[ori].type == 1)
            money = 3000;
        if (tab[ori].type == 2)
            money = 3200;
        if (tab[ori].type == 3)
            money = 3400;
        if (tab[ori].type == 4)
            money = 7100;
        if (tab[ori].type == 5)
            money = 7800;
        if (tab[ori].type == 6)
            money = 8300;
        if (tab[ori].type == 7)
            money = 29000;
        double yx = 1;
        if (tab[ori].type == 4 || tab[ori].type == 5 || tab[ori].type == 6)
        {
            if (tab[des].type == 7)
                yx = 300;
        }
        if (tab[ori].type == 7)
        {
            if (tab[des].type == 8)
            {
                yx = 2000;
            }
            else
                yx = 2000;
        }
        for (int i = 0; i < table_num; i++)
        {
            if (tab[i].type == 7 && tab[i].usable == 1)
            {
                int i2 = 1;
                if (tab[i].instats[4] == 1)
                    i2++;
                if (tab[i].instats[5] == 1)
                    i2++;
                if (tab[i].instats[6] == 1)
                    i2++;
                if (tab[i].instats[tab[des].type] == 0)
                    yx *= i2;
               
            }
        }

        val = yx/time;
        return val;
    }
    else
    {

        double val = 0;
        double money = 0;
        if (tab[ori].type == 1)
            money = 3000;
        if (tab[ori].type == 2)
            money = 3200;
        if (tab[ori].type == 3)
            money = 3400;
        if (tab[ori].type == 4)
            money = 7100;
        if (tab[ori].type == 5)
            money = 7800;
        if (tab[ori].type == 6)
            money = 8300;
        if (tab[ori].type == 7)
            money = 29000;
        double yx = 1;
        // if (tab[ori].type == 1 || tab[ori].type == 2 || tab[ori].type == 3)
        // {

        //     if (tab[des].type == 4 || tab[des].type == 5 || tab[des].type == 6)
        //     {
        //         yx = 1;
        //     }
        //     else
        //         yx = 1;
        // }
        if (tab[ori].type == 4 || tab[ori].type == 5 || tab[ori].type == 6)
        {
            if (tab[des].type == 9)
            {
                yx = 15;
            }
            else
                yx = 15;
        }
        if (tab[ori].type == 7)
        {
            if (tab[des].type == 8)
            {
                yx = 20;
            }
            else
                yx = 20;
        }
        // for (int i = 0; i < table_num; i++)
        // {
        //     if (tab[i].type == 7)
        //     {
        //         int i = 0;
        //         if (tab[i].instats[4] == 1)
        //             i++;
        //         if (tab[i].instats[5] == 1)
        //             i++;
        //         if (tab[i].instats[6] == 1)
        //             i++;
        //         if (tab[i].instats[tab[des].type] == 0)
        //             yx = 2;
        //         else
        //             yx = yx;
        //     }
        // }

        val = yx * money_xs * money / (time_xs * pow(time, 8));
        return val;
    }
}

double f(double x, double maxX, double minRate)
{
    double ans = 0;
    if (x >= maxX)
        ans = minRate;
    else
    {
        ans = (1 - std::sqrt(1 - std::pow(1 - x / maxX, 2))) * (1 - minRate) + minRate;
    }
    return ans;
}
double go_time(map now_map, robot now_bot, int ori, int des)
{
    table *tab = now_map.gettable();
    double des1 = pow(tab[ori].x - now_bot.data.x, 2) + pow(tab[ori].y - now_bot.data.y, 2);
    double des2 = pow(tab[ori].x - tab[des].x, 2) + pow(tab[ori].y - tab[des].y, 2);
    double time = (sqrt(des1) + sqrt(des2)) / 3.5;
    return time;
}