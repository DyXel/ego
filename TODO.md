# TODO
* Rewrite gl_include.hpp
  * Remove static usage, let the end user pass in the correct function ptrs
* Use std::array instead of normal arrays
* Fix all warnings
* Build on windows for testing purposes
* Implement GLES2
  * GLShared::Renderer can take the texture framebuffer color as ctor
    * Could also take vertex and fragment shader sources
  * Remove all unused functions

# Wishlist
* Separate Camera object
  * Should hold the View-Projection matrix
* Sort solid meshes on Scene3D by their material to have less program switches
* Add scene supersampling (SSAA)
* Use RGBA8 instead of RGBA32FLOAT for color buffer
  * Allow quick conversion between the two types
* Allow creating scene with a ITexture object
  * This texture would be used for the framebuffer instead of scene's built in
* Allow to extract pixels from a ITexture object
* Create Material object that holds the following
  * Colors buffer
  * Texture object and UVs buffer
  * Ambient light
* Expose interface for shaders, allow materials to use them instead of built-in ones
  * Allow them to be set as post-effect in the Renderer instead of built-in
