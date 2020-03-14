add_library(Canvas SHARED "")

target_sources(
  Canvas
  PRIVATE
    src/Canvas.cpp
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include/Canvas.h
)

target_include_directories(
  Canvas
  PUBLIC
    include
)

target_link_libraries(
  Canvas
  PRIVATE
    Utility
)
