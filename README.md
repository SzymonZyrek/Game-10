# Game-10 — realtime engine and rendering sandbox

> **Status:** historical / archived learning project  
> **Period:** 2014–2015  
> **Language / stack:** C++, OpenGL, GLFW, GLEW, GLM, GLSL  
> **Why this is public:** engineering archaeology — preserved as part of my portfolio rather than presented as a maintained engine.

Game-10 started when most of my software intuition was still shaped by web/application development.

I wanted to understand what changes when the system has a hard realtime-ish constraint instead of a request/response one, so I started building a small C++/OpenGL engine and repeatedly rewrote the pieces that felt wrong under a frame budget.

The useful result was not a finished game engine. It was an early lesson that **architecture follows constraints**.

At 60 FPS, one frame is roughly 16.7 ms. Suddenly things such as memory layout, predictable iteration, allocation patterns and the shape of the main loop become concrete rather than theoretical.

## What is actually in the code

### Game loop and timing

The main loop uses GLFW timing and a fixed update threshold around 60 Hz:

- frame time and delta time tracking;
- accumulator-based stepping;
- renderer update/render;
- scene update.

See [`src/GameLoop.cpp`](src/GameLoop.cpp).

### Component-oriented object model

A `GameObject` is mostly a composition point for renderable, physics, AI and input components.

See:

- [`src/GameObject.h`](src/GameObject.h)
- [`src/Component.h`](src/Component.h)

The interesting part is what happens after registration.

`Scene` stores different component types in separate arrays, keeps active entries packed toward the front, and uses object/component IDs to connect the logical object back to those arrays.

Deletion uses a swap-with-last style compaction strategy rather than leaving sparse holes.

See [`src/Scene.cpp`](src/Scene.cpp).

This is not a polished modern ECS, and I would not describe it as one. But it shows the direction I was exploring: move hot-path data away from a convenient object graph toward more predictable, type-specific storage.

There is even an old TODO in `Component.h` explicitly calling out **data locality** as the reason to remove another indirection.

That is probably the clearest little fossil in the repository showing what I was learning at the time.

### Rendering

The renderer contains the expected OpenGL machinery directly rather than hiding it behind a mature engine abstraction:

- shader programs and uniforms;
- camera/view/projection/model matrices;
- vertex, UV and normal buffers;
- indexed and non-indexed drawing;
- texture binding;
- GLFW input and context handling.

See [`src/SimpleRenderer.cpp`](src/SimpleRenderer.cpp).

### Resource pipeline

The project also grew a small asset-loading path:

- OBJ model loading;
- optional indexing;
- a binary model cache/fallback path;
- texture loading;
- GLSL shader loading and compilation.

See:

- [`src/ModelLoader.cpp`](src/ModelLoader.cpp)
- [`src/RenderableComponent.cpp`](src/RenderableComponent.cpp)
- [`src/TextureLoader.cpp`](src/TextureLoader.cpp)
- [`src/ShadersLoader.cpp`](src/ShadersLoader.cpp)

### Supporting experiments

The repository also contains side experiments that accumulated around the engine work:

- event dispatch;
- custom logging and periodic aggregation;
- configuration/resource helpers;
- a small home-grown test harness;
- remnants of both Windows/Visual Studio and Objective-C++/macOS plumbing.

That messiness is part of why I keep the repository unchanged instead of rewriting it into something more presentable.

## Why this project matters in my portfolio

Before this project, a lot of architecture looked like a collection of good practices.

Game-10 made the missing half much more obvious:

```text
constraint
   ↓
cost model
   ↓
data / control-flow shape
   ↓
architecture
```

A pattern that is perfectly reasonable in a business application may be the wrong choice inside a tight update/render loop.

That lesson carried forward into later C++ work, concurrency experiments, build tooling, runtime/framework archaeology and eventually the way I think about larger systems: abstractions are useful only as long as they still respect the physical and operational constraints underneath them.

The broader history is documented in my portfolio:

- [Engineering archaeology](https://github.com/SzymonZyrek/SzymonZyrek/blob/main/HOBBY_PROJECTS.md)
- [Project map](https://github.com/SzymonZyrek/SzymonZyrek/blob/main/PROJECTS.md)
- [Profile / portfolio entrypoint](https://github.com/SzymonZyrek)

## Historical-code disclaimer

This is old experimental code.

It contains rough edges, dead code, comments written late at night, bundled old dependencies and design choices I would not make the same way today. I am intentionally not modernizing it into a fake 2026 version of a 2014 project.

Its value is precisely that it shows the actual path: what I was trying, what constraints I had started noticing, and how the mental model was changing.
