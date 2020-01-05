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

set (SRC_NAME
	Name.cpp
	Name.h
)

set (SRC_STRING_MAPPER
	StringMapper.h
)

# Target
set_library (
	${SRC_CONFIG}
	${SRC_INI}
	${SRC_NAME}
	${SRC_STRING_MAPPER}
)

# Dependencies
set_public_dependencies (BaseLibrary)

# Filters
source_group ("Config" FILES ${SRC_CONFIG})
source_group ("INI" FILES ${SRC_INI})
source_group ("Name" FILES ${SRC_NAME})
source_group ("String Mapper" FILES ${SRC_STRING_MAPPER})