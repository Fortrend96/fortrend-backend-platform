cmake_minimum_required(VERSION 3.25)

project(
	FortrendBackendPlatform
	VERSION 0.1.0
	LANGUAGES CXX
)

add_executable(
	fortrend_backend
	src/main.cpp
	src/core/application_config.cpp
	src/core/logger.cpp
)

target_include_directories(
	fortrend_backend
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(
	fortrend_backend
	PRIVATE
		cxx_std_23
)

set_target_properties(
	fortrend_backend
	PROPERTIES
		CXX_EXTENSIONS OFF
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_compile_options(
		fortrend_backend
		PRIVATE
			-Wall
			-Wextra
			-Wpedantic
			-Wconversion
			-Wsign-conversion
			-Wshadow
	)
endif()