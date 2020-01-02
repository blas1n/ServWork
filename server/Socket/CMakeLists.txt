set_project ()

# Files
set (SRC_CLIENT_SOCKET
	ClientSocket.h
)

set (SRC_EVENT_MANAGER
	EventManager.cpp
	EventManager.h
)

set (SRC_EVENT_SOCKET
	EventSocket.cpp
	EventSocket.h
)

set (SRC_REACTOR
	Reactor.h
)

set (SRC_SERVER_SOCKET
	ServerSocket.cpp
	ServerSocket.h
)

set (SRC_SOCKET
	Socket.cpp
	Socket.h
)

set (SRC_USER_DATA
	UserData.cpp
	UserData.h
)

set (SRC
	Def.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC_CLIENT_SOCKET}
	${SRC_EVENT_MANAGER}
	${SRC_EVENT_SOCKET}
	${SRC_REACTOR}
	${SRC_SERVER_SOCKET}
	${SRC_SOCKET}
	${SRC_USER_DATA}
	${SRC}
)

# Dependencies
set_public_dependencies (Config Exchanger)

# Filters
source_group ("Client Socket" FILES ${SRC_CLIENT_SOCKET})
source_group ("Event Manager" FILES ${SRC_EVENT_MANAGER})
source_group ("Event Socket" FILES ${SRC_EVENT_SOCKET})
source_group ("Reactor" FILES ${SRC_REACTOR})
source_group ("Server Socket" FILES ${SRC_SERVER_SOCKET})
source_group ("Socket" FILES ${SRC_SOCKET})
source_group ("User Data" FILES ${SRC_USER_DATA})
source_group ("" FILES ${SRC})