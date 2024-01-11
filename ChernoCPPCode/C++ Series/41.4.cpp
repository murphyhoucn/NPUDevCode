#include <iostream>
#include <string>

struct Vector2
{
	float x, y;

	Vector2(float x, float y)
		: x(x), y(y) {}

	Vector2 Add(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 operator+(const Vector2& other) const
	{
		return Add(other);
	}

	Vector2 Multiply(const Vector2& other) const
	{
		return Vector2(x * other.x, y * other.y);
	}
	Vector2 operator*(const Vector2& other) const
	{
		return Multiply(other);
	}

	bool operator==(const Vector2& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector2& other) const
	{
		return !(*this == other); // this pointer 不太懂，后面会学习
	}
};

std::ostream& operator<<(std::ostream& stream, const Vector2& other)
{
	stream << other.x << ", " << other.y;
	return stream;
}

int main()
{
	Vector2 position(4.0f, 4.0f);
	Vector2 Speed(0.5f, 1.5f);
	Vector2 Powerup(1.1f, 1.1f);

	// 没有运算符重载
	Vector2 result1 = position.Add(Speed.Multiply(Powerup));
	// 有运算符重载
	Vector2 result2 = position + Speed * Powerup;

	std::cout << result1 << std::endl;
	std::cout << result2 << std::endl;

	if (result1 == result2)
	{
		std::cout << "equality" << std::endl;
	}

	if (result1 != result2)
	{
		std::cout << "not equality" << std::endl;
	}

	std::cin.get();
}