#include"function.h"
int main()
{

    freopen("log.txt","w",stderr);
    map now_map;
    robot* now_bot = new robot[4];
    now_map.mapinit(now_bot); // 地图初始化
    
    process_control(now_map, now_bot);
}