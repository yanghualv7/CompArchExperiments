#include<iostream>
#include<string>
#include "1-MLR.h"

/*
��ʼ��һ���㹻���Ľ������result������Ϊ2n+1��
�Դ洢���ܵ������������nλ����������˵Ľ�����Ϊ2nλ����

����������int2��ÿһλ�������λ��ʼ��

����int2�е�ÿһλ�������λ��'1'����ᴴ��һ����ʱ����temp���䳤����result��ͬ��
����������int1��Ӧ��ֵ���Ƶ�temp�����Ӧ��λ���ϣ�ģ������Ƴ˷��е�λ�Ʋ�����

����ʱ����temp�е�ֵ���ӵ��������result�С���һ���漰�����Ƶ���λ��Ӻͽ�λ������

��󣬽�������ɵĽ������result��ǰnλ��ֵ��int1����nλ��ֵ��int2��
*/

void mul(char int1[], char int2[], int n) 
{
    // ����һ���µ��ַ��������洢�˷��Ľ��������Ϊ2n+1����Ϊ����nλ����˵Ľ����������2nλ
    char *result = new char[2 * (n + 1)];
    // ��������������λ�ó�ʼ��Ϊ '0'
    memset(result, '0', 2 * (n + 1));

    // �����λ��ʼ���������� int2 ��ÿһλ
    for (int i = n - 1; i >= 0; i--)
    {
        // �����ǰλ�� '1'������Ҫ�������� int1 �ӵ��������Ӧ��λ��
        if (int2[i] == '1') 
        {
            // ����һ����ʱ�������ڴ洢�м���
            char *temp = new char[2 * (n + 1)];
            // ��ʼ����ʱ����Ϊ '0'
            memset(temp, '0', 2 * (n + 1));

            // ���ݵ�ǰ������λ�����������Ƶ���ȷ��λ��
            for (int j = n; j > 0; j--) 
                temp[j + i] = (int1[j - 1] == '1') ? '1' : '0';

            // ���ж����Ƽӷ�������ʱ����ӵ����ս����
            bool carry = false; // ��λ���
            for (int m = 2 * n; m >= 0; m--) 
            {
                int sum = (result[m] - '0') + (temp[m] - '0') + carry; // ����ÿһλ�ĺ�
                result[m] = (sum & 1) + '0';  // ȡ�͵����һλ����ת��Ϊ�ַ��洢
                carry = sum >> 1; // �����µĽ�λ
            }

            // �ͷ���ʱ����ռ�
            delete[] temp;
        }
    }

    // �������ǰnλ��� int1 ��
    for (int i = 0; i < n; i++)
        int1[i] = result[i];

    // ������ĺ�nλ��� int2 ��
    for (int i = n; i < 2 * n; i++)
        int2[i - n] = result[i];

    // �ͷŽ������ռ�
    delete[] result;
}