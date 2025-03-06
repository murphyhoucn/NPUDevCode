//一段有问题的代码！！！

#include <iostream>
int* CreatedArray()
{
    int* array = new int[50]; // 将array定义在heap上
    return array; 
}

int main()
{
    int* a = CreatedArray();

    std::cin.get();
}