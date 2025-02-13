cmake_minimum_required(VERSION 3.10)
project(CustomCaculator)
set(TARGET_NAME CustomCaculator)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CustomCaculator)

# Enable debugging symbols
set(CMAKE_BUILD_TYPE Debug)

# Add compiler flags for debugging
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# 启用C++11
add_compile_options(-std=c++11)
# 解决节数超过对象文件格式限制
add_compile_options(-bigobj)

# 是否x86 还是x64，默认x64
if(CMAKE_CL_64)
    SET(PLATFORM_CPU "x64")
else()
    SET(PLATFORM_CPU "x86")
endif()
MESSAGE(STATUS "PLATFORM_CPU: ${PLATFORM_CPU}")

# 设置输出路径
if(${PLATFORM_CPU} STREQUAL "x64")
    SET(EXECUTE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/x64/)
else()
    SET(EXECUTE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Win32/)
endif()

aux_source_directory(. DIR_SRCS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${EXECUTE_OUTPUT_PATH})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${EXECUTE_OUTPUT_PATH})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${EXECUTE_OUTPUT_PATH})

add_executable(CustomCaculator ${HEADER_FILES} ${DIR_SRCS})
