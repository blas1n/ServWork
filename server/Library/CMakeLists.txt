set_project ()

# Files
set (SRC_THREAD_POOL
	ThreadPool.cpp
	ThreadPool.h
)

set (SRC
	Core.h
	Exception.h
)

# Target
set_library (
	${SRC_THREAD_POOL}
	${SRC}
)

# Dependencies
set_public_dependencies (Config)

# Filters
source_group ("Thread Pool" FILES ${SRC_THREAD_POOL})
source_group ("" FILES ${SRC})