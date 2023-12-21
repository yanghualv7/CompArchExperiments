#include "1-MLR.h"
#include <algorithm> // ���algorithmͷ�ļ�����remove��copy


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
    // * ������ײ�Ϊ�̶����㣬Ĭ�Ͻ���һ��ָ��Ϊ�����ڶ���ָ��Ϊ��

    int sum = 0, carry = 0;
    char* float3 = new char[10];
    memset(float3, '0', 10);
    size_t size = 10; 

    char* float1_copy = new char[size]; // �����ڴ�
    std::copy(float1, float1 + size, float1_copy); // �����ַ���
    float1_copy[0] = '0';
    float1_copy[n] = '\0';

    char* float2_copy = new char[size]; // �����ڴ�
    std::copy(float2, float2 + size, float2_copy); // �����ַ���
    float2_copy[n] = '\0';
    float2_copy[0] = '1';

    // ���㲹��
    float2_copy = twosComplement(float2_copy, n);

    // ��λ�ӷ�����
    for (int i = n - 1; i >= 0; --i) 
    {
        sum = (float1_copy[i] - '0') + (float2_copy[i] - '0') + carry;
        float3[i] = (sum & 1) + '0'; // ���㵱ǰλ
        carry = sum >> 1; // ���½�λ
    }

    float3[n] = '\0'; // ����ַ���������

    // ��������ԭ��
    int sign = (float3[0] == '0' ? 1 : -1);
    if(sign == -1)
        float3 = twosComplement(float3, 10);
    
    int exponent_value = unsignedToValue(float3 + 1, 8) * sign;

    delete[] float1_copy, float2_copy; // ʹ����Ϻ��ͷ��ڴ�
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

    // * ����λ����Ϣ�洢��β������
    float0[0] = float2[0];
    
}

void modify_exponent(char float0[], int n)
{
    char int_n[8];
    for (int i = 7; i >= 0; i--) 
    {
        int_n[i] = (n & 1) + '0';  // �����λȡ����ת��Ϊ�ַ�
        n = n >> 1;  // ����һλ
    }
    
    int carry = 0, sum = 0;
    for (int i = 7; i > 0; --i) 
    {
        sum = (float0[i] - '0') + (int_n[i] - '0') + carry;
        float0[i] = (sum & 1) + '0'; // ���㵱ǰλ
        if(sum > 0)
            carry = sum >> 1; // ���½�λ
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
    //��λʱ�轫�����ġ�1����ʾ����
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
    // * תΪ����ǰ,�Ƚ�˫����λ������λ
    insertChar(float0, float0_sign);
    insertChar(float1, float1_sign);

    if(float0_sign - '0' == 1)
        twosComplement(float0 + 1, 25);
    if(float1_sign - '0' == 1)
        twosComplement(float1 + 1, 25);

    char *result = (char*)malloc((n+2)*sizeof(char)); // ʹ�ö�̬�ڴ����
    int sum = 0, carry = 0;
    for(int i = n; i >= 0; --i)
    {
        sum = (float0[i] - '0') + (float1[i] - '0') + carry;
        result[i] = (sum & 1) + '0'; // ���㵱ǰλ
        if(sum > 0)
            carry = sum >> 1; // ���½�λ
        else
            carry = 0;
    }

    // * ������ת��ԭ��(���ʹ���˲���ӷ�)
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

    // * ��ײ�
    // ! �˴�Ϊ�˷����ʾ���������������ԣ�������λҲ���룬
    // ! ���˷���λֻ����ռλ�����������Ի���addsub�����·��䡣
    exponent_value =  addsub(float1, float2, 9);

    if(exponent_value < 0) 
    {
        char temp[100];
        strcpy(temp, float1);
        strcpy(float1, float2);
        strcpy(float2, temp);
    }


    exponent_value = abs(exponent_value);
    // ����ͳһ
    modify_exponent(float2 + 1, exponent_value);

    // ! β������exponent_valueλ��β�����(����λ��1������ʾ����)
    mantissa_right_shift(mantissa2, float2 + 9,  mantissa1, float1 + 9, exponent_value);
 
    char *res =  add_mantissa(mantissa1, float1[0], mantissa2, float2[0], 25);
    // std::cout << "res: " << res << std::endl; 
    // std::cout << "mantissa1: " << mantissa1 << std::endl;
    // std::cout << "mantissa2: " << mantissa2 << std::endl;

    // ! ˫����λ����ȱ�������������������ʵ���ҹ淽���������ʱ��ʵ��
    if(res[0] != res[1])
    {
        // std::cout << "Overflow!" << std::endl;
        // �ҹ�
        right_shift(res, 1);
        res[25] = '1'; //ʹ�ú���1��
        res[26] = '\0';
        // std::cout << "res: " << res << std::endl; 
        modify_exponent(float1 + 1, 1);
    }
    compose_float(resual_num, float1, res);

    resual_num[32] = '\0';
    
    return resual_num;
}