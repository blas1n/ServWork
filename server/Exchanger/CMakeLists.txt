set_project ()

# Files
set (SRC_EXCHANGER
	Exchanger.cpp
	Exchanger.h
)

set (SRC_RECEIVER
	Receiver.cpp
	Receiver.h
)

set (SRC_SENDER
	Sender.cpp
	Sender.h
)

# Target
add_library (${PROJECT_ID} STATIC
	${SRC_EXCHANGER}
	${SRC_RECEIVER}
	${SRC_SENDER}
)

# Filters
source_group ("Exchanger" FILES ${SRC_EXCHANGER})
source_group ("Receiver" FILES ${SRC_RECEIVER})
source_group ("Sender" FILES ${SRC_SENDER})