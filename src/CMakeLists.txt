set (SRC
	Base_TCP.cpp
	INI.cpp
	Linux_TCP.cpp
	main.cpp
	ThreadPool.cpp
)

include_directories (${CMAKE_SOURCE_DIR}/include)

add_executable (BS_Engine_Package_Server ${SRC})

target_link_libraries (BS_Engine_Package_Server PUBLIC ${CMAKE_THREAD_LIBS_INIT})