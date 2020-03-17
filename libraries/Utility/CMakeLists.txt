add_library(Utility SHARED "")

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
    ${CMAKE_CURRENT_LIST_DIR}/include/AlmostEquals.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Color.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Matrix.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Point.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Ray.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Tuple.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Vector.h
)

target_include_directories(
  Utility
  PUBLIC
    include
)
