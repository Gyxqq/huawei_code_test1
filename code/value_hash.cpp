#include"data_struct.h"
#include<stdlib.h>
#include<time.h>
#include"c_map.h"
double value_hash(map now_map,robot now_bot,int ori,int des)
{
    srand(time(0));
    return rand() % 100 + 1;
}