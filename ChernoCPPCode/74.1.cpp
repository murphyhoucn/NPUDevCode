#include <iostream>
#include <memory>
#include <chrono>	
class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
public:
	Timer()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		Stop();
	}
	
	void Stop()
	{
		auto EndTimepoint = std::chrono::high_resolution_clock::now();
		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(EndTimepoint).time_since_epoch().count();

		auto duration = end - start;
		double ms = duration * 0.001;

		std::cout << duration << "us (" << ms << "ms)\n";
	}
};

int main()
{
	int value = 0;
	{
		Timer timer;

		for (int i = 0; i < 1000000; i++)
		{
			value += 2;
		}
	}
	std::cout << value << std::endl;

	__debugbreak();// VS打断点专用语法
}