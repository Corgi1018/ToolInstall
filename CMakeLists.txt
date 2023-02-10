cmake_minimum_required(VERSION 3.20.0)
project(MayaGather_Debug VERSION 0.1.0)
project(MayaGather_Release VERSION 0.1.0)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")
include(CTest)
enable_testing()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#生成compile_components.json (clang)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#使用中文
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_library(MayaGather SHARED main.cpp)
add_subdirectory(script/maya maya_${Maya_Version})
target_sources(
    MayaGather 
    PUBLIC
    # "src/file.h"
    "script/maya/maya_plugin.h"
    "script/maya/maya_plugin.cpp"
    # "src/maya_plugin.h"
    # "src/maya_plugin.cpp"
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
# 设置maya插件后缀名
set_target_properties(
    MayaGather PROPERTIES SUFFIX "_${Maya_Version}.mll"
)


include(CPack)
