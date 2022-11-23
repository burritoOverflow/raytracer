add_library(Geometry STATIC "")

target_sources(
  Geometry
  PRIVATE
  src/Cone.cpp
  src/Cube.cpp
  src/Cylinder.cpp
  src/Intersection.cpp
  src/Plane.cpp
  src/Shape.cpp
  src/Sphere.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/Cone.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/Cube.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/Cylinder.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/Intersection.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/Plane.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/Shape.hpp
    ${CMAKE_CURRENT_LIST_DIR}/include/Sphere.hpp
)

target_include_directories(
  Geometry
  PUBLIC
    include
)

target_link_libraries(Geometry
  PRIVATE
  Utility
  PUBLIC
  Material
)
