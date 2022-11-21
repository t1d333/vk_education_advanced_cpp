FIND_PACKAGE(GTest REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

ADD_EXECUTABLE(
        tests
        src/main.cpp
        src/constructorstest.cpp
        src/sizetest.cpp
        src/inserttest.cpp
)
TARGET_LINK_LIBRARIES(tests ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} set -lstdc++fs)


SET (TEST_COMMAND ${CMAKE_BINARY_DIR}/project/tests/tests)

ADD_TEST(
        NAME BaseTest
        COMMAND ${TEST_COMMAND} ${CMAKE_SOURCE_DIR}/project/tests/data --gtest_filter=-*Extra*
)

