﻿cmake_minimum_required (VERSION 3.15)

project (StateTemplate VERSION 0.1.0 LANGUAGES CXX)

file (GLOB src src/*.cpp src/*.c)
file (GLOB include include/*.hpp include/*.h)

add_library (
	${PROJECT_NAME} SHARED
	${src}
	${include}
)
add_library (${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

find_package(Mebius REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Mebius::Mebius)
find_package(StateControllerExtension REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE StateControllerExtension::StateControllerExtension)
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".stx")

target_compile_features (${PROJECT_NAME} PRIVATE cxx_std_20)
target_compile_definitions (
	${PROJECT_NAME}
	PRIVATE
	WIN32
	_WINDOWS
	UNICODE
	_UNICODE
	$<$<CONFIG:Debug>: 
		_DEBUG
		DEBUG
	>
	$<$<CONFIG:Release>:
		NDEBUG
	>
)

target_compile_options (
	${PROJECT_NAME}
	PRIVATE
	/W4
	/arch:AVX
	/EHsc
	/fp:fast
	/GS
	/GT
	/MP
	/nologo
	/Oi
	/Qpar
	/utf-8
	$<$<CONFIG:Debug>:
		/GR
		/guard:cf
		/MDd
		/Ob0
		/Od
		/Zi
	>
	$<$<CONFIG:Release>:
		/GL
		/GR-
		/guard:cf-
		/MD
		/O2
		/Os
		/Zc:inline
	>
)
target_link_options (
	${PROJECT_NAME}
	PRIVATE
	/LTCG
	/nologo
	$<$<CONFIG:Debug>:
		/debug
		/opt:noref
	>
	$<$<CONFIG:Release>:
		/opt:ref
	>
)

target_include_directories (
	${PROJECT_NAME}
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_include_directories (
	${PROJECT_NAME}
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/share>
	$<INSTALL_INTERFACE:include>
)
