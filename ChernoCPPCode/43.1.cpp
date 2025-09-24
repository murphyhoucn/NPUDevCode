#include <iostream>
#include <string>

class Entity
{
public:
    Entity()
    {
        std::cout << "Created Entity!" << std::endl;
    }

    ~Entity()
    {
        std::cout << "Destoryed Entity!" << std::endl;
    }

};
int main()
{
    {
        Entity e; // 定义来栈上的对象
    }// e的作用域就在这个大括号之中，执行完大括号之后，就调用了析构函数。

    std::cin.get();
}

// 输入如下：
/*
Created Entity!
Destoryed Entity!
*/