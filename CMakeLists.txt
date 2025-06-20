# 指定CMake的最低版本
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(CustomCaculator)

# 设置目标名称
set(TARGET_NAME CustomCaculator)

# 设置启动项目
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CustomCaculator)

# 设置使用到的Qt模块 ------------------------------------------------------------------
set(QT_MODULES Core Gui Widgets)

# 查找 Qt 库（以 Qt5 为例）
find_package(Qt5 COMPONENTS ${QT_MODULES} REQUIRED)

# Qt，开启Qt代码自动生成
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 设置生成文件的输出目录
set(CMAKE_AUTOMOC_OUTPUT_DIR "${CMAKE_BINARY_DIR}/moc")

# 启用C++17
add_compile_options(-std=c++17)

# 解决节数超过对象文件格式限制
add_compile_options(-bigobj)

# 检测平台（x86 或 x64）
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(PLATFORM_CPU "x64")
else()
    set(PLATFORM_CPU "x86")
endif()
message(STATUS "PLATFORM_CPU: ${PLATFORM_CPU}")


# 添加VS过滤器
macro(source_group_by_dir source_files)
    if(MSVC)
        set(cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(file ${${source_files}})
            string(REGEX REPLACE ${cur_dir}/\(.*\) \\1 file_path ${file})
            string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${file_path})
            string(COMPARE EQUAL ${file_path} ${sgbd_group_name} nogroup)
            string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
            get_filename_component(file_extension ${file} EXT)
            if(file_extension STREQUAL ".ui")                   # ui文件，放Form Files
                source_group("Form Files" FILES ${file})
            elseif(file_extension STREQUAL ".qrc")
                source_group("Resource Files" FILES ${file})    # qrc文件，放Resource Files
				elseif(file_extension STREQUAL ".ts")
                source_group("Language" FILES ${file})    # qrc文件，放Language
            elseif(NOT nogroup)
                source_group(${sgbd_group_name} FILES ${file})  # 使用所在子目录名作为过滤器名
            endif()
        endforeach(file)
    endif(MSVC)
endmacro(source_group_by_dir)

# 设置输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PLATFORM_CPU})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PLATFORM_CPU})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${PLATFORM_CPU})
# 设置生成 GUI 应用程序（不显示控制台窗口）
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

# 所有源文件
file(GLOB_RECURSE SRC_FILE "*.cpp" "*.cxx" "*.cc" "*.C" "*.c++" "*.h" "*.hpp" "*.H" "*.hxx" "*.ui" "*.qrc" "*.ts")

# 排除生成的moc、qrc和ui文件
foreach(file ${SRC_FILE})
    list(APPEND TARGET_SRC ${file})
endforeach(file ${SRC_FILE})
list(FILTER TARGET_SRC EXCLUDE REGEX "moc_|qrc_|ui_")
list(FILTER TARGET_SRC EXCLUDE REGEX "build/*")

# 添加VS过滤器
source_group_by_dir(TARGET_SRC)

# 添加可执行文件
add_executable(${TARGET_NAME} ${TARGET_SRC})

# 包含目录
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

# 链接 Qt 库
target_link_libraries(${PROJECT_NAME} 
  Qt5::Core 
  Qt5::Widgets
)