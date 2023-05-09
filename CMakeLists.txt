PROJECT(bridge)
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_C_FLAGS "-std=gnu11 -g -O0 -Werror  -fPIC -Wall -Wno-unused-function -Wno-unused-value \
 -Wno-unused-variable -fno-strict-aliasing -fwrapv")

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/ ${PROJECT_SOURCE_DIR}/include/)

AUX_SOURCE_DIRECTORY(./src/. DIR_SOURCE)

ADD_LIBRARY(bridge SHARED ${DIR_SOURCE})

TARGET_INCLUDE_DIRECTORIES(bridge
    INTERFACE . include
)

ADD_SUBDIRECTORY(test)
