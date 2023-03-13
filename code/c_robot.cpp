#include"c_robot.h"
#include"c_map.h"
#include<cmath>
back_command* robot::route_control(map& now_map){

}
bool robot::avoid_crash(robot bot[]){
    bool crash = false;
    double time =0.02;//一帧在判题器中的时间
    for(int frame=0;frame<5;frame++)
    {
        for(int i=0;i<4;i++)//计算所有机器人下一帧大概的位置
        {
            double v=sqrt(bot[i].data.speed_x*bot[i].data.speed_x+bot[i].data.speed_y*bot[i].data.speed_y);
            bot[i].data.x=bot[i].data.x+v*cos(bot[i].data.toward)* time;
            bot[i].data.y=bot[i].data.y+v*sin(bot[i].data.toward)* time;
            bot[i].data.toward=bot[i].data.toward+bot[i].data.ang_speed*time;
        }
        for(int i=0;i<4;i++)//分别判断各个机器人是否可能碰撞（已考虑体积变大的情况）
        {
            for(int j=i+1;j<4;j++)
            {
                double distance=sqrt((bot[i].data.x-bot[j].data.x)*(bot[i].data.x-bot[j].data.x)+(bot[i].data.y-bot[j].data.y)*(bot[i].data.y-bot[j].data.y));
                if(!(bot[i].data.control_flag||bot[j].data.control_flag)&&distance<=0.45)
                {
                    crash=true;
                }else if((bot[i].data.control_flag||bot[j].data.control_flag)&&distance<=0.53)
                {
                    crash=true;
                }
            }
        }
    }
    return crash;
}
