add_library(SceneTests SHARED "")

target_sources(
  SceneTests
  PRIVATE
    LightTests.cpp
)

target_link_libraries(
  SceneTests
  PRIVATE
    Material
    Scene
    Utility
    gmock
)
