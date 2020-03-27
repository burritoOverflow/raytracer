add_library(SceneTests SHARED "")

target_sources(
  SceneTests
  PRIVATE
    LightTests.cpp
    WorldTests.cpp
)

target_link_libraries(
  SceneTests
  PRIVATE
    Geometry
    Material
    Scene
    Utility
    gmock
)
