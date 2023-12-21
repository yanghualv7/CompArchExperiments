#include "1-MLR.h"

int main()
{
    char binary[64]; // 增加数组大小以容纳可能的空格
    std::cout << "请输入32位二进制数(允许存在空格):" << std::endl;
    std::cin.getline(binary, 64); // 使用getline读取含空格的行

    removeSpaces(binary); // 删除所有空格

    int n = strlen(binary);
    // 浮点数
    if (n == 32) 
    {
        float floatValue = floatToValue(binary);
        std::cout << "浮点数真值为：" << floatValue << std::endl;
    }
    // 整数
    unsigned int unsignedValue = unsignedToValue(binary, n);
    std::cout << "无符号整数真值为：" << unsignedValue << std::endl;

    int intValue = intToValue(binary, n);
    std::cout << "有符号整数真值为：" << intValue << std::endl;

    system("pause");
    return 0;
}
