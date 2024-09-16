cmake_minimum_required(VERSION 3.10)
project(WeatherApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(CURL REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

include_directories(include)

add_executable(WeatherApp src/main.cpp src/Weather.cpp
        include/Weather.h)

target_link_libraries(WeatherApp CURL::libcurl JsonCpp::JsonCpp)