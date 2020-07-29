project('ego', 'cpp', default_options : 'cpp_std=c++17')

glm_dep = dependency('glm')

ego_inc = include_directories('include/')

ego_src = files([
	'src/gl_core/mesh.cpp',
	'src/gl_core/renderer.cpp',
	'src/gl_core/scene2d.cpp',
	'src/gl_core/scene3d.cpp',
	'src/gl_es/mesh.cpp',
	'src/gl_es/renderer.cpp',
	'src/gl_es/scene2d.cpp',
	'src/gl_es/scene3d.cpp',
	'src/gl_shared/cache.cpp',
	'src/gl_shared/colbuf.cpp',
	'src/gl_shared/gl_include.cpp',
	'src/gl_shared/indbuf.cpp',
	'src/gl_shared/mesh.cpp',
	'src/gl_shared/program.cpp',
	'src/gl_shared/renderer.cpp',
	'src/gl_shared/scene.cpp',
	'src/gl_shared/shader.cpp',
	'src/gl_shared/texture.cpp',
	'src/gl_shared/uvbuf.cpp',
	'src/gl_shared/vertbuf.cpp',
	'src/renderer.cpp'
])

ego_cpp_args = [
	'-DGLM_FORCE_CXX17',
	'-DGLM_FORCE_INLINE',
	'-DGLM_FORCE_PURE',
	'-DGLM_FORCE_SIZE_T_LENGTH',
	'-DGLM_ENABLE_EXPERIMENTAL'
]

ego_lib = static_library('ego', ego_src, cpp_args : ego_cpp_args, dependencies : glm_dep, include_directories : ego_inc)

ego_dep = declare_dependency(compile_args : ego_cpp_args, dependencies : glm_dep, include_directories : ego_inc, link_with : ego_lib)
