set_project ()

# Files
set (SRC_BUFFER
	Buffer.h
)

set (SRC_EXCEPTION
	Exception.h
)

set (SRC_NAME
	Name.cpp
	Name.h
)

set (SRC_STRING_TRANSLATOR
	StringTranslator.h
)

set (SRC_THREAD_POOL
	ThreadAccesser.h
	ThreadPool.cpp
	ThreadPool.h
)

set (SRC
	Core.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC_BUFFER}
	${SRC_EXCEPTION}
	${SRC_NAME}
	${SRC_STRING_TRANSLATOR}
	${SRC_THREAD_POOL}
	${SRC}
)

# Dependencies
set_private_dependencies (Config)

# Filters
source_group ("Buffer" FILES ${SRC_BUFFER})
source_group ("Exception" FILES ${SRC_EXCEPTION})
source_group ("Name" FILES ${SRC_NAME})
source_group ("String Translator" FILES ${SRC_STRING_TRANSLATOR})
source_group ("Thread Pool" FILES ${SRC_THREAD_POOL})
source_group ("" FILES ${SRC})