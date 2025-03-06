#include <iostream>
#include <string>
using namespace std;

class Printable
{
public:
	virtual string GetClassName() = 0;  // pure virtual function
};

class Entity : public Printable
{
public:
	virtual string GetName() { return "Entity"; }
	string GetClassName() override { return "Entity"; }
};

class Player : public Entity
{
private:
	string m_Name;
public:
	Player(const string& name) : m_Name(name) {}

	string GetName() override { return m_Name; }
	string GetClassName() override { return "Palyer"; }
};

void PrintName(Entity* entity)
{
	cout << entity->GetName() << endl;
}

void Print(Printable* obj)
{
	cout << obj->GetClassName() << endl;
}

int main()
{
	Entity* e = new Entity();
	// PrintName(e);

	Player* p = new Player("Cherno");
	// PrintName(p);

	Print(e);
	Print(p);

	cin.get();
}