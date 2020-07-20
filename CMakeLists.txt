cmake_minimum_required(VERSION 3.12.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# This project is strictly C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ensure CMAKE_BUILD_TYPE is set correctly.
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set up project and executable
project(drawing2-test C CXX)
add_executable(drawing2-test)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	PROPERTY VS_STARTUP_PROJECT "drawing2-test"
)

find_package(glm REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Add libraries from dependencies to executable
target_link_libraries(drawing2-test PRIVATE
	SDL2::Main
	SDL2::Image
	glm
)

# Add compiler definitions to executable
target_compile_definitions(drawing2-test PUBLIC
	GLM_FORCE_CXX17
	GLM_FORCE_INLINE
	GLM_FORCE_SIZE_T_LENGTH
	GLM_FORCE_INTRINSICS
	GLM_ENABLE_EXPERIMENTAL
)

# Add compiler flags to executable
set(CLANG_OR_GNU $<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>)
target_compile_options(drawing2-test PRIVATE
	# Clang and GNU compilers
	$<${CLANG_OR_GNU}:-Wall -Wextra -pedantic>
	$<$<AND:$<CONFIG:Debug>,${CLANG_OR_GNU}>:-ggdb3 -O0 -D_DEBUG>
	$<$<AND:$<CONFIG:Release>,${CLANG_OR_GNU}>:-Ofast>
	$<$<AND:$<CONFIG:RelWithDebInfo>,${CLANG_OR_GNU}>:-ggdb3 -Ofast -D_DEBUG>
	# Microsoft compiler
	$<$<CXX_COMPILER_ID:MSVC>:/W4>
)

# Source files
set(CSR ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(drawing2-test PRIVATE
	${CSR}/game_instance.cpp
	${CSR}/game_instance.hpp
	${CSR}/main.cpp
	${CSR}/sdl_utility.cpp
	${CSR}/sdl_utility.hpp
	${CSR}/drawing/sdlwindow.cpp
	${CSR}/drawing/sdlwindow.hpp
	${CSR}/drawing/gl_core/mesh.cpp
	${CSR}/drawing/gl_core/mesh.hpp
	${CSR}/drawing/gl_core/renderer.cpp
	${CSR}/drawing/gl_core/renderer.hpp
# 	${CSR}/drawing/gl_core/scene.cpp
# 	${CSR}/drawing/gl_core/scene.hpp
	${CSR}/drawing/gl_core/scene2d.cpp
	${CSR}/drawing/gl_core/scene2d.hpp
	${CSR}/drawing/gl_core/scene3d.cpp
	${CSR}/drawing/gl_core/scene3d.hpp
# 	${CSR}/drawing/gl_es/renderer.cpp
# 	${CSR}/drawing/gl_es/renderer.hpp
	${CSR}/drawing/gl_shared/cache.cpp
	${CSR}/drawing/gl_shared/cache.hpp
	${CSR}/drawing/gl_shared/colbuf.cpp
	${CSR}/drawing/gl_shared/colbuf.hpp
	${CSR}/drawing/gl_shared/common.hpp
	${CSR}/drawing/gl_shared/gl_core_funcs.inl
	${CSR}/drawing/gl_shared/gl_es2_funcs.inl
	${CSR}/drawing/gl_shared/gl_include_defines.h
	${CSR}/drawing/gl_shared/gl_include.cpp
	${CSR}/drawing/gl_shared/gl_include.hpp
	${CSR}/drawing/gl_shared/indbuf.cpp
	${CSR}/drawing/gl_shared/indbuf.hpp
	${CSR}/drawing/gl_shared/mesh.cpp
	${CSR}/drawing/gl_shared/mesh.hpp
	${CSR}/drawing/gl_shared/program.cpp
	${CSR}/drawing/gl_shared/program.hpp
	${CSR}/drawing/gl_shared/renderer.cpp
	${CSR}/drawing/gl_shared/renderer.hpp
	${CSR}/drawing/gl_shared/scene.cpp
	${CSR}/drawing/gl_shared/scene.hpp
	${CSR}/drawing/gl_shared/shader.cpp
	${CSR}/drawing/gl_shared/shader.hpp
	${CSR}/drawing/gl_shared/uvbuf.cpp
	${CSR}/drawing/gl_shared/uvbuf.hpp
	${CSR}/drawing/gl_shared/vertbuf.cpp
	${CSR}/drawing/gl_shared/vertbuf.hpp
	${CSR}/drawing/gl_shared/texture.cpp
	${CSR}/drawing/gl_shared/texture.hpp
)
unset(CSR)
