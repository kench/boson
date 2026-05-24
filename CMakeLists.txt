cmake_minimum_required(VERSION 3.31)

project(Boson)

find_package(nlohmann_json 3.11.3 REQUIRED)
find_package(Threads REQUIRED)
find_package(ixwebsocket CONFIG REQUIRED)

include(CTest)

add_executable(boson main.cc)

target_link_libraries(boson PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(boson PRIVATE ixwebsocket::ixwebsocket)

add_executable(boson_test main.cc)
target_link_libraries(boson_test PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(boson_test PRIVATE ixwebsocket::ixwebsocket)

set(CMAKE_BUILD_TYPE "Debug")

target_compile_options(boson_test PRIVATE -coverage)
target_link_options(boson_test PRIVATE -coverage)

add_test(NAME boson COMMAND boson_test)

add_executable(boson_json_parse_test test/json-parse.cc)
target_link_libraries(boson_json_parse_test PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(boson_json_parse_test PRIVATE ixwebsocket::ixwebsocket)

set(CMAKE_BUILD_TYPE "Debug")

target_compile_options(boson_json_parse_test PRIVATE -coverage)
target_link_options(boson_json_parse_test PRIVATE -coverage)

add_test(NAME boson_json_parse COMMAND boson_json_parse_test)

install(TARGETS boson DESTINATION bin)