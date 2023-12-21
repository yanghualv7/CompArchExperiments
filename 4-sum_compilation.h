#include<stdio.h>
#include<stdlib.h>

int Sum(int sum[])
{
    int sum_num = 0;
    for(int i = 0; i < 5; i++)
        sum_num += sum[i];

    return sum_num;
}