#ifndef DRAWING_GL_SHARED_COMMON_HPP
#define DRAWING_GL_SHARED_COMMON_HPP
#include <glm/vec4.hpp>
#include "gl_include.hpp"
#include "../enums.hpp"
#include "../scene_createinfo.hpp"

namespace Drawing
{

namespace GLShared
{

enum Attribute
{
	ATTRIBUTE_VERTICES = 0, // Vertex positions
	ATTRIBUTE_COLORS, // Color array
	ATTRIBUTE_UVS, // Texture coordinates
	ATTRIBUTE_COUNT // Total number of attributes
};

enum Uniform
{
	UNIFORM_MVP_MAT = 0, // mat4: Model-View-Projection matrix
	UNIFORM_COUNT // Total number of uniforms
};

constexpr const char* ATTRIBUTE_NAMES[ATTRIBUTE_COUNT] =
{
	"in_pos",
	"in_color",
	"in_uv",
};

constexpr const char* UNIFORM_NAMES[UNIFORM_COUNT] =
{
	"in_mvp",
};

constexpr GLenum GLBufferHintFromEnum(BufferHint hint)
{
	if(hint == BUFFER_HINT_STREAM)
		return GL_STREAM_DRAW;
	else if(hint == BUFFER_HINT_STATIC)
		return GL_STATIC_DRAW;
	else if(hint == BUFFER_HINT_DYNAMIC)
		return GL_DYNAMIC_DRAW;
	else
		return static_cast<GLenum>(0); // Should be unreachable
}

constexpr GLfloat GLTextureFilteringFromEnum(TextureFiltering filtering)
{
	if(filtering == TEXTURE_FILTERING_NEAREST)
		return GL_NEAREST;
	else if(filtering == TEXTURE_FILTERING_LINEAR)
		return GL_LINEAR;
	else
		return static_cast<GLenum>(0); // Should be unreachable
}

constexpr GLint GLTextureWrapFromEnum(TextureWrap wrap)
{
	if(wrap == TEXTURE_WRAP_REPEAT)
		return GL_REPEAT;
	else if(wrap == TEXTURE_WRAP_MIRRORED_REPEAT)
		return GL_MIRRORED_REPEAT;
	else if(wrap == TEXTURE_WRAP_CLAMP_TO_EDGE)
		return GL_CLAMP_TO_EDGE;
	else
		return static_cast<GLenum>(0); // Should be unreachable
}

constexpr GLenum GLTopologyFromEnum(MeshTopology topology)
{
	if(topology == MESH_TOPOLOGY_POINT_LIST)
		return GL_POINTS;
	else if(topology == MESH_TOPOLOGY_LINE_LIST)
		return GL_LINES;
	else if(topology == MESH_TOPOLOGY_LINE_STRIP)
		return GL_LINE_STRIP;
	else if(topology == MESH_TOPOLOGY_TRIANGLE_LIST)
		return GL_TRIANGLES;
	else if(topology == MESH_TOPOLOGY_TRIANGLE_STRIP)
		return GL_TRIANGLE_STRIP;
	else if(topology == MESH_TOPOLOGY_TRIANGLE_FAN)
		return GL_TRIANGLE_FAN;
	else
		return static_cast<GLenum>(0); // Should be unreachable
}

constexpr GLbitfield GLClearBitsFromScenePropertyBits(uint8_t value)
{
	GLbitfield clearBits = 0;
	if(value & SCENE_PROPERTY_CLEAR_COLOR_BUFFER_BIT)
		clearBits |= GL_COLOR_BUFFER_BIT;
	if(value & SCENE_PROPERTY_CLEAR_DEPTH_BUFFER_BIT)
		clearBits |= GL_DEPTH_BUFFER_BIT;
	return clearBits;
}

} // GLShared

} // Drawing

#endif // DRAWING_GL_SHARED_COMMON_HPP
