cmake_minimum_required(VERSION 3.10)
project(mil)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_path(BOOST_INCLUDE_DIR
        NAMES boost/beast.hpp
        PATHS /opt/homebrew/include
        /opt/homebrew/opt/boost/include
        /usr/local/include
        /usr/include
        REQUIRED
)

# Экспорт команд для Zed (чтобы работало автодополнение)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(mil
  src/main.cpp
  src/CssWork.cpp
        src/Server.cpp
        include/Server.h
)

target_include_directories(mil PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(
        mil PRIVATE
        ${BOOST_INCLUDE_DIR}
        src
)

target_link_libraries(mil
        ${Boost_LIBRARIES}
)

# Говорим Beast использовать std::error_code вместо boost::system::error_code
target_compile_definitions(mil PRIVATE
        BOOST_BEAST_USE_STD_ERIC=1
        BOOST_ASIO_USE_STD_ERIC=1
)
