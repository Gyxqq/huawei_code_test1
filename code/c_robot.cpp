#include"c_robot.h"
#include"c_map.h"
#include<cmath>
#include<cstring>
#include"data_struct.h"
back_command* robot::route_control(map& now_map){
    const double PI=3.14159;
	const double min_angle=1.97392;
	double delta_x, delta_y;
	//机器人与所要去的工作台的坐标变化量 
	double tan_angle, angle;
	//计算机器人与工作台连线的角度
	double turn_angle;
	bool direction;
	//判断机器人顺时针还是逆时针旋转
	table *goto_table;
	//定义地图上的工作台
	goto_table=now_map.gettable();
	//返回地图上的工作台 
	back_command *command_need=new back_command;
	//声明需要返回的指令 
	command_need->command_num=0;
	//指令个数初始化 
	if(data.table==data.ori){
		command_need->command_num++;
		strcpy(command_need->back_command->command, "buy");
		command_need->back_command->arg1=data.num;
		command_need->back_command->command_tpye=1;
		data.control_flag=2;
	}
	//机器人到达起点 
	else if(data.table==data.des){
		command_need->command_num++;
		strcpy(command_need->back_command->command, "sell");
		command_need->back_command->arg1=data.num;
		command_need->back_command->command_tpye=1;
		data.control_flag=0;
	}
	//机器人到达终点 
	if(data.control_flag==1){
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
	else if(data.control_flag==2){
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
	//机器人去往终点
	turn_angle=data.toward-angle;
	//机器人朝向与所要转到的朝向的角度的差值
	if(turn_angle<=min_angle){
		command_need->command_num++;
		strcpy(command_need->back_command->command, "rotate");
		command_need->back_command->arg1=data.num;
		command_need->back_command->arg2=
	}
}
bool robot::avoid_crash(robot bot[]){
    bool crash = false;
    double time =0.02;//一帧在判题器中的时间
	robot_data temp_bot[4];
    for(int frame=0;frame<5;frame++)
    {
        for(int i=0;i<4;i++)//计算所有机器人下一帧大概的位置
        {
			temp_bot[i]=bot[i].data;
            double v=sqrt(temp_bot[i].speed_x*temp_bot[i].speed_x+temp_bot[i].speed_y*temp_bot[i].speed_y);
            temp_bot[i].x=temp_bot[i].x+v*cos(temp_bot[i].toward)* time;
            temp_bot[i].y=temp_bot[i].y+v*sin(temp_bot[i].toward)* time;
            temp_bot[i].toward=temp_bot[i].toward+temp_bot[i].ang_speed*time;
        }
        for(int i=0;i<4;i++)//分别判断各个机器人是否可能碰撞（已考虑体积变大的情况）
        {
            if(i!=data.num)
            {
                double distance=sqrt((temp_bot[i].x-temp_bot[data.num].x)*(temp_bot[i].x-temp_bot[data.num].x)+(temp_bot[i].y-temp_bot[data.num].y)*(bot[i].data.y-bot[data.num].data.y));
                if(!(temp_bot[i].control_flag||temp_bot[data.num].control_flag)&&distance<=0.45)
                {
                    crash=true;
                }else if((temp_bot[i].control_flag||temp_bot[data.num].control_flag)&&distance<=0.53)
                {
                    crash=true;
                }
            }
        }
    }
    return crash;
}
back_command* robot::bot_avoid_crash()
{
	
}