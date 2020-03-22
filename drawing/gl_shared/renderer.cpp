#include "renderer.hpp"

#include <SDL.h>

#include "gl_include.hpp"
#include "colbuf.hpp"
#include "vertbuf.hpp"
#include "indbuf.hpp"
#include "uvbuf.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

static const GLchar* COLORED_MESH_VS_SRC =
R"(#version 100
attribute vec3 in_pos;
attribute vec4 in_color;
varying vec4 out_color;
uniform mat4 in_mvp;
void main()
{
	gl_Position = in_mvp * vec4(in_pos, 1.0);
	out_color = in_color;
})";
static const GLchar* COLORED_MESH_FS_SRC =
R"(#version 100
precision mediump float;
varying vec4 out_color; // input from vertex shader
uniform bool in_hasClipRect;
uniform vec4 in_clipRect;
void main()
{
	gl_FragColor = out_color;
})";
static const GLchar* TEXTURED_MESH_VS_SRC =
R"(#version 100
attribute vec3 in_pos;
attribute vec4 in_color;
attribute vec2 in_uv;
varying vec4 out_color;
varying vec2 out_uv;
uniform mat4 in_mvp;
void main()
{
	gl_Position = in_mvp * vec4(in_pos, 1.0);
	out_color = in_color;
	out_uv = in_uv;
})";
static const GLchar* TEXTURED_MESH_FS_SRC =
R"(#version 100
precision mediump float;
varying vec4 out_color; // input from vertex shader
varying vec2 out_uv; // input from vertex shader
uniform sampler2D in_tex;
void main()
{
	gl_FragColor = texture2D(in_tex, out_uv) + out_color;
})";

Renderer::Renderer(SDL_Window* sdlWindow) : sdlWindow(sdlWindow)
{
	// Enable additive blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	sc = std::make_shared<ShadersContainer>();
	
	{
		GLShared::Shader vs(GL_VERTEX_SHADER, COLORED_MESH_VS_SRC);
		GLShared::Shader fs(GL_FRAGMENT_SHADER, COLORED_MESH_FS_SRC);
		sc->sp1.Attach(vs);
		sc->sp1.Attach(fs);
		sc->sp1.Link();
	}
	
	{
		GLShared::Shader vs(GL_VERTEX_SHADER, TEXTURED_MESH_VS_SRC);
		GLShared::Shader fs(GL_FRAGMENT_SHADER, TEXTURED_MESH_FS_SRC);
		sc->sp2.Attach(vs);
		sc->sp2.Attach(fs);
		sc->sp2.Link();
	}
}

bool Renderer::SetVSync(VSyncState state)
{
	switch(state)
	{
		case VSyncState::VSYNC_STATE_DISABLED:
		{
			return SDL_GL_SetSwapInterval(0) == 0;
		}
		case VSyncState::VSYNC_STATE_ENABLED:
		{
			return SDL_GL_SetSwapInterval(1) == 0;
		}
		case VSyncState::VSYNC_STATE_ADAPTIVE:
		{
			return SDL_GL_SetSwapInterval(-1) == 0;
		}
	}
	return false;
}

Drawing::VertBuf Renderer::NewVertBuf(BufferHint hint)
{
	return std::make_shared<VertBuf>(hint);
}

Drawing::IndBuf Renderer::NewIndBuf(BufferHint hint)
{
	return std::make_shared<IndBuf>(hint);
}

Drawing::ColBuf Renderer::NewColBuf(BufferHint hint)
{
	return std::make_shared<ColBuf>(hint);
}

Drawing::UVBuf Renderer::NewUVBuf(BufferHint hint)
{
	return std::make_shared<UVBuf>(hint);
}

Drawing::Texture Renderer::NewTexture(const TextureCreateInfo& info)
{
	return std::make_shared<Texture>(info);
}

} // GLCore

} // Detail

} // Drawing
