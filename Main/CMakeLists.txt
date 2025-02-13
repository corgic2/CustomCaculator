cmake_minimum_required(VERSION 3.10)
set(TARGET_NAME Main)

file(GLOB LOCAL_SRCS "*.cpp" "*.h")
source_group("Main" FILES ${LOCAL_SRCS})
add_executable(Main ${LOCAL_SRCS})  # 如果子目录是库
