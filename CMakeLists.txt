cmake_minimum_required(VERSION 3.21)

project(RayTracer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(ENABLE_PRECOMPILED_HEADERS OFF)

include(CTest)
include(GoogleTest)
enable_testing()

add_subdirectory(3rdparty)
add_subdirectory(libraries)
add_subdirectory(app)
add_subdirectory(test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
