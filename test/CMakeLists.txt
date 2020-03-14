add_executable(LibraryTests "")

add_subdirectory(Utility)

target_sources(
    LibraryTests
    PRIVATE
        main.cpp
)

target_link_libraries(
    LibraryTests
    PRIVATE
        Utility
        UtilityTests
        gmock
)

add_test( LibraryTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/LibraryTests)