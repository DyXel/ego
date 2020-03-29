#include "renderer.hpp"

#include <SDL.h>

#include "colbuf.hpp"
#include "gl_include.hpp"
#include "indbuf.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "uvbuf.hpp"
#include "vertbuf.hpp"

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

Renderer::Renderer(SDL_Window* sdlWindow) : sdlWindow(sdlWindow), initialScene(nullptr)
{
	// Enable additive blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	{
		GLShared::Shader vs(GL_VERTEX_SHADER, COLORED_MESH_VS_SRC);
		GLShared::Shader fs(GL_FRAGMENT_SHADER, COLORED_MESH_FS_SRC);
		programs[PROGRAM_ONLY_COLOR].Attach(vs);
		programs[PROGRAM_ONLY_COLOR].Attach(fs);
		programs[PROGRAM_ONLY_COLOR].Link();
	}
	
	{
		GLShared::Shader vs(GL_VERTEX_SHADER, TEXTURED_MESH_VS_SRC);
		GLShared::Shader fs(GL_FRAGMENT_SHADER, TEXTURED_MESH_FS_SRC);
		programs[PROGRAM_TEXTURE_PLUS_COLOR].Attach(vs);
		programs[PROGRAM_TEXTURE_PLUS_COLOR].Attach(fs);
		programs[PROGRAM_TEXTURE_PLUS_COLOR].Link();
	}
}

const Program& Renderer::GetProgram(ProgramTypes value) const
{
	return programs[value];
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

SVertBuf Renderer::NewVertBuf(BufferHint hint)
{
	return std::make_shared<VertBuf>(hint);
}

SIndBuf Renderer::NewIndBuf(BufferHint hint)
{
	return std::make_shared<IndBuf>(hint);
}

SColBuf Renderer::NewColBuf(BufferHint hint)
{
	return std::make_shared<ColBuf>(hint);
}

SUVBuf Renderer::NewUVBuf(BufferHint hint)
{
	return std::make_shared<UVBuf>(hint);
}

STexture Renderer::NewTexture(const TextureCreateInfo& info)
{
	return std::make_shared<Texture>(info);
}

void Renderer::SetInitialScene(SScene scene)
{
	initialScene = std::dynamic_pointer_cast<Scene>(scene);
}

SScene Renderer::GetInitialScene()
{
	throw std::exception();
}

void Renderer::DrawAllScenes()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if(initialScene == nullptr)
	{
		SDL_GL_SwapWindow(sdlWindow);
		return;
	}
	
	Scene* currScene = initialScene.get();
	do
	{
		currScene->Draw();
		currScene = currScene->GetNext();
	}while(currScene != nullptr);
	
	SDL_GL_SwapWindow(sdlWindow);
}

} // GLCore

} // Detail

} // Drawing
