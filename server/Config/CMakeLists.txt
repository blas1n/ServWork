set_project ()

# Files
set (SRC_CONFIG
	Config.cpp
	Config.h
)

set (SRC_INI
	INI.cpp
	INI.h
)

set (SRC_STRING_MAPPER
	StringMapper.cpp
	StringMapper.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC_CONFIG}
	${SRC_INI}
	${SRC_STRING_MAPPER}
)

# Dependencies
set_public_dependencies (Library)

# Filters
source_group ("Config" FILES ${SRC_CONFIG})
source_group ("INI" FILES ${SRC_INI})
source_group ("String Mapper" FILES ${SRC_STRING_MAPPER})