cmake_minimum_required(VERSION 3.20.0)
project(MayaGather_Debug VERSION 0.1.0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
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
    "src/file.cpp"
    "src/file.h"
)
# target_link_libraries(MayaGather PUBLIC src) 

# target_include_directories(src PUBLIC 
#                            "${PROJECT_BINARY_DIR}" 
#                            "${PROJECT_SOURCE_DIR}/src" 
#                            ) 
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
target_link_libraries (MayaGather Boost::filesystem)
target_link_libraries(MayaGather Boost::unit_test_framework)
target_link_libraries(MayaGather Boost::log)
target_link_libraries(MayaGather Boost::log_setup)
target_link_libraries(MayaGather Boost::iostreams)
target_link_libraries(MayaGather Boost::locale)
target_link_libraries(MayaGather Boost::program_options)
target_link_libraries(MayaGather Boost::contract)
target_link_libraries(MayaGather Boost::coroutine)





include(CPack)
