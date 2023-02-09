cmake_minimum_required(VERSION 3.20.0)
project(MayaGather_Debug VERSION 0.1.0)
project(MayaGather_Release VERSION 0.1.0)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
include(CTest)
enable_testing()
set(CMAKE_CXX_STANDARD 17)
#使用中文
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(MayaGather main.cpp)
target_sources(
    MayaGather 
    PUBLIC
    "src/file.h"
    "src/maya_plugin.h"
    "src/maya_plugin.cpp"
)

find_package(Boost COMPONENTS
locale
filesystem
unit_test_framework
log
log_setup
iostreams
program_options
contract
coroutine)
find_package(fmt)
#模块模式查找包(maya)
if (DEFINED Maya_Version)
    find_package(Maya ${Maya_Version} MODULE)
    find_package(OpenMP REQUIRED)
    message(STATUS "Maya found")
endif()



target_link_libraries (MayaGather Boost::filesystem)
target_link_libraries(MayaGather Boost::unit_test_framework)
target_link_libraries(MayaGather Boost::log)
target_link_libraries(MayaGather Boost::log_setup)
target_link_libraries(MayaGather Boost::iostreams)
target_link_libraries(MayaGather Boost::locale)
target_link_libraries(MayaGather Boost::program_options)
target_link_libraries(MayaGather Boost::contract)
target_link_libraries(MayaGather Boost::coroutine)
target_link_libraries(MayaGather fmt::fmt)
target_include_directories(MayaGather PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(MayaGather maya::maya_all)


include(CPack)
