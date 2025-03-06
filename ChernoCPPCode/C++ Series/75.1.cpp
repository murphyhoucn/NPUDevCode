#include <iostream>
#include <string>
#include <tuple>

std::tuple<std::string, int> CreatePerson()
{
	return{ "Cherno", 24 };
}


struct Person
{
	std::string Name;
	int Age;
};

int main()
{
	// method 1:tuple
	auto person = CreatePerson();
	std::string& name = std::get<0>(person);
	int age = std::get<1>(person);
	
	// method 2:tie
	std::string name;
	int age;
	std::tie(name, age) = CreatePerson();

	// method 3: struct
	Person person1;
	person1.Name = "Cherno";
	person1.Age = 24;
}