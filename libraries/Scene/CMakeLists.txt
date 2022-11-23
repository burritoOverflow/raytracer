add_library(Scene STATIC "")

target_sources(
  Scene
  PRIVATE
    src/Camera.cpp
    src/Light.cpp
    src/World.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/Camera.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/Light.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/World.hpp
)

target_include_directories(
  Scene
  PUBLIC
    include
)

target_link_libraries(
  Scene
  PRIVATE
    Geometry
    Utility
    Material
  PUBLIC
    Canvas
)
