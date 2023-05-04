CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/include/)

SET(CMAKE_C_FLAGS "-std=gnu11 -g -O0 -Werror")

# bridge list
ADD_EXECUTABLE(
    bridge_test_list
    list_test.c
)

TARGET_LINK_LIBRARIES(
    bridge_test_list
    bridge
    pthread
)

# bridge vector
ADD_EXECUTABLE(
    bridge_test_vector
    vector_test.c
)

TARGET_LINK_LIBRARIES(
    bridge_test_vector
    bridge
    pthread
)

# bridge pair
ADD_EXECUTABLE(
    bridge_test_pair
    pair_test.c
)

TARGET_LINK_LIBRARIES(
    bridge_test_pair
    bridge
    pthread
)

# bridge map
ADD_EXECUTABLE(
    bridge_test_map
    map_test.c
)

TARGET_LINK_LIBRARIES(
    bridge_test_map
    bridge
    pthread
)
