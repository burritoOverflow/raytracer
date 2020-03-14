cmake_minimum_required(VERSION 3.15)
project(RayTracer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(ENABLE_PRECOMPILED_HEADERS OFF)

include(CTest)
enable_testing()

include_directories(
    src,
    3rdparty/stb
    3rdparty/eigen
)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(3rdparty)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
