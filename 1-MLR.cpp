#include "1-MLR.h"

int main()
{
    char binary[64]; // ���������С�����ɿ��ܵĿո�
    std::cout << "������32λ��������(������ڿո�):" << std::endl;
    std::cin.getline(binary, 64); // ʹ��getline��ȡ���ո����

    removeSpaces(binary); // ɾ�����пո�

    int n = strlen(binary);
    // ������
    if (n == 32) 
    {
        float floatValue = floatToValue(binary);
        std::cout << "��������ֵΪ��" << floatValue << std::endl;
    }
    // ����
    unsigned int unsignedValue = unsignedToValue(binary, n);
    std::cout << "�޷���������ֵΪ��" << unsignedValue << std::endl;

    int intValue = intToValue(binary, n);
    std::cout << "�з���������ֵΪ��" << intValue << std::endl;

    system("pause");
    return 0;
}
