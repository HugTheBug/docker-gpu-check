cmake_minimum_required (VERSION 3.10)

project ("cpp_vulkan")

add_executable (cpp_vulkan "cpp_vulkan.cpp")
set_property(TARGET cpp_vulkan PROPERTY CXX_STANDARD 17)
add_definitions(-DVK_PROTOTYPES)

find_package(Vulkan REQUIRED FATAL_ERROR)
target_include_directories (cpp_vulkan 
    PRIVATE ${Vulkan_INCLUDE_DIRS}
)

target_link_libraries (cpp_vulkan ${Vulkan_LIBRARIES})
