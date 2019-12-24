set_project ()

# Files
set (SRC_BASE
	Base_TCP.cpp
	Base_TCP.h
)

set (SRC_LINUX
	Linux_TCP.cpp
	Linux_TCP.h
)

set (SRC
	TCP.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC_BASE}
	${SRC_LINUX}
	${SRC}
)

# Dependencies
set_public_dependencies (base_library)

# Filters
source_group ("Base" FILES ${SRC_BASE})
source_group ("Linux" FILES ${SRC_LINUX})
source_group ("" FILES ${SRC})