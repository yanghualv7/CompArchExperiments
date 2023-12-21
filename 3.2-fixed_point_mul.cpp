#include "3.2-fixed_point_mul.h"

int main()
{

    int n;
    std::cout << "请输入二进制数的长度(n):" << std::endl;
    std::cin >> n;
    char int1[n];
    char int2[n];

    getchar();//清除输入缓冲区

    std::cout << "请输入第一个二进制数(允许存在空格):" << std::endl;
    std::cin.getline(int1, n+1); // 使用getline读取含空格的行
    
    std::cout << "请输入第二个二进制数(允许存在空格):" << std::endl;
    std::cin.getline(int2, n+1); // 使用getline读取含空格的行

    removeSpaces(int1); // 删除所有空格
    removeSpaces(int2); // 删除所有空格

    std::cout<<"结果为："<<int1<<"*"<<int2<<"=";
    mul(int1, int2, n);
    std::cout<<int1<<" "<<int2<<std::endl;

    system("pause");
    return 0;
}