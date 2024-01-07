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

class ScopePtr
{
private:
    Entity* m_Ptr;
public:
    ScopePtr(Entity* ptr)
        : m_Ptr(ptr) {}

    ~ScopePtr()
    {
        delete m_Ptr;
    }
};

int main()
{
    {
        ScopePtr e = new Entity();
    }

    std::cin.get();
}

// 输入如下：
/*
Created Entity!
Destoryed Entity!
*/

// 对象定义在heap上,但是我们通过ScopePtr来实现了new-delete, 在跳出大括号的时候,自动调用delete了．