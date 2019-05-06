# Viewer

Central viewer managing window, controllers, animations, and main loop.

## Enum class: OGLProfile

Profile definitions for OGLConfig

```cpp
enum class OGLProfile: int {
  NONE = 0,
  CORE = GLFW_OPENGL_CORE_PROFILE,
  COMPATIBILITY = GLFW_OPENGL_COMPAT_PROFILE
};
```

## Struct: OGLConfig

OpenGL configuration, may be set by user before calling Viewer::init().
 * Default parameters:
   - OpenGL 3.2
   - forward-compatible context
   - core profile
   - bright gray background color

## Struct: FrameBufferSize

Frame buffer size, to be set by renderer in Renderer::initViewer(), called by Viewer::init().

 * Default parameters:
   - RGBA channels: 8 bit each
   - depth buffer: 24 bit
   - stencil buffer: 8 bit

## Class: Viewer

Central viewer managing window, controllers, animations, and main loop. A few static functions are required for GLFW callbacks.

## create()

* `return` {ViewerSP}

Create shared pointer

## init(renderer)

* `renderer` {RendererSP}
* `return` {[Viewer][]*} This pointer for method chaining

Initialize GLFW with given renderer

## initSimpleRenderer(camera, scene)

* `camera` {CameraSP&} Unallocated pointer
* `scene` {GrouSP&} Unallocated pointer
* `return` {[Viewer][]*} This pointer for method chaining

Initialize viewer with default renderer, Gouraud shader, perspective camera, and empty scene (with child node camera)

## initSimpleRenderer(camera, scene, light)

* `camera` {CameraSP&} Unallocated pointer
* `scene` {GroupSP&} Unallocated pointer
* `light` {LightSP&} Unallocated pointer
* `return` {[Viewer][]*} This pointer for method chaining

Initialize viewer with default renderer, Gouraud shader, perspective camera, directed light, and empty scene (with child nodes camera and light

## setOpenGLConfig(oglConfig)

* `oglConfig` {OGLConfig&}
* `return` {[Viewer][]*} This pointer for method chaining

Set OpenGL configuration. In order to take effect, this method has to be called before init().

## addController(controller)

* `controller` {ControllerSP}
* `return` {[Viewer][]*} This pointer for method chaining

Add controller to be checked in main loop, e.g., a camera controller

## addControllers(controllers)

* `controllers` {std::vector\<ControllerSP>&}
* `return` {[Viewer][]*} This pointer for method chaining

Add controllers to be checked in main loop, e.g., a camera controller

## addControllers(controllers)

* `controllers` {std::vector\<ControllerSP>&&}
* `return` {[Viewer][]*} This pointer for method chaining

Add controllers to be checked in main loop, e.g., a camera controller

## addAnimation(animation)

* `animation` {AnimationSP}
* `return` {[Viewer][]*} This pointer for method chaining

Add animation to be updated in main loop

## addAnimations(animations)

* `animations` {std::vector\<AnimationSP>&}
* `return` {[Viewer][]*} This pointer for method chaining

Add animations to be updated in main loop

## addAnimations(animations)

* `animations` {std::vector\<AnimationSP>&&}
* `return` {[Viewer][]*} This pointer for method chaining

Add animations to be updated in main loop

## startAnimations()

* `return` {[Viewer][]*} This pointer for method chaining

Start all animations

## getWindowSize(width, height)

* `width` {int&}
* `height` {int&}

Get current window dimensions

## setWindowSize(width, height)

* `width` {int}
* `height` {int}
* `return` {[Viewer][]*} This pointer for method chaining

Set window dimensions

## isWindowResized()

* `return` {bool}

Check if window has been resized since last call of this method. The internal resize flag is cleared afterwards.

## setWindowTitle(title)

* `title` {char*}
* `return` {[Viewer][]*} This pointer for method chaining

Set window title

## createWindow(title, width, height)

* `title` {char*}
* `width` {int}
* `height` {int}
* `return` {[Viewer][]*} This pointer for method chaining

Create OpenGL context, open window with given title and dimensions, and initialize GLEW

## createFullscreenWindow(title)

* `title` {char*}
* `return` {[Viewer][]*} This pointer for method chaining

Create OpenGL context, open fullscreen window with given title, hide mouse cursor, and initialize GLEW

## startMainLoop()

Start main loop, periodically check input devices and render scene


[Viewer]: https://github.com/VoltanaDMG/scg3_v2019/blob/v2019.x/scg3/doc/api/viewer.md