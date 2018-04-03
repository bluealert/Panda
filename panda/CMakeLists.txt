add_subdirectory(tcp)
add_subdirectory(http)
add_subdirectory(utils)
add_subdirectory(middlewares)

file(GLOB_RECURSE OperatorsHeaders operators/*.h)

add_library(panda
        ${OperatorsHeaders}
        Config.h Panda.cpp Context.cpp Router.cpp
        IOServicePool.cpp Pipeline.cpp)
target_link_libraries(panda panda_tcp panda_http panda_utils picohttpparser
        ${Boost_LIBRARIES} ${Glog_LIBRARIES} pthread)