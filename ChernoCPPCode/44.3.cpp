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
        std::weak_ptr<Entity> e0;
        {
            std::shared_ptr<Entity> sharedEntiy = std::make_shared<Entity>();
            e0 = sharedEntiy;
        }
    }

    std::cin.get();
}