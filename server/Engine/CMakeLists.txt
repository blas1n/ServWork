set_project ()

# Files
set (SRC
	Engine.cpp
	Engine.h
)

# Target
set_library (
	${SRC}
)

# Dependencies
set_public_dependencies (Socket)

# Filters
source_group ("" FILES ${SRC})