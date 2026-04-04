cmake_minimum_required(VERSION 3.10)
project(dspTest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Экспорт команд для Zed (чтобы работало автодополнение)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(dspTest
  src/main.cpp
  src/CssWork.cpp
)

target_include_directories(dspTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
