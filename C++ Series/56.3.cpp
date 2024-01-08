#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Device {};

class DeviceManager
{
private:
	std::unordered_map<std::string, std::vector<Device*>> m_Devices;
public:
	const std::unordered_map<std::string, std::vector<Device*>>& GetDevice() const
	{
		return m_Devices;
	}
};

int main()
{
	DeviceManager dm;

	// const std::unordered_map<std::string, std::vector<Device*>>& devices = dm.GetDevice();
    
    // 使用alias
    using DeviceMap = std::unordered_map<std::string, std::vector<Device*>>;
    typedef std::unordered_map<std::string, std::vector<Device*>> DeviceMap;
    const DeviceMap& devices = dm.GetDevice();
    
    // 使用auto
	const auto& devices = dm.GetDevice();

	std::cin.get();
}