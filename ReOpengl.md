# reOpenGL — Lightweight OpenGL Abstraction in C.  <br>

`reOpenGL` is a lightweight OpenGL utility and abstraction layer written in pure C. <br>
---
## Features

-  Simple initialization (`GLFW`, `GLEW`)
-  Framebuffer support (render to texture)
-  Custom shader loader & hot reloader
-  Texture loading via `stb_image`
-  Matrix transformations (Model/View/Projection)
-  Perspective and orthographic projection helpers
-  Camera view matrix (LookAt)
-  Utility wrappers for uniform uploads and vertex buffers
---
## Requirements

- C89/99/11 -compatible compiler/ 
- OpenGL 3.3+
- [GLFW](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)
- [stb_image](https://github.com/nothings/stb) (included as `stb_img.h`)
- `LAmath.h` (Custom or minimal math library for Vec3f, Mat4f, etc.) : author (gWall)

---

important flags when you compile using gcc i.e.  

```bash
gcc -o test test.c -lglfw -lGL -lGLEW -lm
```









