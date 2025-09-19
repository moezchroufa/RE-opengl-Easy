## "reOpengl" : MAKE OPENGL EASY AND GREAT
( it's not perfect and missing a lot features but it's fine for me ) 

you must copy paste "reOpengl.h" and "stb_img.h"  in your project folder.
"stb_img.h" : is important to loadTextures(); if you are not gonna use them don't include it!
"test.c" is uselful as an example to start with. 

->MinGW for windows FLAGS:
-lglew32 -lglfw3 -lopengl32 -lgdi32 
"example using GCC" :

$ gcc -o test test.c -lglew32 -lglfw3 -lopengl32 -lgdi32 


NOTE : as you notice the code is influenced with C89 style
you will see me doing things like that sometimes DrawingS = {.x= , .y= } , or Vec3f ={ x ,y} , Vec3(x,y)
it's like a free style c11 c99 c89 .. 
  
-> feel free to use this or don't !
Author : moezchroufa (gWall)
