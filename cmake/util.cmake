macro (set_project)
	get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
	project(${PROJECT_ID})
endmacro ()

macro (set_library)
	add_library (${PROJECT_ID} STATIC ${ARGN})
	set_target_properties (${PROJECT_ID} PROPERTIES SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endmacro ()

macro (set_public_dependencies)
	set_dependencies_internal(PUBLIC ${ARGN})
endmacro ()

macro (set_private_dependencies)
	set_dependencies_internal(PRIVATE ${ARGN})
endmacro ()

macro (set_dependencies_internal QUALIFIER)
	get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
	target_link_libraries (${PROJECT_ID} ${QUALIFIER} ${ARGN})

	foreach (ARG ${ARGN})
		get_target_property (ARG_PATH ${ARG} SOURCE_DIR)
		target_include_directories (${PROJECT_ID} ${QUALIFIER} ${QUALIFIER} ${ARG_PATH})
	endforeach ()
endmacro ()