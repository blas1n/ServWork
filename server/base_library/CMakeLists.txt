set_project ()

# Files
set (SRC
	INI.cpp
	INI.h
	ThreadPool.cpp
	ThreadPool.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC}
)

# Dependencies
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	target_link_libraries (${PROJECT_ID} PUBLIC ${CMAKE_THREAD_LIBS_INIT})
endif ()

# Filters
source_group ("" FILES ${SRC})