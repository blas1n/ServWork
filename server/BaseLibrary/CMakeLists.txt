set_project ()

# Files
set (SRC_BUFFER
	Buffer.cpp
	Buffer.h
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
source_group ("String Translator" FILES ${SRC_STRING_TRANSLATOR})
source_group ("" FILES ${SRC})