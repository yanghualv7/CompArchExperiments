#include <iostream>
#include <cmath>
#include <cstring>

unsigned int unsignedToValue(char binary[], int n) 
{
    unsigned int value = 0;
    for (int i = 0; i < n; ++i)
        value = (value << 1) | (binary[i] - '0'); // 位运算左移并加上当前位
    return value;
}

int intToValue(char binary[], int n) 
{
    if (binary[0] == '0')
    // 如果是正数
        return unsignedToValue(binary, n);
    
    else 
    { // 如果是负数
        // 计算补码
        bool falg = true;
        for (int i = n-1; i >= 0; --i)
            {
                if(binary[i] == '1' && falg)
                    falg = false;
                else if (!falg)
                    binary[i] = binary[i] == '0' ? '1' : '0';  
            }

        unsigned int magnitude = unsignedToValue(binary, n);
        return -static_cast<int>(magnitude);
    }
}

// 将二进制字符串转换为单精度浮点数
float floatToValue( char binary[]) 
{
    // 按照IEEE 754标准，前1位是符号位，接下来的8位是指数，剩下的23位是尾数
    int sign = (binary[0] == '1') ? -1 : 1;
    unsigned int exponent = unsignedToValue(&binary[1], 8);
    unsigned int mantissa = unsignedToValue(&binary[9], 23);

    // 特殊情况处理
    if (exponent == 255)
        return mantissa == 0 ? sign * INFINITY : NAN;

    // 计算真实指数值
    int e = exponent - 127;

    // 计算尾数的真实值，初始化为1.0（因为1.mantissa形式）
    float m = 1.0f;
    for (int i = 0; i < 23; ++i)
        m += (binary[i + 9] - '0') * std::pow(2.0f, -i - 1);

    // 计算并返回真实值
    if (exponent == 0) 
    {
        // 非规格化数
        e = 1 - 127;
        m = mantissa * std::pow(2.0f, -23);
    }

    return sign * m * std::pow(2.0f, e);
}

// 新增函数，用于删除字符串中的所有空格
void removeSpaces(char* s)
{
    char* d = s;
    do 
    {
        while (*s == ' ') 
            ++s;
    } while ((*d++ = *s++));
}