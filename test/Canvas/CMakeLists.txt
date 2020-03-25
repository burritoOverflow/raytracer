add_library(CanvasTests SHARED "")

target_sources(
  CanvasTests
  PRIVATE
    CanvasTests.cpp
)

target_link_libraries(
  CanvasTests
  PRIVATE
    Canvas
    Utility
    gmock
)
