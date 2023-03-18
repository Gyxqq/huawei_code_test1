#include "data_struct.h"
#include <math.h>
#include "c_map.h"
const double delayframe = 300; // 转弯减速等产生的时间差，用于调整
const double _7to89 = 1000000;
const double _6to7 = 100;
const double _5to7 = 90;
const double _4to7 = 80;
const double _6to9 = 70;
const double _5to9 = 60;
const double _4to9 = 50;
const double _23to6 = 40;
const double _13to5 = 30;
const double _12to4 = 20;
const double _123to9 = 10;
const double tableneed = 120;
double f(double x, double maxX, double minRate); // 官方文档中的f函数，用以计算时间系数和碰撞系数
double value_hash(map now_map, robot now_bot, int ori, int des, int now_frame)
{
    double val = 0;                                                           // 输出的hash值
    double temp_frame1 = 0;                                                   // 从起点到终点的持有帧
    double temp_frame2 = 0;                                                   // 总帧数
    double money_in[8] = {0, 3000, 4400, 5800, 15400, 17200, 19200, 76000};   // 买入价
    double money_out[8] = {0, 6000, 7600, 9200, 22500, 25000, 27500, 105000}; // 卖出价
    double distance1 = 0, distance2 = 0;
    int tablenum = *(now_map.gettable_num());
    table *temp_table = now_map.gettable();
    int oritype = temp_table[ori].type, destype = temp_table[des].type;
    std::cerr<<std::endl<<"jztout"<<std::endl<<"1 "<<oritype<<std::endl;
    distance1 = sqrt((temp_table[ori].x - now_bot.data.x) * (temp_table[ori].x - now_bot.data.x) + (temp_table[ori].y - now_bot.data.y) * (temp_table[ori].y - now_bot.data.y));
    distance2 = sqrt((temp_table[ori].x - temp_table[des].x) * (temp_table[ori].x - temp_table[des].x) + (temp_table[ori].y - temp_table[des].y) * (temp_table[ori].y - temp_table[des].y));
    temp_frame1 = (distance2) / 6 * 50;
    temp_frame2 = (distance1 + distance2) / 6 * 50;
    double timerate = f(temp_frame1, 9000, 0.8);
    double profit = (money_out[temp_table[ori].type] * timerate) - money_in[temp_table[ori].type];
    val = profit / (distance1 + distance2);
    std::cerr<<"2 "<<oritype<<std::endl;
    if(oritype==7)val=profit;
    std::cerr<<"3 "<<oritype<<std::endl;
    // 增加不同情况的权重
    if (oritype == 7 && (destype == 8 || destype == 9))
        val = val * _7to89;
    else if (oritype == 6 && destype == 7)
        val = val * _6to7;
    else if (oritype == 5 && destype == 7)
        val = val * _5to7;
    else if (oritype == 4 && destype == 7)
        val = val * _4to7;
    else if (oritype == 6 && destype == 9)
        val = val * _6to9;
    else if (oritype == 5 && destype == 9)
        val = val * _5to9;
    else if (oritype == 4 && destype == 9)
        val = val * _4to9;
    else if ((oritype == 2 || oritype == 3) && destype == 6)
        val = val * _23to6;
    else if ((oritype == 1 || oritype == 3) && destype == 5)
        val = val * _13to5;
    else if ((oritype == 1 || oritype == 2) && destype == 4)
        val = val * _12to4;
    else if ((oritype >= 1 && oritype <= 3) && destype == 9)
        val = val * _123to9;
        std::cerr<<"4 "<<oritype<<std::endl;
    for (int i = 0; i < tablenum; i++)
    {
        if (temp_table[i].type == 7 && temp_table[i].instats[oritype] == 0)
            val = val * tableneed;
    }
    std::cerr<<"5 "<<oritype<<std::endl;
    if (destype == 7 && temp_table[des].instats[oritype] == 0)
        val = val * tableneed;
    std::cerr<<"6 "<<oritype<<std::endl;
    if (temp_frame2 + delayframe > 9000 - now_frame)
        val = 0;
    std::cerr<<"7 "<<oritype<<std::endl;
    return val;
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