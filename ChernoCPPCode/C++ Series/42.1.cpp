#include <iostream>

class Entity;
void PrintEntity(Entity* e);

class Entity
{
public:
    int x, y;

    Entity(int x, int y)
    {
        this->x = x;
        this->y = y;
        PrintEntity(this);
    }

    int GetX() const
    {
        // this->x = 5;
        const Entity* e = this;
        return this->x;
    }
};


void PrintEntity(Entity* e)
{
    // Print
}

int main()
{

    std::cin.get();
}