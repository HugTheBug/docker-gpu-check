#include <iostream>
#include <vector>
#include <string>
#include <vulkan/vulkan.h>

using namespace std;

string DeviceTypeName(const VkPhysicalDeviceType &type)
{
	switch (type)
	{
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_OTHER:
		return "Other";
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
		return "Integrated GPU";
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
		return "Discrete GPU";
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
		return "Virtual GPU";
	case VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_CPU:
		return "CPU";
	default:
		return "Unknown";
	}
}

void PrintDeviceInfo(const VkPhysicalDeviceProperties &properties)
{
	cout << "Device:" << endl;
	cout << "\t"
		 << "vendor ID: " << properties.vendorID << endl;
	cout << "\t"
		 << "device ID: " << properties.deviceID << endl;
	cout << "\t"
		 << "type: " << DeviceTypeName(properties.deviceType) << endl;
	cout << "\t"
		 << "name: " << properties.deviceName << endl;
}

bool IsGPU(const VkPhysicalDeviceType &type)
{
	return type == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU ||
		   type == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ||
		   type == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU;
}

int main()
{
	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = nullptr;
	appInfo.pApplicationName = "Where is my GPU?";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;

	std::vector<const char *> enabledExtensions = {VK_KHR_SURFACE_EXTENSION_NAME};
	createInfo.enabledExtensionCount = enabledExtensions.size();
	createInfo.ppEnabledExtensionNames = enabledExtensions.data();

	VkInstance instance;
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
	{
		cout << "Failed to create Vulkan instance." << endl;
		return 1;
	}

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	if (deviceCount)
	{
		cout << "Detected " << deviceCount << " devices " << endl;

		vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		cout << "Searching for GPUs ..." << endl;
		bool gpuDetected = false;
		for (const auto &device : devices)
		{
			VkPhysicalDeviceProperties deviceProperties;
			vkGetPhysicalDeviceProperties(device, &deviceProperties);
			if (IsGPU(deviceProperties.deviceType))
			{
				PrintDeviceInfo(deviceProperties);
				gpuDetected = true;
			}
		}
		if (!gpuDetected)
		{
			cout << "No GPUs detected." << endl;
		}
	}
	else
	{
		cout << "No devices detected, none at all." << endl;
	}

	vkDestroyInstance(instance, nullptr);
	return 0;
}
