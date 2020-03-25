add_library(UtilityTests SHARED "")

target_sources(
  UtilityTests
  PRIVATE
    ColorTests.cpp
    MatrixTests.cpp
    PointTests.cpp
    RayTests.cpp
    TupleTests.cpp
    VectorTests.cpp
)

target_link_libraries(
  UtilityTests
  PRIVATE
    Utility
    gmock
)
