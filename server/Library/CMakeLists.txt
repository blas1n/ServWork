set_project ()

# Files
set (SRC_BUFFER
	Buffer.cpp
	Buffer.h
)

set (SRC_NAME
	Name.cpp
	Name.h
)

set (SRC
	Core.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC_BUFFER}
	${SRC_STRING}
	${SRC}
)

# Dependencies
set_private_dependencies (Config)

# Filters
source_group ("Buffer" FILES ${SRC_BUFFER})
source_group ("Name" FILES ${SRC_NAME})
source_group ("" FILES ${SRC})