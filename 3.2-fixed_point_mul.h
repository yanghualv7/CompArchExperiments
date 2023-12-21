#include<iostream>
#include<string>
#include "1-MLR.h"

/*
初始化一个足够长的结果数组result，长度为2n+1，
以存储可能的最大结果（两个n位二进制数相乘的结果最多为2n位）。

遍历操作数int2的每一位，从最低位开始。

对于int2中的每一位，如果该位是'1'，则会创建一个临时数组temp，其长度与result相同，
并将操作数int1对应的值复制到temp中相对应的位置上，模拟二进制乘法中的位移操作。

将临时数组temp中的值添加到结果数组result中。这一步涉及二进制的逐位相加和进位处理。

最后，将计算完成的结果数组result的前n位赋值回int1，后n位赋值回int2。
*/

void mul(char int1[], char int2[], int n) 
{
    // 创建一个新的字符数组来存储乘法的结果，长度为2n+1，因为两个n位数相乘的结果最多可能是2n位
    char *result = new char[2 * (n + 1)];
    // 将结果数组的所有位置初始化为 '0'
    memset(result, '0', 2 * (n + 1));

    // 从最低位开始，遍历乘数 int2 的每一位
    for (int i = n - 1; i >= 0; i--)
    {
        // 如果当前位是 '1'，则需要将被乘数 int1 加到结果中相应的位置
        if (int2[i] == '1') 
        {
            // 创建一个临时数组用于存储中间结果
            char *temp = new char[2 * (n + 1)];
            // 初始化临时数组为 '0'
            memset(temp, '0', 2 * (n + 1));

            // 根据当前乘数的位将被乘数复制到正确的位置
            for (int j = n; j > 0; j--) 
                temp[j + i] = (int1[j - 1] == '1') ? '1' : '0';

            // 进行二进制加法，将临时结果加到最终结果中
            bool carry = false; // 进位标记
            for (int m = 2 * n; m >= 0; m--) 
            {
                int sum = (result[m] - '0') + (temp[m] - '0') + carry; // 计算每一位的和
                result[m] = (sum & 1) + '0';  // 取和的最后一位，并转换为字符存储
                carry = sum >> 1; // 计算新的进位
            }

            // 释放临时数组空间
            delete[] temp;
        }
    }

    // 将结果的前n位存回 int1 中
    for (int i = 0; i < n; i++)
        int1[i] = result[i];

    // 将结果的后n位存回 int2 中
    for (int i = n; i < 2 * n; i++)
        int2[i - n] = result[i];

    // 释放结果数组空间
    delete[] result;
}
