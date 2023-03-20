project(g3log)


set(HEADERS
    include/g3log/log.hpp
    include/g3log/active.hpp
    include/g3log/g3log.hpp
    include/g3log/logworker.hpp
    include/g3log/shared_queue.hpp
    include/g3log/sinkwrapper.hpp
    include/g3log/stlpatch_future.hpp
    include/g3log/atomicbool.hpp
    include/g3log/filesink.hpp
    include/g3log/loglevels.hpp
    include/g3log/moveoncopy.hpp
    include/g3log/sinkhandle.hpp
    include/g3log/time.hpp
    include/g3log/crashhandler.hpp
    include/g3log/future.hpp
    include/g3log/logcapture.hpp
    include/g3log/logmessage.hpp
    include/g3log/sink.hpp
    include/g3log/rotatingfilesink.hpp
)

set(SOURCES
    filesink.cpp
    g3log.cpp
    logcapture.cpp
    loglevels.cpp
    logmessage.cpp
    logworker.cpp
    time.cpp
    rotatingfilesink.cpp

)

IF (MSVC OR MINGW)
    set(SOURCES ${SOURCES}
        crashhandler_windows.cpp
        stacktrace_windows.cpp
    )
ELSE()
set(SOURCES ${SOURCES}
    crashhandler_unix.cpp
)
ENDIF (MSVC OR MINGW)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME}
    pthread
)

IF (MSVC OR MINGW)
    target_link_libraries(${PROJECT_NAME}
        dbghelp
    )
ENDIF (MSVC OR MINGW)

target_include_directories(${PROJECT_NAME}
    PUBLIC include
    PRIVATE .                 # "dot" is redundant, because local headers are always available in C/C++.
)

