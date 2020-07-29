# TODO
* Fix code duplication in scene drawing
  * The draw code between scenes is the same (Scene2D and Scene3D)
  * The sorting of meshes across backends is the same (GLCore and GLES)
* Make public as much protected stuff as possible from internal class code
  * Remove trivial getters/setters
  * Make all members either public or private
  * Only leave non-virtual interface dtors on protected
* Use custom program for the purpose of blitting framebuffers on GLES
* Remove all unused GLES functions
* Add scene supersampling (SSAA)
* Build on windows for testing purposes

# Wishlist
* Separate Camera object
  * Should hold the View-Projection matrix
* Sort solid meshes on Scene3D by their material to have less program switches
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
