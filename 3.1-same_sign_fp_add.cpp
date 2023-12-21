#include <iostream>
#include<string.h>
#include "3.1-same_sign_fp_add.h"

int main()
{
    // todo 如若需要手动输入请打开第二段代码 
#if 0

    char float1[64]= "0100 0010 1111 0000 0000 0000 0000 0000";
    char float2[64]= "0100 0001 1101 0000 0000 0000 0000 0000";
#endif

#if 1

    char float1[64];
    char float2[64];
    std::cout << "请输入第一个32位二进制数(允许存在空格):" << std::endl;
    std::cin.getline(float1, 64); // 使用getline读取含空格的行

    std::cout << "请输入第二个32位二进制数(允许存在空格):" << std::endl;
    std::cin.getline(float2, 64); // 使用getline读取含空格的行
#endif

    removeSpaces(float1); // 删除所有空格
    removeSpaces(float2); // 删除所有空格

    float val = floatToValue(addfloat(float1, float2));
    std::cout << "两个二进制数相加的结果为:" << val << std::endl;

    system("pause");
    return 0;


}

