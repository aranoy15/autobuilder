#add_library(lib STATIC "")

add_subdirectory(controllers)
add_subdirectory(models)

include(ExternalProject)

set(EXTERNAL_DIR ${CMAKE_BINARY_DIR}/external)

#ExternalProject_Add(jwt
#    GIT_REPOSITORY https://github.com/arun11299/cpp-jwt.git
#    PREFIX ${EXTERNAL_DIR}
#    CONFIGURE_COMMAND ""
#    BUILD_COMMAND ""
#    INSTALL_COMMAND ""
#    LOG_DOWNLOAD ON
#    GIT_PROGRESS ON
#)

ExternalProject_Add(sqlite
    GIT_REPOSITORY https://github.com/SqliteModernCpp/sqlite_modern_cpp.git
    PREFIX ${EXTERNAL_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    GIT_PROGRESS ON
)

ExternalProject_Add(luabinding
    GIT_REPOSITORY https://github.com/satoren/kaguya.git
    PREFIX ${EXTERNAL_DIR}
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    GIT_PROGRESS ON
)

add_dependencies(${TARGET} sqlite luabinding) #jwt 

target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(${TARGET} PUBLIC ${CMAKE_BINARY_DIR}/external/src/jwt/include)
target_include_directories(${TARGET} PUBLIC ${CMAKE_BINARY_DIR}/external/src/sqlite/hdr)
target_include_directories(${TARGET} PUBLIC ${CMAKE_BINARY_DIR}/external/src/luabinding/include)

