#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <string.h>
using namespace std;
int flag(int *x, int *y, int pos_x, int pos_y, int l);
int check_table(int pos_x, int pos_y);
int check_robot(int pos_x, int pos_y, int *line_x, int *line_y, int l);
int main()
{   srand((unsigned)time(0));	   //随机数种子 
	int n; //地图个数
	cout<<"请输入需要的地图个数"<<endl; 
	cin >> n;
	for (int k = 0; k < n; k++)
	{
		char filename[15] = "map";
		char order[5] = {0};
		int temp_num=k;
		for (int m = 3; m >= 0; m--)
		{
			order[m] = (temp_num % 10) + '0';
			temp_num /= 10;
		}
		strcat(filename, order);
		strcat(filename, ".txt");
		//	}
		freopen(filename, "w", stdout);
		//	cout<<filename<<endl;
		int table_num;				   //工作台数量 
		int table;					   //工作台类型 
		int table_x[55], table_y[55];  //工作台坐标 
		int robot_x[5], robot_y[5];	   //机器人坐标 
		int temp_x, temp_y;			   //临时坐标 
		char map[105][105];			   //存储地图 
		memset(map, '.', sizeof(map)); //地图初始化 
		
		table_num = (rand() % 50) + 1; //随机化工作台数量 
		for (int i = 0; i < table_num; i++)
		{
			int f, h;
			do
			{
				temp_x = (rand() % 100);
				temp_y = (rand() % 100);
				f = flag(table_x, table_y, temp_x, temp_y, i);
				h = check_table(temp_x, temp_y);
			} while (f == 1 || h == 1);
			table_x[i] = temp_x;
			table_y[i] = temp_y;
			table = (rand() % 9) + 1;
			map[temp_x][temp_y] = table + '0';
		} //生成工作台坐标 
		for (int i = 0; i < 4; i++)
		{
			int f, h;
			do
			{
				temp_x = (rand() % 100);
				temp_y = (rand() % 100);
				f = flag(robot_x, robot_y, temp_x, temp_y, i);
				h = check_robot(temp_x, temp_y, table_x, table_y, table_num);
			} while (f == 1 || h == 1);
			robot_x[i] = temp_x;
			robot_y[i] = temp_y;
			map[temp_x][temp_y] = 'A';
		} //生成机器人坐标 
		//	cout<<table_num<<endl;
		//	for(int i=0; i<table_num; i++){
		//		cout<<table_x[i]<<" "<<table_y[i]<<endl;
		//	}
		//	cout<<endl<<4<<endl;
		//	for(int i=0; i<4; i++){
		//		cout<<robot_x[i]<<" "<<robot_y[i]<<endl;
		//	}
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				cout << map[i][j];
			}
			cout << endl;
		} // 输出地图 
	}
	return 0;
}
inline int flag(int *x, int *y, int pos_x, int pos_y, int l)
{
	for (int i = 0; i < l; i++)
	{
		if (pos_x == x[i] && pos_y == y[i])
		{
			return 1;
		}
	}
	return 0;
} //判断坐标是否重复 
inline int check_table(int pos_x, int pos_y)
{
	if (pos_x <= 1 || pos_x >= 98 || pos_y <= 1 || pos_y >= 98)
	{
		return 1;
	}
	else
	{
		return 0;
	}
} //判断工作台坐标是否溢出 
inline int check_robot(int pos_x, int pos_y, int *line_x, int *line_y, int l)
{
	if (pos_x <= 5 || pos_x >= 95 || pos_y <= 5 || pos_y >= 95)
	{
		return 1;
	}
	for (int i = 0; i < l; i++)
	{
		if (pos_x == line_x[i] && pos_y == line_y[i])
		{
			return 1;
		}
	}
	return 0;
} //判断机器人坐标是否溢出