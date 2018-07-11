cmake_minimum_required(VERSION 3.3)
project(axiclient)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        axiopcjsonclient.cpp
	easylogging++.cc
	simpleclient.cpp
)

set(LIB_SRC 
	curl
	jsoncpp
	jsonrpccpp-common
	jsonrpccpp-client
	z
)

add_library(${PROJECT_NAME}_core ${SOURCE_FILES})
add_executable(${PROJECT_NAME} simpleclient.cpp)
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_core ${LIB_SRC})
