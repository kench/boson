cmake_minimum_required(VERSION 3.31)

if (APPLE)
  set(CMAKE_OSX_ARCHITECTURES "arm64")
  set(VCPKG_OSX_ARCHITECTURES "arm64")
endif()

project(Boson LANGUAGES CXX)

find_package(nlohmann_json 3.11.3 REQUIRED)
find_package(Threads REQUIRED)
find_package(ixwebsocket CONFIG REQUIRED)
find_package(SDL3 3.4.4 REQUIRED)
find_package(OpenXR CONFIG REQUIRED)

if(WIN32)
find_package(Spout2 CONFIG REQUIRED)
endif()

include(CTest)

if (APPLE)
  set(APP_SOURCES src/main.cc src/main-sdl.cc)
  set(APP_RESOURCES resources/macos/Boson.icns)
  add_executable(Boson MACOSX_BUNDLE
    ${APP_SOURCES}
    ${APP_RESOURCES}
  )
  set_target_properties(Boson PROPERTIES
    MACOSX_BUNDLE_TRUE ON
    MACOSX_BUNDLE_INFO_PLIST "resources/macos/Info.plist"
    RESOURCE "${APP_RESOURCES}"
  )
  set(MACOSX_BUNDLE_BUNDLE_NAME "Boson")
  set(MACOSX_BUNDLE_GUI_IDENTIFIER "tv.kenley.boson.Boson")
  set(MACOSX_BUNDLE_BUNDLE_VERSION "0.0.1")
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0")
  set(MACOSX_BUNDLE_LONG_VERSION_STRING "Boson 0.0.1")
  set(MACOSX_BUNDLE_COPYRIGHT "Copyright © 2026 Kenley Cheung")
  set(MACOSX_BUNDLE_ICON_FILE "Boson.icns")

  target_link_libraries(Boson PRIVATE nlohmann_json::nlohmann_json)
  target_link_libraries(Boson PRIVATE ixwebsocket::ixwebsocket)
  target_link_libraries(Boson PRIVATE OpenXR::headers OpenXR::openxr_loader)

  find_library(SDL3_FRAMEWORK
    NAMES SDL3
    PATHS "~/Library/Frameworks"
  )

  if(NOT SDL3_FRAMEWORK)
    message(FATAL_ERROR "SDL3.framework could not be found!")
  else()
    message(STATUS "Using SDL3_FRAMEWORK at: ${SDL3_FRAMEWORK}")
  endif()

  set_source_files_properties("${SDL3_FRAMEWORK}" PROPERTIES
    MACOSX_PACKAGE_LOCATION Frameworks
  )
  target_sources(Boson PRIVATE "${SDL3_FRAMEWORK}")
  target_link_libraries(Boson PRIVATE ${SDL3_FRAMEWORK})
  target_include_directories(Boson PRIVATE ${SDL3_FRAMEWORK}/Headers)

  set_target_properties(Boson PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "@executable_path/../Frameworks"
  )
else()
  add_executable(boson src/main.cc src/main-sdl.cc)
  target_link_libraries(boson PRIVATE nlohmann_json::nlohmann_json)
  target_link_libraries(boson PRIVATE ixwebsocket::ixwebsocket)
  target_link_libraries(boson PRIVATE SDL3::SDL3)
  if(WIN32)
  target_link_libraries(boson PRIVATE Spout2::Spout)
  target_link_libraries(boson PRIVATE Spout2::SpoutDX)
  endif()

  add_executable(boson_test src/main.cc src/main-sdl.cc)

  target_link_libraries(boson_test PRIVATE nlohmann_json::nlohmann_json)
  target_link_libraries(boson_test PRIVATE ixwebsocket::ixwebsocket)
  target_link_libraries(boson_test PRIVATE SDL3::SDL3)
  if(WIN32)
  target_link_libraries(boson_test PRIVATE Spout2::Spout)
  target_link_libraries(boson_test PRIVATE Spout2::SpoutDX)
  endif()
  target_compile_options(boson_test PRIVATE -coverage)
  target_link_options(boson_test PRIVATE -coverage)

  add_test(NAME boson COMMAND boson_test)

  add_executable(boson_json_parse_test test/json-parse.cc)
  target_link_libraries(boson_json_parse_test PRIVATE nlohmann_json::nlohmann_json)
  target_link_libraries(boson_json_parse_test PRIVATE ixwebsocket::ixwebsocket)
  target_compile_options(boson_json_parse_test PRIVATE -coverage)
  target_link_options(boson_json_parse_test PRIVATE -coverage)

  add_test(NAME boson_json_parse COMMAND boson_json_parse_test)

  install(TARGETS boson DESTINATION bin)
endif()

