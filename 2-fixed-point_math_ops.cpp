#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
0111-0111
�����0000
ZF=1,SF=0,CF=0,OF=0

0111+1000
�����1111
ZF=0,SF=1,CF=0,OF=0

0001+1111
�����0000
ZF=1,SF=0,CF =1,OF=0
cc
0111+0001
�����1000
ZF=0,SF=1,CF = 0,OF =1

0111-1000
�����1111
ZF=0,SF=1,CF=1,OF=1
*/

// ����ԭ������
char* addsub(char int1[], char int2[], int flag, int n, char result[]);

int main() 
{
    // ����������ַ�������
    const int n = 4; // λ��
    char int1[n+1] = "0111";
    char int2[n+1] = "1000";
    char result[n+1];
    
    // �ӷ�����
    printf("�ӷ�����:%s+%s\n",int1,int2);
    char *result0 =  addsub(int1, int2, 0, n, result);
    printf("���: %s\n\n", result0);


    // ��������
    printf("��������:%s-%s\n",int1,int2);
    char *result1 = addsub(int1, int2, 1, n, result);
    printf("���: %s\n\n", result1);

    system("pause");
    return 0;
}

char* addsub(char int1[], char int2[], int flag, int n, char result[]) 
{
    int CF = 0; // ��λ��־
    int OF = 0; // �����־
    int SF = 0; // ���ű�־
    int ZF = 1; // ���־��Ԥ��Ϊ1�����������㣬��ᱻ����Ϊ0
    int sum = 0;
    // ���flagΪ1��ȡint2�Ĳ��루������
    if (flag == 1) 
    {
        for (int i = n - 1; i >= 0; --i) 
            int2[i] = (int2[i] == '0') ? '1' : '0'; // ȡ��
    }

    // ��λ�ӷ�����
    bool zf_flag = true;
    int of_flag = 0;
    for (int i = n - 1; i >= 0; --i) 
    {
        sum = (int1[i] - '0') + (int2[i] - '0') + CF;

        //���ڴ���sub�ź�
        if (i == n - 1)
            sum += flag;
        
        result[i] = (sum & 1) + '0'; // ���㵱ǰλ
        CF = sum >> 1; // ���½�λ
    
        // ����������һλ������λ���͸���of_flag
        if (i == 1)
            of_flag = CF;
        if (i == 0)
            OF = of_flag ^ CF;

        // ����SF��ZF
        SF = result[0] == '1'? 1 : 0;
        if (result[i] == '1'&& zf_flag) 
        {
            ZF = 0;
            zf_flag = false;
        }
    }

    CF = flag ^ CF;
    result[n] = '\0'; // ����ַ���������

    // �����־λ
    printf("ZF = %d, SF = %d, CF = %d, OF = %d\n",ZF, SF, CF, OF);

    return result;
}
