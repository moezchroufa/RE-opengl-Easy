# reOpenGL — Lightweight OpenGL Abstraction in C. <br>

## `reOpenGL` is a lightweight OpenGL utility and abstraction layer written in pure C. <br>

## Features

-  Easy window creation with GLFW
-  Texture loading using `stb_image.h`
-  3D Camera system (FPS-style)
-  Mesh abstraction with VAO/VBO support
-  Framebuffer support (offscreen rendering)
-  Input handling (keyboard + mouse)
-  Shader compilation & linking with GLSL file loading
-  Projection & View matrix utilities via [`cglm`](https://github.com/recp/cglm)

---

## Requirements

- C89/C99/C11
- OpenGL 3.3+
- [GLFW](https://www.glfw.org/)
- [GLEW](http://glew.sourceforge.net/)
- [stb_image](https://github.com/nothings/stb) (included as `stb_img.h`)
- [Deprecated] `LAmath.h` (Custom or minimal math library for Vec3f, Mat4f, etc.) : author (gWall)
-  Instead of using LAmath.h , we use cglm now! until we fix "LAmath.h"

---

important flags when you compile using gcc:  
NOTE : 
-lm : for math library needed for cglm.
-lc : links the C standard library.  

```bash
gcc -o test test.c decl_file.c -lglfw3 -lopengl32 -lGLEW32 -lm -lc
```
