# usage example_add_unit_test(name srcs...)
function(example_add_unit_test name)
    cmake_parse_arguments(EXAMPLE_ADD_UNIT_TEST
        ""
        ""
        ""
        ${ARGN}
    )

    set(TEST_TARGET_NAME ${TARGET_NAME}_${name}UnitTest)

    set(TEST_TARGET_SOURCES
        main.cpp
        ${EXAMPLE_ADD_UNIT_TEST_UNPARSED_ARGUMENTS}
    )

    add_executable(${TEST_TARGET_NAME}
        ${TEST_TARGET_SOURCES}
    )

    message(STATUS Target: ${TARGET_NAME})

    target_link_libraries(${TEST_TARGET_NAME}
        PRIVATE ${TARGET_NAME}
    )
    target_link_libraries(${TEST_TARGET_NAME}
        PUBLIC fmt::fmt
    )
    target_link_libraries(${TEST_TARGET_NAME}
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
    )

    set_target_properties(${TEST_TARGET_NAME}
        PROPERTIES FOLDER test/unit
    )

    include(GoogleTest)

    gtest_discover_tests(${TEST_TARGET_NAME}
        WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
        DISCOVERY_TIMEOUT 20
        PROPERTIES
            TIMEOUT 30
        XML_OUTPUT_DIR ${CMAKE_BINARY_DIR}/test_outputs
    )
endfunction()

# automated unit tests
add_subdirectory(utilities/src)
