#include <iostream>
#include <cmath>
#include <cstring>

unsigned int unsignedToValue(char binary[], int n) 
{
    unsigned int value = 0;
    for (int i = 0; i < n; ++i)
        value = (value << 1) | (binary[i] - '0'); // λ�������Ʋ����ϵ�ǰλ
    return value;
}

int intToValue(char binary[], int n) 
{
    if (binary[0] == '0')
    // ���������
        return unsignedToValue(binary, n);
    
    else 
    { // ����Ǹ���
        // ���㲹��
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

// ���������ַ���ת��Ϊ�����ȸ�����
float floatToValue( char binary[]) 
{
    // ����IEEE 754��׼��ǰ1λ�Ƿ���λ����������8λ��ָ����ʣ�µ�23λ��β��
    int sign = (binary[0] == '1') ? -1 : 1;
    unsigned int exponent = unsignedToValue(&binary[1], 8);
    unsigned int mantissa = unsignedToValue(&binary[9], 23);

    // �����������
    if (exponent == 255)
        return mantissa == 0 ? sign * INFINITY : NAN;

    // ������ʵָ��ֵ
    int e = exponent - 127;

    // ����β������ʵֵ����ʼ��Ϊ1.0����Ϊ1.mantissa��ʽ��
    float m = 1.0f;
    for (int i = 0; i < 23; ++i)
        m += (binary[i + 9] - '0') * std::pow(2.0f, -i - 1);

    // ���㲢������ʵֵ
    if (exponent == 0) 
    {
        // �ǹ����
        e = 1 - 127;
        m = mantissa * std::pow(2.0f, -23);
    }

    return sign * m * std::pow(2.0f, e);
}

// ��������������ɾ���ַ����е����пո�
void removeSpaces(char* s)
{
    char* d = s;
    do 
    {
        while (*s == ' ') 
            ++s;
    } while ((*d++ = *s++));
}