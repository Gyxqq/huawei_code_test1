#include "data_struct.h"
#include "c_map.h"
#include "function.h"
#include <string.h>
//#include <Windows.h>
bool process_control(map &now_map, robot now_bot[])
{
  while (1)
  {

   // Sleep(50);
    int frame = 0;
    int money = 0;
    input(frame, money, now_map.gettable(), now_map.gettable_num(), now_bot);
    //  std::cerr<<"gyx "; // 输入
    std::cerr << "process_control frame=" << frame << std::endl;
    bool control = robot_table_control(now_map, now_bot);

    // std::cerr<<"gyx ";                              // 机器人调度
    back_command *this_back_command = new back_command[4]; // 为输出命令申请空间
    for (int i = 0; i < 4; i++)
    {
      back_command *com;
      std::cerr << "gyx1 ";
      if (now_bot[i].avoid_crash(now_bot))
      {
        std::cerr << "gyx2 ";
        com = now_bot[i].bot_avoid_crash(now_bot);
      }
      else
      {
        map1 now_map1;
        now_map1.table_in_map = now_map.gettable();
        now_map1.table_num = *now_map.gettable_num();
        std::cerr << "gyx3 ";
        com = now_bot[i].route_control(now_map1);
        std::cerr << "gyx4 ";
        std::cerr << "\n % bot_num" << i << " control_flag " << now_bot[i].data.control_flag << std::endl;
      }
      memcpy(&this_back_command[i], com, sizeof(back_command));
    }
    output_command *this_output = output_process(this_back_command, frame);
    output(this_output);
  }
}