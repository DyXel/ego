# TODO
* Rename to Ego (Egoistic Graphics Orchestrator)
* Move `Drawing::Detail::I` interfaces to just `Drawing::I`
* Use RGBA8 instead of RGBA32FLOAT for color buffer
  * Allow quick conversion between the two types
* Run clang static analyzer on the entire codebase
* Add method to IRenderer to quickly retrieve a QUAD mesh data
* Use rendertargets for each scene
  * Use clear color
  * Their size will be a multiple of their viewport
  * Allow setting arbitrary supersampling on base 2
* Create Material object that holds the following
  * Colors buffer
  * Texture object and UVs buffer
  * Ambient light
* Separate Camera object
  * Should hold the View-Projection matrix

# Wishlist
* Sort meshes on the Scene3D by their material to have less program switches
