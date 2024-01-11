#include <iostream>
#include <string>
#include <memory>

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

    void Print()
    {
        std::cout << "Hello world!" << std::endl;
    }

};

int main()
{
    {
        // method 1: 不可以！！！
        // std::unique_ptr<Entity> entity = new Entity(); // 这种写法不可以，因为unique_ptr的构造函数有explicit关键词，只能接受显式构造

        // method 2: 可以，但是因为异常安全问题，不采用这种方法！！
        // std::unique_ptr<Entity> entity(new Entity());

        // method 3: 最好的方法，因为这样做安全。
        std::unique_ptr<Entity> entity = std::make_unique<Entity>();
        entity->Print();
    }

    std::cin.get();
}

// 程序输入如下
/*
Created Entity!
Hello world!
Destoryed Entity!
*/