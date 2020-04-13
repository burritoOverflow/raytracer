add_library(MaterialTests SHARED "")

target_sources(
  MaterialTests
  PRIVATE
    MaterialTests.cpp
)

target_link_libraries(
  MaterialTests
  PRIVATE
    Material
    Pattern
    Scene
    Utility
    gmock
)
