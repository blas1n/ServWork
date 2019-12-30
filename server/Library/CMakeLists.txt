set_project ()

# Files
set (SRC_BUFFER
	Buffer.cpp
	Buffer.h
)

set (SRC
	Core.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC_BUFFER}
	${SRC}
)

# Filters
source_group ("Buffer" FILES ${SRC_BUFFER})
source_group ("" FILES ${SRC})