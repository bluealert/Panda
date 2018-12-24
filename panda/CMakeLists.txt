file(GLOB_RECURSE OperatorsHeaders operators/*.h)

add_library(panda
        ${OperatorsHeaders}
        Config.h Panda.cpp Context.cpp Router.cpp IOServicePool.cpp Pipeline.cpp
        tcp/Acceptor.cpp tcp/Source.cpp tcp/Channel.cpp
        utils/Slice.cpp utils/Path.cpp utils/HTTP.cpp
        http/Status.cpp http/Request.cpp http/Response.cpp http/Parser11.cpp)
target_link_libraries(panda picohttpparser
        ${Boost_LIBRARIES} ${Glog_LIBRARIES} pthread)