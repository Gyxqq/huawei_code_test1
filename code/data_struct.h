struct table
{
    int num;  // 工作台编号，从0开始
    int type; // 工作台类型 type=1为1型工作台，以此类推

    double x, y; // 工作台位置

    int rest;      /*
     
                   -1:表示没有生产
                   0:表示生产因为输出格满而阻塞
                   >=0:表示剩余生产的帧数
     
                   */
    bool outstats; // 产品格状态 0表示无,1表示有

    bool instats[8]; // 储存原料格状态 储存七种原料填充状态，从数组1号元素开始 0表示无,1表示有

    // 储存工作台信息
};

struct command
{
    char command[8]; // 指令内容
    /*
    命令                        int 参数1[取值]              double 参数2
    forward 前进                机器人ID[0，3]        前进速度[-2,6] 单位m/s
    rotate 旋转                 机器人ID[0，3]        旋转速度[-pai,pai] 单位弧度每秒
    buy 购买当前工作台物品       机器人ID[0，3]                 none
    sell 售出当前物品           机器人ID[0，3]                  none
    destroy 摧毁物品            机器人ID[0，3]                  none
    */

    double arg1;
    double arg2;
};

struct output_command
{
    int frame;            // 当前帧
    int command_num;      // 输出的命令数
    command *out_command; // 储存命令的数组，建议采用动态内存分配空间
};

struct robot_data{
   int num;           // 机器人编号 [0,3]
  double x, y;       // 机器人位置
  int table;         // 机器人所处的工作台ID -1表示当前没有处于任何工作台周围 从0开始
  int object;        // 携带物品种类 0表示未携带
  double time_value; // 时间价值系数
  double col_value;  // 碰撞价值系数
  double ang_speed;  // 角速度
      double speed_x,
      speed_y;   // 线速度
  double toward; // 朝向 与平面直角坐标系的单位圆射线方向相同 toward=0时向右
};