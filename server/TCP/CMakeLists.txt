set_project ()

# Files
set (SRC_BASE
	TCP_Base.cpp
	TCP_Base.h
)

set (SRC_LINUX
	TCP_Linux.cpp
	TCP_Linux.h
)

set (SRC_WINDOWS
	TCP_Windows.cpp
	TCP_Windows.h
)

set (SRC
	TCP.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC_BASE}
	${SRC_LINUX}
	${SRC_WINDOWS}
	${SRC}
)

# Dependencies
set_public_dependencies (base_library)

# Filters
source_group ("Base" FILES ${SRC_BASE})
source_group ("Linux" FILES ${SRC_LINUX})
source_group ("Windows" FILES ${SRC_WINDOWS})
source_group ("" FILES ${SRC})