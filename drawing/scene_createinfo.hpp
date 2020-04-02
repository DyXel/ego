#ifndef DRAWING_SCENE_CREATEINFO_HPP
#define DRAWING_SCENE_CREATEINFO_HPP
#include <glm/mat4x4.hpp>
#include <glm/ext/vector_int4.hpp>

#include "drawing.hpp"

namespace Ego
{

enum ScenePropertyBits : uint8_t
{
	SCENE_PROPERTY_NOTHING_BIT            = 0x00000000,
	SCENE_PROPERTY_CLEAR_COLOR_BUFFER_BIT = 0x00000001,
	SCENE_PROPERTY_CLEAR_DEPTH_BUFFER_BIT = 0x00000002,
	SCENE_PROPERTY_ENABLE_DEPTH_TEST_BIT  = 0x00000004,
	SCENE_PROPERTY_BACKFACE_CULLING_BIT   = 0x00000008,
	SCENE_PROPERTY_VERTEX_MSAA_BIT        = 0x00000010,
};

struct SceneCreateInfo
{
	uint8_t properties; // values of ScenePropertyBits OR'd
	// Non-mutable optional options
	glm::vec4 clearColor;
	// Mutable initial options
	glm::mat4 viewProj;
	glm::ivec4 viewport; // x = x, y = y, z = width, w = height
	SScene next;
};

} // namespace Ego

#endif // DRAWING_SCENE_CREATEINFO_HPP
