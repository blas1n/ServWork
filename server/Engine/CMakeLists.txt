set_project ()

# Files
set (SRC
	Engine.cpp
	Engine.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC}
)

# Dependencies
set_public_dependencies (Socket)

# Filters
source_group ("" FILES ${SRC})