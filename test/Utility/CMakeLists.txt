add_library( UtilityTests SHARED "")

target_sources(
    UtilityTests
    PRIVATE
        ColorTests.cpp
        PointTests.cpp
        TupleTests.cpp
        VectorTests.cpp
)

target_link_libraries(
    UtilityTests
    PRIVATE
        Utility
        gmock
)
