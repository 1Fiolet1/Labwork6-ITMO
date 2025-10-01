cmake_minimum_required(VERSION 3.14)
project(LabWork6)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
  cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG master
)
FetchContent_MakeAvailable(cpr)


FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)


add_subdirectory(lib)


include_directories(${CMAKE_SOURCE_DIR}/lib)


set(SOURCES
    bin/main.cpp
    lib/response.cpp
    lib/json.cpp
    lib/parser.cpp
)


add_executable(LabWork6 ${SOURCES})


target_link_libraries(LabWork6 PRIVATE parser json cpr nlohmann_json::nlohmann_json)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
