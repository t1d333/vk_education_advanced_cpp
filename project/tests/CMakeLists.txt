FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

ADD_EXECUTABLE(
        tests
        src/main.cpp
        src/constnesstest.cpp
        src/copy_correctness_test.cpp
        src/emptytest.cpp
        src/iterators_test.cpp
        src/destructor_test.cpp
        src/erasetest.cpp
)
TARGET_LINK_LIBRARIES(tests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} set -lstdc++fs)


SET (TEST_COMMAND ${CMAKE_BINARY_DIR}/project/tests/tests)

ADD_TEST(
        NAME BaseTest
        COMMAND ${TEST_COMMAND} ${CMAKE_SOURCE_DIR}/project/tests/data --gtest_filter=-*Extra*
)

