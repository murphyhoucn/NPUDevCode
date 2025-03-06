#include <iostream>
using namespace std;

class Log
{
public:
	const int LogLevelError = 0;
	const int LogLevelWarning = 1;
	const int LogLevelInfo = 2;
private:
	int m_LogLevel = LogLevelInfo;
public:
	void SetLevel(int level)
	{
		m_LogLevel = level;
	}

	void Error(const char* message)
	{
		if (m_LogLevel >= LogLevelError)
			cout << "[ERROR]:" << message << endl;
	}
	void Warn(const char* message)
	{
		if (m_LogLevel >= LogLevelWarning)
			cout << "[WARNING]:" << message << endl;
	}
	void Info(const char* message)
	{
		if (m_LogLevel >= LogLevelInfo)
			cout << "[INFO]:" << message << endl;
	}
};

// Log类中出现了两个public，只是因为这是一种个人的编程风格。把公共变量放在一部分，把公共方法放在一部分……

int main()
{
	Log log;

	log.SetLevel(log.LogLevelError);

	log.Error("Hello error!");
	log.Warn("Hello warning!");
	log.Info("Hello info!");

	cin.get();
}