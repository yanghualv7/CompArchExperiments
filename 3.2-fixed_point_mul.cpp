#include "3.2-fixed_point_mul.h"

int main()
{

    int n;
    std::cout << "��������������ĳ���(n):" << std::endl;
    std::cin >> n;
    char int1[n];
    char int2[n];

    getchar();//������뻺����

    std::cout << "�������һ����������(������ڿո�):" << std::endl;
    std::cin.getline(int1, n+1); // ʹ��getline��ȡ���ո����
    
    std::cout << "������ڶ�����������(������ڿո�):" << std::endl;
    std::cin.getline(int2, n+1); // ʹ��getline��ȡ���ո����

    removeSpaces(int1); // ɾ�����пո�
    removeSpaces(int2); // ɾ�����пո�

    std::cout<<"���Ϊ��"<<int1<<"*"<<int2<<"=";
    mul(int1, int2, n);
    std::cout<<int1<<" "<<int2<<std::endl;

    system("pause");
    return 0;
}