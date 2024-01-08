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
        // method 1: 不可以！因为shared_ptr需要分配控制块来存储引用计数。
        // std::shared_ptr<Entity> sharedEntity(new Entity());

        // method 2: 使用这样方法！
        std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
        std::shared_ptr<Entity> e0 = sharedEntity;
    }

    std::cin.get();
}