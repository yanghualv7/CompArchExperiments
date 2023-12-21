#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
0111-0111
结果：0000
ZF=1,SF=0,CF=0,OF=0

0111+1000
结果：1111
ZF=0,SF=1,CF=0,OF=0

0001+1111
结果：0000
ZF=1,SF=0,CF =1,OF=0
cc
0111+0001
结果：1000
ZF=0,SF=1,CF = 0,OF =1

0111-1000
结果：1111
ZF=0,SF=1,CF=1,OF=1
*/

// 函数原型声明
char* addsub(char int1[], char int2[], int flag, int n, char result[]);

int main() 
{
    // 定义二进制字符串数组
    const int n = 4; // 位数
    char int1[n+1] = "0111";
    char int2[n+1] = "1000";
    char result[n+1];
    
    // 加法运算
    printf("加法运算:%s+%s\n",int1,int2);
    char *result0 =  addsub(int1, int2, 0, n, result);
    printf("结果: %s\n\n", result0);


    // 减法运算
    printf("减法运算:%s-%s\n",int1,int2);
    char *result1 = addsub(int1, int2, 1, n, result);
    printf("结果: %s\n\n", result1);

    system("pause");
    return 0;
}

char* addsub(char int1[], char int2[], int flag, int n, char result[]) 
{
    int CF = 0; // 进位标志
    int OF = 0; // 溢出标志
    int SF = 0; // 符号标志
    int ZF = 1; // 零标志，预设为1，如果结果非零，则会被设置为0
    int sum = 0;
    // 如果flag为1，取int2的补码（减法）
    if (flag == 1) 
    {
        for (int i = n - 1; i >= 0; --i) 
            int2[i] = (int2[i] == '0') ? '1' : '0'; // 取反
    }

    // 逐位加法运算
    bool zf_flag = true;
    int of_flag = 0;
    for (int i = n - 1; i >= 0; --i) 
    {
        sum = (int1[i] - '0') + (int2[i] - '0') + CF;

        //用于处理sub信号
        if (i == n - 1)
            sum += flag;
        
        result[i] = (sum & 1) + '0'; // 计算当前位
        CF = sum >> 1; // 更新进位
    
        // 如果不是最后一位产生进位，就更新of_flag
        if (i == 1)
            of_flag = CF;
        if (i == 0)
            OF = of_flag ^ CF;

        // 更新SF和ZF
        SF = result[0] == '1'? 1 : 0;
        if (result[i] == '1'&& zf_flag) 
        {
            ZF = 0;
            zf_flag = false;
        }
    }

    CF = flag ^ CF;
    result[n] = '\0'; // 结果字符串结束符

    // 输出标志位
    printf("ZF = %d, SF = %d, CF = %d, OF = %d\n",ZF, SF, CF, OF);

    return result;
}
