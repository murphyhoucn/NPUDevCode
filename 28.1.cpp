#include <iostream>
#include <string>
using namespace std;

class Entity
{
public:
	string GetName() { return "Entity"; }
};

class Player : public Entity
{
private:
	string m_Name;
public:
	Player(const string& name) : m_Name(name) {}

	string GetName() { return m_Name; }
};

void PrintName(Entity* entity)
{
	cout << entity->GetName() << endl;
}
int main()
{
	Entity* e = new Entity();
	PrintName(e);

	Player* p = new Player("Cherno");
	PrintName(p);

	cin.get();
}

// Entity
// Entity
