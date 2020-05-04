#add_library(logic STATIC "")

add_subdirectory(controllers)
add_subdirectory(utils)

#target_include_directories(${TARGET} PRIVATE ${CMAKE_SOURCE_DIR})
#target_link_libraries(logic cpprestsdk::cpprest ${Boost_LIBRARIES}) #lib