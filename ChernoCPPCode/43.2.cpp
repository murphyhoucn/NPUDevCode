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
        Entity* e = new Entity(); 
    }//定义在heap上的对象，如果不使用delete手动释放内存空间则该内存空间就不会被释放，因此没有调用析构函数。

    std::cin.get();
}

// 输入如下：
/*
Created Entity!
*/