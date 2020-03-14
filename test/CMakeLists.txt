set(UNIT_TEST_SOURCE_FILES
    main.cpp
)

add_executable(unitTests ${UNIT_TEST_SOURCE_FILES})

add_test(
    NAME unitTests
    COMMAND unitTests
)

target_link_libraries(unitTests PUBLIC
    gtest_main
    ${CMAKE_PROJECT_NAME}_lib
)
