cmake_minimum_required(VERSION 3.10)
set(TARGET_NAME UIModule)

file(GLOB LOCAL_SRCS "*.cpp" "*.h" "*.ui")
source_group("UIModule" FILES ${LOCAL_SRCS})
add_executable(UIModule ${LOCAL_SRCS})  # 如果子目录是库
