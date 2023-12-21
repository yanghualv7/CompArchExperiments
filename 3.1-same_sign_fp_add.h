#include "1-MLR.h"
#include <algorithm> // 添加algorithm头文件用于remove和copy


char* twosComplement(char float0[], int n) 
{
    bool falg = true;
    for (int i = n-1; i > 0; --i)
        {
            if(float0[i] == '1' && falg)
                falg = false;
            else if (!falg)
                float0[i] = float0[i] == '0' ? '1' : '0';
        }
    return float0;
}


int addsub(char float1[], char float2[], int n)
{
    // * 由于求阶差为固定计算，默认将第一个指定为正，第二个指定为负

    int sum = 0, carry = 0;
    char* float3 = new char[10];
    memset(float3, '0', 10);
    size_t size = 10; 

    char* float1_copy = new char[size]; // 分配内存
    std::copy(float1, float1 + size, float1_copy); // 复制字符串
    float1_copy[0] = '0';
    float1_copy[n] = '\0';

    char* float2_copy = new char[size]; // 分配内存
    std::copy(float2, float2 + size, float2_copy); // 复制字符串
    float2_copy[n] = '\0';
    float2_copy[0] = '1';

    // 计算补码
    float2_copy = twosComplement(float2_copy, n);

    // 逐位加法运算
    for (int i = n - 1; i >= 0; --i) 
    {
        sum = (float1_copy[i] - '0') + (float2_copy[i] - '0') + carry;
        float3[i] = (sum & 1) + '0'; // 计算当前位
        carry = sum >> 1; // 更新进位
    }

    float3[n] = '\0'; // 结果字符串结束符

    // 计算结果的原码
    int sign = (float3[0] == '0' ? 1 : -1);
    if(sign == -1)
        float3 = twosComplement(float3, 10);
    
    int exponent_value = unsignedToValue(float3 + 1, 8) * sign;

    delete[] float1_copy, float2_copy; // 使用完毕后释放内存
    return exponent_value;
}

void compose_float(char float0[], char float1[], char float2[]) 
{
    for(int i = 0; i < 32; i++)
    {
        if(i < 9)
            float0[i] = float1[i];
        else
            float0[i] = float2[i - 6];       
    }

    // * 符号位的信息存储在尾数部分
    float0[0] = float2[0];
    
}

void modify_exponent(char float0[], int n)
{
    char int_n[8];
    for (int i = 7; i >= 0; i--) 
    {
        int_n[i] = (n & 1) + '0';  // 将最低位取出并转换为字符
        n = n >> 1;  // 右移一位
    }
    
    int carry = 0, sum = 0;
    for (int i = 7; i > 0; --i) 
    {
        sum = (float0[i] - '0') + (int_n[i] - '0') + carry;
        float0[i] = (sum & 1) + '0'; // 计算当前位
        if(sum > 0)
            carry = sum >> 1; // 更新进位
        else
            carry = 0;
    }
}

void right_shift(char float0[], int n) 
{
    int len = 26;
    for (int i = len - n - 1; i >= 0; i--)
        float0[i + n] = float0[i];
}

void mantissa_right_shift(char mantissa0[], char float0[], char mantissa1[], char float1[], int n) 
{
    //移位时需将隐含的‘1’显示出来
    mantissa0[n] = '1';
    mantissa1[0] = '1';   
    for(int i = 0; i < 23; i++)
    {
        mantissa0[i+n+1] = float0[i];
        mantissa1[i+1] = float1[i];
    }
    mantissa0[25+n+1] = '\0';
    mantissa1[25] = '\0';

}


void insertChar(char *arr, char sign) 
{
    int length = strlen(arr);
    for (int i = length+1; i >= 0; i--)
        arr[i+2] = arr[i];
    arr[0] = sign;
    arr[1] = sign;
}

char* add_mantissa(char float0[], char float0_sign, char float1[], char float1_sign, int n)
{
    // * 转为补码前,先将双符号位放入首位
    insertChar(float0, float0_sign);
    insertChar(float1, float1_sign);

    if(float0_sign - '0' == 1)
        twosComplement(float0 + 1, 25);
    if(float1_sign - '0' == 1)
        twosComplement(float1 + 1, 25);

    char *result = (char*)malloc((n+2)*sizeof(char)); // 使用动态内存分配
    int sum = 0, carry = 0;
    for(int i = n; i >= 0; --i)
    {
        sum = (float0[i] - '0') + (float1[i] - '0') + carry;
        result[i] = (sum & 1) + '0'; // 计算当前位
        if(sum > 0)
            carry = sum >> 1; // 更新进位
        else
            carry = 0;
    }

    // * 将补码转回原码(如果使用了补码加法)
    if(result[0] - '0' == 1 )
        twosComplement(result + 1, n + 1);

    result[n+1] = '\0';
    return result;

}

char* addfloat(char float1[],char float2[])
{
    int exponent_value = 0;
    char* mantissa1 = new char[27];
    memset(mantissa1, '0', 27);
    char* mantissa2 = new char[27];
    memset(mantissa2, '0', 27);
    char* resual_num = new char[32];

    // * 求阶差
    // ! 此处为了方便表示阶码相减后的正负性，将符号位也放入，
    // ! 但此符号位只用于占位，具体正负性会在addsub中重新分配。
    exponent_value =  addsub(float1, float2, 9);

    if(exponent_value < 0) 
    {
        char temp[100];
        strcpy(temp, float1);
        strcpy(float1, float2);
        strcpy(float2, temp);
    }


    exponent_value = abs(exponent_value);
    // 阶码统一
    modify_exponent(float2 + 1, exponent_value);

    // ! 尾数右移exponent_value位，尾数相加(隐含位“1”已显示出来)
    mantissa_right_shift(mantissa2, float2 + 9,  mantissa1, float1 + 9, exponent_value);
 
    char *res =  add_mantissa(mantissa1, float1[0], mantissa2, float2[0], 25);
    // std::cout << "res: " << res << std::endl; 
    // std::cout << "mantissa1: " << mantissa1 << std::endl;
    // std::cout << "mantissa2: " << mantissa2 << std::endl;

    // ! 双符号位不相等表明发生溢出，本程序仅实现右规方法，左规暂时不实现
    if(res[0] != res[1])
    {
        // std::cout << "Overflow!" << std::endl;
        // 右规
        right_shift(res, 1);
        res[25] = '1'; //使用恒置1法
        res[26] = '\0';
        // std::cout << "res: " << res << std::endl; 
        modify_exponent(float1 + 1, 1);
    }
    compose_float(resual_num, float1, res);

    resual_num[32] = '\0';
    
    return resual_num;
}