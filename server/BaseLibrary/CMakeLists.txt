set_project ()

# Files
set (SRC_BUFFER
	Buffer.cpp
	Buffer.h
)

set (SRC_ENDIAN_TRANSLATOR
	EndianTranslator.h
)

set (SRC_STRING_TRANSLATOR
	StringTranslator.h
)

set (SRC
	Type.h
)

# Target
set_library (
	${SRC_BUFFER}
	${SRC_ENDIAN_TRANSLATOR}
	${SRC_STRING_TRANSLATOR}
	${SRC_THREAD_POOL}
	${SRC}
)

# Definitions
target_compile_definitions (${PROJECT_ID} PUBLIC
	ROOT_DIR="${CMAKE_SOURCE_DIR}/"
	CUR_DIR="${SERV_WORK_DIR}/"
)

# Filters
source_group ("Buffer" FILES ${SRC_BUFFER})
source_group ("Endian Translator" FILES ${SRC_ENDIAN_TRANSLATOR})
source_group ("String Translator" FILES ${SRC_STRING_TRANSLATOR})
source_group ("" FILES ${SRC})