#include"data_struct.h"
#include<math.h>
#include"c_map.h"
double f(double x,double maxX,double minRate);//官方文档中的f函数，用以计算时间系数和碰撞系数
 double value_hash(map now_map, robot now_bot, int ori, int des,int now_frame)
{
    const double delayframe=200;
    double val=0;   //输出的hash值
    double temp_frame1=0;       //从起点到终点的持有帧
    double temp_frame2=0;       //总帧数
    double money_in[8]={0,3000,4400,5800,15400,17200,19200,76000};  //买入价
    double money_out[8]={0,6000,7600,9200,22500,25000,27500,105000};  //卖出价
    double distance1=0,distance2=0;
    table* temp_table=now_map.gettable();
    distance1=sqrt((temp_table[ori].x-now_bot.data.x)*(temp_table[ori].x-now_bot.data.x)+(temp_table[ori].y-now_bot.data.y)*(temp_table[ori].y-now_bot.data.y));
    distance2=sqrt((temp_table[ori].x-temp_table[des].x)*(temp_table[ori].x-temp_table[des].x)+(temp_table[ori].y-temp_table[des].y)*(temp_table[ori].y-temp_table[des].y));
    temp_frame1=(distance2)/6*50;
    temp_frame2=(distance1+distance2)/6*50;
    double timerate=f(temp_frame1,9000,0.8);
    double profit=(money_out[temp_table[ori].type]*timerate)-money_in[temp_table[ori].type];
    val=pow(profit,temp_table[ori].type)/temp_frame2;
    if(temp_frame2+delayframe>9000-now_frame)val=0;
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