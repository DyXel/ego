/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2019 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

OGL_PROC(void, glActiveTexture, (GLenum))
OGL_PROC(void, glAttachShader, (GLuint, GLuint))
OGL_PROC(void, glBindAttribLocation, (GLuint, GLuint, const char *))
OGL_PROC(void, glBindTexture, (GLenum, GLuint))
OGL_PROC(void, glBlendEquationSeparate, (GLenum, GLenum))
OGL_PROC(void, glBlendFunc, (GLenum, GLenum))
OGL_PROC(void, glBlendFuncSeparate, (GLenum, GLenum, GLenum, GLenum))
OGL_PROC(void, glClear, (GLbitfield))
OGL_PROC(void, glClearColor, (GLclampf, GLclampf, GLclampf, GLclampf))
OGL_PROC(void, glCompileShader, (GLuint))
OGL_PROC(GLuint, glCreateProgram, (void))
OGL_PROC(GLuint, glCreateShader, (GLenum))
OGL_PROC(void, glDeleteProgram, (GLuint))
OGL_PROC(void, glDeleteShader, (GLuint))
OGL_PROC(void, glDeleteTextures, (GLsizei, const GLuint *))
OGL_PROC(void, glDisable, (GLenum))
OGL_PROC(void, glDisableVertexAttribArray, (GLuint))
OGL_PROC(void, glDrawArrays, (GLenum, GLint, GLsizei))
OGL_PROC(void, glDrawElements, (GLenum, GLsizei, GLenum, const GLvoid*))
OGL_PROC(void, glEnable, (GLenum))
OGL_PROC(void, glEnableVertexAttribArray, (GLuint))
OGL_PROC(void, glFinish, (void))
OGL_PROC(void, glGenFramebuffers, (GLsizei, GLuint *))
OGL_PROC(void, glGenTextures, (GLsizei, GLuint *))
OGL_PROC(void, glGetBooleanv, (GLenum, GLboolean *))
OGL_PROC(const GLubyte *, glGetString, (GLenum))
OGL_PROC(GLenum, glGetError, (void))
OGL_PROC(void, glGetIntegerv, (GLenum, GLint *))
OGL_PROC(void, glGetProgramiv, (GLuint, GLenum, GLint *))
OGL_PROC(void, glGetShaderInfoLog, (GLuint, GLsizei, GLsizei *, char *))
OGL_PROC(void, glGetShaderiv, (GLuint, GLenum, GLint *))
OGL_PROC(GLint, glGetUniformLocation, (GLuint, const char *))
OGL_PROC(void, glLinkProgram, (GLuint))
OGL_PROC(void, glPixelStorei, (GLenum, GLint))
OGL_PROC(void, glReadPixels, (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid*))
OGL_PROC(void, glScissor, (GLint, GLint, GLsizei, GLsizei))
OGL_PROC(void, glShaderBinary, (GLsizei, const GLuint *, GLenum, const void *, GLsizei))
#if defined(__NACL__) || defined(__ANDROID__)
OGL_PROC(void, glShaderSource, (GLuint, GLsizei, const GLchar **, const GLint *))
#else
OGL_PROC(void, glShaderSource, (GLuint, GLsizei, const GLchar* const*, const GLint *))
#endif
OGL_PROC(void, glTexImage2D, (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *))
OGL_PROC(void, glTexParameteri, (GLenum, GLenum, GLint))
OGL_PROC(void, glTexParameterf, (GLenum, GLenum, GLfloat))
OGL_PROC(void, glTexSubImage2D, (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid *))
OGL_PROC(void, glUniform1f, (GLint, GLfloat))
OGL_PROC(void, glUniform1i, (GLint, GLint))
OGL_PROC(void, glUniform4f, (GLint, GLfloat, GLfloat, GLfloat, GLfloat))
OGL_PROC(void, glUniformMatrix4fv, (GLint, GLsizei, GLboolean, const GLfloat *))
OGL_PROC(void, glUseProgram, (GLuint))
OGL_PROC(void, glVertexAttribPointer, (GLuint, GLint, GLenum, GLboolean, GLsizei, const void *))
OGL_PROC(void, glViewport, (GLint, GLint, GLsizei, GLsizei))
OGL_PROC(void, glBindFramebuffer, (GLenum, GLuint))
OGL_PROC(void, glFramebufferTexture2D, (GLenum, GLenum, GLenum, GLuint, GLint))
OGL_PROC(GLenum, glCheckFramebufferStatus, (GLenum))
OGL_PROC(void, glDeleteFramebuffers, (GLsizei, const GLuint *))
OGL_PROC(GLint, glGetAttribLocation, (GLuint, const GLchar *))
OGL_PROC(void, glGetProgramInfoLog, (GLuint, GLsizei, GLsizei*, GLchar*))
OGL_PROC(void, glGenBuffers, (GLsizei, GLuint *))
OGL_PROC(void, glDeleteBuffers, (GLsizei, const GLuint *))
OGL_PROC(void, glBindBuffer, (GLenum, GLuint))
OGL_PROC(void, glBufferData, (GLenum, GLsizeiptr, const GLvoid *, GLenum))
OGL_PROC(void, glBufferSubData, (GLenum, GLintptr, GLsizeiptr, const GLvoid *))
OGL_PROC(void, glDepthFunc, (GLenum func))
OGL_PROC(void, glGenRenderbuffers, (GLsizei, GLuint *))
OGL_PROC(void, glBindRenderbuffer, (GLenum, GLuint))
OGL_PROC(void, glRenderbufferStorage, (GLenum, GLenum, GLsizei, GLsizei))
OGL_PROC(void, glFramebufferRenderbuffer, (GLenum, GLenum, GLenum, GLuint))
OGL_PROC(void, glDeleteRenderbuffers, (GLsizei, const GLuint *))
