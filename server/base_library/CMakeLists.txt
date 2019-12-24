set_project ()

# Files
set (SRC_INI
	INI.cpp
	INI.h
)

set (SRC_THREAD
	ThreadAccesser.h
	ThreadPool.cpp
	ThreadPool.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC_INI}
	${SRC_THREAD}
)

# Dependencies
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries (${PROJECT_ID} PUBLIC ${CMAKE_THREAD_LIBS_INIT})
endif ()

# Filters
source_group ("INI" FILES ${SRC_INI})
source_group ("Thread" FILES ${SRC_THREAD})