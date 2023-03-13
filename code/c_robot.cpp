#include"c_robot.h"
#include"c_map.h"
#include<cmath>
#include<cstring>
#include"data_struct.h"
back_command* robot::route_control(map& now_map){
    const double PI=3.14159;
	double delta_x, delta_y;
	double tan_angle, angle;
	//机器人与所要去的工作台的坐标变化量 
	table *goto_table;
	//定义地图上的工作台
	goto_table=now_map.gettable();
	//返回地图上的工作台 
	back_command command_need;
	//声明需要返回的指令 
	command_need.command_num=0;
	//指令个数初始化 
	if(data.table==data.ori){
		command_need.command_num++;
		strcpy(command_need.back_command->command, "buy");
		command_need.back_command->command[3]=' ';
		command_need.back_command->command[4]=data.num+'0';
	}
	//机器人到达起点 
	else if(data.table==data.des){
		command_need.command_num++;
		strcpy(command_need.back_command->command, "sell");
		command_need.back_command->command[4]=' ';
		command_need.back_command->command[5]=data.num+'0';
	}
	//机器人到达终点 
	if(data.object==0){
		delta_x=goto_table[data.ori].x-data.x;
		delta_y=goto_table[data.ori].y-data.y;
		tan_angle=delta_y/delta_x;
		if(delta_x>=0){
			angle=atan(tan_angle);
		}
		else if(delta_y>=0){
			tan_angle*=-1;
			angle=atan(tan_angle);
			angle=PI-angle;
		}
		else if(delta_y<0){
			tan_angle*=-1;
			angle=atan(tan_angle);
			angle=-1*PI-angle;
		}
	}
	//机器人去往起点 
	else if(data.object>=1&&data.object<=9){
		delta_x=goto_table[data.des].x-data.x;
		delta_y=goto_table[data.des].y-data.y;
		tan_angle=delta_y/delta_x;
		if(delta_x>=0){
			angle=atan(tan_angle);
		}
		else if(delta_y>=0){
			tan_angle*=-1;
			angle=atan(tan_angle);
			angle=PI-angle;
		}
		else if(delta_y<0){
			tan_angle*=-1;
			angle=atan(tan_angle);
			angle=-1*PI-angle;
		}
	}
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
