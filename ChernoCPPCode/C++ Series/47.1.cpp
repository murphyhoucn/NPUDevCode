#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
	float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
{
	stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
	return stream;
}

int main()
{
	std::vector<Vertex> vertices;
	vertices.push_back({ 1, 2, 3 });
	vertices.push_back({ 4, 5, 6 });

	std::cout << "first" << std::endl;
	for (int i = 0; i < vertices.size(); i++)
		std::cout << vertices[i] << std::endl;

	std::cout << "second" << std::endl;
	for (Vertex& v: vertices) 
		std::cout << v << std::endl;
	// 这是一种新的写法！！

	std::cout << "third" << std::endl;
	vertices.erase(vertices.begin() + 1);

	for (Vertex& v : vertices)
		std::cout << v << std::endl;

	std::cout << "forth" << std::endl;
	vertices.clear();
	//for (vertex& v : vertices)
	//	std::cout << v << std::endl;


	std::cin.get();
}