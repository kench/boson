cmake_minimum_required(VERSION 3.31)

project(Boson)

include(CTest)

add_executable(boson)

target_sources(boson
  PRIVATE
    main.cc
)

add_executable(boson_test main.cc)
set(CMAKE_BUILD_TYPE "Debug")
target_compile_options(boson_test PRIVATE -coverage)
target_link_options(boson_test PRIVATE -coverage)

add_test(NAME boson COMMAND boson_test)
