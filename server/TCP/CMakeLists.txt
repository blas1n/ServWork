set_project ()

# Files
set (SRC
	TCP.cpp
	TCP.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC}
)

# Dependencies
set_public_dependencies (base_library)

# Filters
source_group ("" FILES ${SRC})