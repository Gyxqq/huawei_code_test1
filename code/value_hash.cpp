#include"data_struct.h"
#include<math.h>
#include"c_map.h"
double f(double x,double maxX,double minRate);//官方文档中的f函数，用以计算时间系数和碰撞系数
double value_hash(map now_map,robot now_bot,int ori,int des)
{
    double val=0;
    double temp_frame=0;
    double money[8]={0,3000,3200,3400,7100,7800,8300,29000};
    double distance1=0,distance2=0;
    table* temp_table=now_map.gettable();
    distance1=sqrt((temp_table[ori].x-now_bot.data.x)*(temp_table[ori].x-now_bot.data.x)+(temp_table[ori].y-now_bot.data.y)*(temp_table[ori].y-now_bot.data.y));
    distance2=sqrt((temp_table[ori].x-temp_table[des].x)*(temp_table[ori].x-temp_table[des].x)+(temp_table[ori].y-temp_table[des].y)*(temp_table[ori].y-temp_table[des].y));
    temp_frame=(distance1+distance2)/6*50;
    double timerate=f(temp_frame,9000,0.8);
    val=money[temp_table[ori].type]*timerate/temp_frame;
    return val;
}

double f(double x,double maxX,double minRate)
{
    double ans=0;
    if(x>=maxX)ans=minRate;
    else
    {
        ans=(1-std::sqrt(1-std::pow(1-x/maxX,2)))*(1-minRate)+minRate;
    }
    return ans;
}