cmake_minimum_required(VERSION 3.10)

set(TARGET "server")

project(${TARGET} C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_INSTALL_RPATH "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

#Turn off U in cpprestsdk because throw conflict with rttr template parameter
add_definitions(-D_TURN_OFF_PLATFORM_STRING) 

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${TARGET} main.cpp)

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

message("Conan libs ${CONAN_LIBS}")

target_link_libraries(${TARGET} PRIVATE ${CONAN_LIBS})

add_definitions(-DCPP_JWT_USE_VENDORED_NLOHMANN_JSON)

add_subdirectory(library)
add_subdirectory(logic)
add_subdirectory(config)
