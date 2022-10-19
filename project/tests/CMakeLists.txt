FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

INCLUDE_DIRECTORIES(include)

ADD_EXECUTABLE(
        tests
        src/main.cpp
        src/utils.cpp
        src/creation_test.cpp
)
TARGET_LINK_LIBRARIES(tests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} matrix -lstdc++fs)


SET (TEST_COMMAND ${CMAKE_BINARY_DIR}/project/tests/tests)

ADD_TEST(
        NAME BaseTest
        COMMAND ${TEST_COMMAND} ${CMAKE_SOURCE_DIR}/project/tests/data --gtest_filter=-*Extra*
)

