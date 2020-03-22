#ifndef DRAWING_SCENE_CREATEINFO_HPP
#define DRAWING_SCENE_CREATEINFO_HPP
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include "drawing.hpp"

namespace Drawing
{

// enum SceneType
// {
// // Enables backface culling, depth testing, clears on every draw and
// // optionally enables vertices msaa if msaaSamples is non-0.
// // for non-transparent meshes: sort by texture, with 0 being first (so draw non-textured first)
// // for transparent meshes: draw from back to front, with depth test still enabled
// SCENE_TYPE_3D = 0,
// // Disables backface culling, no depth testing, clears on every draw, no
// // vertices msaa.
// SCENE_TYPE_2D = 1,
// };

enum ScenePropertyBits
{
	SCENE_PROPERTY_NOTHING_BIT            = 0x00000000,
	SCENE_PROPERTY_CLEAR_DEPTH_BUFFER_BIT = 0x00000001,
	SCENE_PROPERTY_CLEAR_COLOR_BUFFER_BIT = 0x00000002,
	SCENE_PROPERTY_VERTEX_MSAA_BIT        = 0x00000004,
	SCENE_PROPERTY_CUSTOM_VIEWPORT_BIT    = 0x00000008,
// 	SCENE_PROPERTY_GAUSS_TRANSPARENCY_BIT = 0x00000010,
};

// enum ScenePropertyBits
// {
// 	SCENE_PROPERTY_BACKFACE_CULLING_BIT   = 0x00000001,
// 	SCENE_PROPERTY_ENABLE_DEPTH_TEST_BIT  = 0x00000002,
// 	SCENE_PROPERTY_CLEAR_DEPTH_BUFFER_BIT = 0x00000004,
// 	SCENE_PROPERTY_CLEAR_COLOR_BUFFER_BIT = 0x00000008,
// 	SCENE_PROPERTY_VERTEX_MSAA_BIT        = 0x00000010,
// 	SCENE_PROPERTY_CUSTOM_RECTANGLE_BIT   = 0x00000020,
// };

struct SceneCreateInfo
{
	ScenePropertyBits properties;
	// Non-mutable optional options
	glm::vec4 clearColor;
	uint8_t msaaSamples;
	// Mutable initial options
	glm::mat4 viewProj;
	glm::vec4 viewport; // x = x, y = y, z = width, w = height
	SScene next;
};

} // namespace Drawing

#endif // DRAWING_SCENE_CREATEINFO_HPP
