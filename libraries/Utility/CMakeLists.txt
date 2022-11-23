add_library(Utility STATIC "")

target_sources(
  Utility
  PRIVATE
  src/Color.cpp
  src/Matrix.cpp
  src/Point.cpp
  src/Ray.cpp
  src/Tuple.cpp
  src/Vector.cpp
  PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/include/AlmostEquals.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/Color.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/Matrix.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/Point.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/Ray.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/Tuple.hpp
  ${CMAKE_CURRENT_LIST_DIR}/include/Vector.hpp
)

target_include_directories(
  Utility
  PUBLIC
  include
)
