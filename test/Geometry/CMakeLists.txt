add_library( GeometryTests SHARED "")

target_sources(
  GeometryTests
  PRIVATE
    IntersectionTests.cpp
    SphereTests.cpp
)

target_link_libraries(
  GeometryTests
  PRIVATE
    Geometry
    Utility
    gmock
)
