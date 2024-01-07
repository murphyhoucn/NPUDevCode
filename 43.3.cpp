//一段有问题的代码！！！

#include <iostream>
int* CreatedArray()
{
    int array[50];
    return array; //array的生存期仅在这个大括号之内，跳出大括号之后，array所定义的内存空间都被释放掉了，所以返回的地址也没有什么用了。
}

int main()
{
    int* a = CreatedArray();

    std::cin.get();
}