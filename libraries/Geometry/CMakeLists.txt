add_library(Geometry STATIC "")

target_sources(
  Geometry
  PRIVATE
  src/Intersection.cpp
  src/Plane.cpp
  src/Shape.cpp
  src/Sphere.cpp
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include/Intersection.h
  ${CMAKE_CURRENT_LIST_DIR}/include/Plane.h
  ${CMAKE_CURRENT_LIST_DIR}/include/Shape.h
  ${CMAKE_CURRENT_LIST_DIR}/include/Sphere.h
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
