#include <iostream>
#include<string.h>
#include "3.1-same_sign_fp_add.h"

int main()
{
    // todo ������Ҫ�ֶ�������򿪵ڶ��δ��� 
#if 0

    char float1[64]= "0100 0010 1111 0000 0000 0000 0000 0000";
    char float2[64]= "0100 0001 1101 0000 0000 0000 0000 0000";
#endif

#if 1

    char float1[64];
    char float2[64];
    std::cout << "�������һ��32λ��������(������ڿո�):" << std::endl;
    std::cin.getline(float1, 64); // ʹ��getline��ȡ���ո����

    std::cout << "������ڶ���32λ��������(������ڿո�):" << std::endl;
    std::cin.getline(float2, 64); // ʹ��getline��ȡ���ո����
#endif

    removeSpaces(float1); // ɾ�����пո�
    removeSpaces(float2); // ɾ�����пո�

    float val = floatToValue(addfloat(float1, float2));
    std::cout << "��������������ӵĽ��Ϊ:" << val << std::endl;

    system("pause");
    return 0;


}

