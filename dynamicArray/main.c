#include <stdio.h>
#include "dynamicArray.h"


#define BUFFER_SIZE 20
#define DEFAULT_NUM 5
int main()
{
    dynamicArray array;
    /* 初始化 */
    dynamicArrayInit(&array, BUFFER_SIZE);

    {

        /* 插入数据 */
        dynamicArrayInsertData(&array, 3);
        for(int idx = 1; idx <= DEFAULT_NUM; idx++)
        {
            dynamicArrayInsertData(&array, 21);
        }

        
    }
    /* 模块化 */
    {  
        /* 获取动态数组的大小 */
        int size = 0;
    
        dynamicArrayGetSize(&array, &size);
        printf("size:%d\n", size);
    }
    
    
    {
        /* 获取动态数组的大小 */
        int size = 0;
        dynamicArrayGetSize(&array, &size);
        printf("size:%d\n", size);

        int val = 0;
        for(int idx = 0; idx < size; idx++)
        {
            dynamicArrayGetAppointPosVal(&array, idx, &val);
            printf("val:%d\t", val);
        }
        printf("\n");

    }
    {
   
        /* 删除指定 */
        dynamicArrayDeleteAppointPosData(&array);

        /* 获取动态数组的大小 */
        dynamicArrayGetSize(&array, &size);
        printf("size:%d\n", size);

        int val = 0;
        for(int idx = 0; idx < size; idx++)
        {
            dynamicArrayGetAppointPosVal(&array, idx, &val);
            printf("val:%d\t", val);
        }

    }
    return 0;

}


