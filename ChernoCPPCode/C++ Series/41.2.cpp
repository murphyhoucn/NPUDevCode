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
};

int main()
{
	Vector2 position(4.0f, 4.0f);
	Vector2 Speed(0.5f, 1.5f);
	Vector2 Powerup(1.1f, 1.1f);

	// 没有运算符重载
	Vector2 result1 = position.Add(Speed.Multiply(Powerup));
	// 有运算符重载
	Vector2 result2 = position + Speed * Powerup;

	std::cin.get();
}