all:
	gcc src/raytracer.c -o bin/raytracer -I include -L lib -lmingw32 -lSDLmain -lSDL

ansi:
	gcc src/raytracer.c -o bin/raytracer -I include -L lib -lmingw32 -lSDLmain -lSDL -ansi

clean:
	del bin\raytracer.exe