cmake_minimum_required(VERSION 3.25)

project(
	FortrendBackendPlatform
	VERSION 0.1.0
	LANGUAGES CXX
)

add_executable(
	fortrend_backend
	src/main.cpp
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

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
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
elseif(MSVC)
	target_compile_options(
		fortrend_backend
		PRIVATE
			/W4
			/permissive-
	)
endif()