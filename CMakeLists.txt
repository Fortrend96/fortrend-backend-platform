cmake_minimum_required(VERSION 3.25)

project(
	FortrendBackendPlatform
	VERSION 0.1.0
	LANGUAGES CXX
)

function(fortrend_enable_warnings target_name)
	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		target_compile_options(
			${target_name}
			PRIVATE
				-Wall
				-Wextra
				-Wpedantic
				-Wconversion
				-Wsign-conversion
				-Wshadow
		)
	endif()
endfunction()

function(fortrend_enable_sanitizers target_name)
	if(NOT FORTREND_ENABLE_SANITIZERS)
		return()
	endif()

	if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		message(
			FATAL_ERROR
			"Sanitizer configuration currently supports GCC only"
		)
	endif()

	target_compile_options(
		${target_name}
		PRIVATE
			-fsanitize=address,undefined
			-fno-omit-frame-pointer
			-fno-sanitize-recover=all
	)

	target_link_options(
		${target_name}
		PRIVATE
			-fsanitize=address,undefined
	)
endfunction()

add_library(
	fortrend_core
	STATIC
		src/core/application_config.cpp
		src/core/error.cpp
		src/core/logger.cpp
)

target_include_directories(
	fortrend_core
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(
	fortrend_core
	PUBLIC
		cxx_std_23
)

set_target_properties(
	fortrend_core
	PROPERTIES
		CXX_EXTENSIONS OFF
)

fortrend_enable_warnings(fortrend_core)

add_executable(
	fortrend_backend
	src/main.cpp
)

target_link_libraries(
	fortrend_backend
	PRIVATE
		fortrend_core
)

set_target_properties(
	fortrend_backend
	PROPERTIES
		CXX_EXTENSIONS OFF
)

fortrend_enable_warnings(fortrend_backend)

include(CTest)

if(BUILD_TESTING)
	include(FetchContent)

	set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
	set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG v1.18.0
		GIT_SHALLOW TRUE
	)

	FetchContent_MakeAvailable(googletest)

	add_subdirectory(tests)
endif()