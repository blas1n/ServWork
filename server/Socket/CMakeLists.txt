set_project ()

# Files
set (SRC_BASE_SOCKET
	BaseSocket.cpp
	BaseSocket.h
)

set (SRC_SERVER_SOCKET
	ServerSocket.cpp
	ServerSocket.h
)

set (SRC_USER_DATA
	UserData.cpp
	UserData.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC_BASE_SOCKET}
	${SRC_USER_DATA}
)

# Dependencies
set_public_dependencies (Config Exchanger)

# Filters
source_group ("Base Socket" FILES ${SRC_BASE_SOCKET})
source_group ("Server Socket" FILES ${SRC_SERVER_SOCKET})
source_group ("User Data" FILES ${SRC_USER_DATA})