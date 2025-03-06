// 注释来自ChatGPT

#include <iostream>
#include <string> // 包含 C 字符串处理函数所需的头文件

class String
{
private:
    char* m_Buffer;         // 存储字符串的字符数组
    unsigned int m_Size;    // 字符串的长度（不包括 null 终止符）
public:
    // 构造函数，接受一个 C 风格字符串作为参数
    String(const char* string)
    {
        m_Size = strlen(string);                     // 计算字符串的长度
        m_Buffer = new char[m_Size + 1];             // 为字符串分配内存，包括 null 终止符
        memcpy(m_Buffer, string, m_Size + 1);        // 将传入的字符串复制到 m_Buffer
    }

    // 析构函数，释放动态分配的内存
    ~String()
    {
        delete[] m_Buffer;
    }

    // 声明友元，使得重载的输出运算符能够访问类的私有成员
    friend std::ostream& operator<<(std::ostream& stream, const String& string);
};

// 重载输出运算符
std::ostream& operator<<(std::ostream& stream, const String& string)
{
    stream << string.m_Buffer;    // 将字符串输出到流
    return stream;
}

// 主函数
int main()
{
    // 创建 String 对象并初始化为 "Cherno"
    String string = "Cherno";

    // 使用重载的输出运算符输出 String 对象的内容
    std::cout << string << std::endl;

    std::cin.get();  // 等待用户输入
}