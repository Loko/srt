#ifndef H_SRT_BUFFER
#define H_SRT_BUFFER

#include "SDL/SDL.h"
#include "srtColor.h"
#include "srtMath.h"

#define SRT_DEFAULT_FOV 45.0
#define SRT_DEFAULT_IMAGE_PLANE_DISTANCE 1.0

int SRT_SCREEN_WIDTH;
int SRT_SCREEN_HEIGHT;
srtColor SRT_CLEAR_COLOR;
srtColor *SRT_COLOR_BUFFER;
SDL_Surface *SRT_SURFACE;

srtReal SRT_IMAGE_PLANE_WIDTH, SRT_IMAGE_PLANE_HEIGHT, SRT_IMAGE_PLANE_DISTANCE;

void srtPerspective(srtReal fovy, srtReal aspect, srtReal zDistance) {
	SRT_ASSERT_MSG(zDistance > SRT_REAL_EPSILON, "Must Have A Positive Plane Distance!");
	srtReal fovRad = degreesToRadians(fovy);
	SRT_IMAGE_PLANE_DISTANCE = zDistance;
	SRT_IMAGE_PLANE_HEIGHT = zDistance * srtTan(fovRad * 0.5);
	SRT_IMAGE_PLANE_WIDTH = SRT_IMAGE_PLANE_HEIGHT * aspect;
}

void srtClearColor4(srtReal r, srtReal g, srtReal b, srtReal a) {
	SRT_CLEAR_COLOR.r = srtClamp(r, 0.0, 1.0);
	SRT_CLEAR_COLOR.g = srtClamp(g, 0.0, 1.0);
	SRT_CLEAR_COLOR.b = srtClamp(b, 0.0, 1.0);
	SRT_CLEAR_COLOR.a = srtClamp(a, 0.0, 1.0);
}

void srtClearColor3(srtReal r, srtReal g, srtReal b) {
	srtClearColor4(r, g, b, 1.0);
}

void srtClearColor(const srtColor const *color) {
	srtClearColor4(color->r, color->g, color->b, color->a);
}

void srtPutPixel(int x, int y, srtColor *color) {
	srtColor *target;
	target = SRT_COLOR_BUFFER + (((SRT_SCREEN_HEIGHT - 1) - y) * SRT_SCREEN_WIDTH) + x;
	*target = *color;
}

srtColor * srtGetPixel(int x, int y) {
	srtColor *target;
	target = SRT_COLOR_BUFFER + (((SRT_SCREEN_HEIGHT - 1) - y) * SRT_SCREEN_WIDTH) + x;
	return target;
}

void srtClear(void) {
	int bufferSize = SRT_SCREEN_WIDTH * SRT_SCREEN_HEIGHT;
	int i;
	for (i = 0; i < bufferSize; ++i) {
		SRT_COLOR_BUFFER[i] = SRT_CLEAR_COLOR;
	}
}

void srtCreateWindow(int screenWidth, int screenHeight, char* title) {
	SRT_SCREEN_WIDTH = screenWidth;
	SRT_SCREEN_HEIGHT = screenHeight;
	 

    SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption(title, NULL);
    SRT_SURFACE = SDL_SetVideoMode(screenWidth, screenHeight, 32, SDL_SWSURFACE);
	
	SRT_COLOR_BUFFER = malloc(sizeof(srtColor) * (screenWidth * screenHeight));
	
	/* set up default perspective based on resolution */
	srtPerspective(SRT_DEFAULT_FOV, SRT_SCREEN_WIDTH / (srtReal) SRT_SCREEN_HEIGHT, SRT_DEFAULT_IMAGE_PLANE_DISTANCE);
}

void srtPaintBuffer(void) {
	int bufferSize = SRT_SCREEN_WIDTH * SRT_SCREEN_HEIGHT;
	int i;

	for (i = 0; i < bufferSize; ++i) {
		Uint32 *target;
		Uint32 col;
		col = srtColor_MapRGBA(&SRT_COLOR_BUFFER[i]);
		target = (Uint32 *)SRT_SURFACE->pixels + i;
		*target = col;
	}
}

void srtFlip(void) {
	SDL_Flip(SRT_SURFACE);
}

#endif