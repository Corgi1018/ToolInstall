cmake_minimum_required(VERSION 3.20.0)
project(MayaGather_Debug VERSION 0.1.0)

include(CTest)
enable_testing()
set(CMAKE_CXX_STANDARD 17)

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
include(CPack)
