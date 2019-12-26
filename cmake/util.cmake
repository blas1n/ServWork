macro (set_project)
	get_filename_component(PROJECT_ID ${CMAKE_CURRENT_SOURCE_DIR} NAME)
	project(${PROJECT_ID})
endmacro ()

macro (set_public_dependencies)
	set_dependencies_internal(PUBLIC ${ARGN})
endmacro ()

macro (set_private_dependencies)
	set_dependencies_internal(PRIVATE ${ARGN})
endmacro ()

macro (set_dependencies_internal QUALIFIER)
	get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)

	foreach (ARG ${ARGN})
		string(REGEX REPLACE "./" "" TARGET_NAME ${ARG})
		target_link_libraries (${PROJECT_ID} ${QUALIFIER} ${TARGET_NAME})

		set (ABS_PATH ${PARENT_DIR}/${ARG})

		if (NOT EXISTS ${ABS_PATH})
			set (ABS_PATH ${CMAKE_SOURCE_DIR}/${ARG})
		endif()

		if (NOT EXISTS ${ABS_PATH})
				message (FATAL_ERROR "${ABS_PATH} does not exists.")
		endif ()

		target_include_directories (${PROJECT_ID} ${QUALIFIER} ${ABS_PATH})
	endforeach ()
endmacro ()