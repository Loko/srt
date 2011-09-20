#ifndef H_SRT_LIGHTING
#define H_SRT_LIGHTING

#include "srtVector.h"
#include "srtColor.h"

/* Implement later */
int SRT_LIGHT0 = 0;
int SRT_LIGHT1 = 1;
int SRT_LIGHT2 = 2;
int SRT_LIGHT3 = 3;
int SRT_LIGHT4 = 4;

int SRT_NUM_ACTIVE_LIGHTS = 0;

typedef struct {
	int enabled;
	srtColor ambient, diffuse, specular;
	/* ambient, diffuse, specular */
} srtLight;

int SRT_LIGHTING_ENABLED = 0;
srtColor SRT_LIGHT_AMBIENT, SRT_LIGHT_DIFFUSE, SRT_LIGHT_SPECULAR;
srtVector3 SRT_LIGHT_POSITION;

void srtLightingEnabled(int enabled) {
	SRT_LIGHTING_ENABLED = enabled;
}

/* these should all take the index of the light */
void srtLightPosition3(srtReal x, srtReal y, srtReal z) {
	SRT_LIGHT_POSITION.x = x;
	SRT_LIGHT_POSITION.y = y;
	SRT_LIGHT_POSITION.z = z;
}

void srtLightPosition(const srtVector3 * const position) {
	SRT_LIGHT_POSITION.x = position->x;
	SRT_LIGHT_POSITION.y = position->y;
	SRT_LIGHT_POSITION.z = position->z;
}

void srtLightAmbient4(srtReal r, srtReal g, srtReal b, srtReal a) {
	SRT_LIGHT_AMBIENT.a = a;
	SRT_LIGHT_AMBIENT.r = r;
	SRT_LIGHT_AMBIENT.g = g;
	SRT_LIGHT_AMBIENT.b = b;
}

void srtLightAmbient(const srtColor * const color) {
	SRT_LIGHT_AMBIENT.a = color->a;
	SRT_LIGHT_AMBIENT.r = color->r;
	SRT_LIGHT_AMBIENT.g = color->g;
	SRT_LIGHT_AMBIENT.b = color->a;
}

void srtLightDiffuse4(srtReal r, srtReal g, srtReal b, srtReal a) {
	SRT_LIGHT_DIFFUSE.a = a;
	SRT_LIGHT_DIFFUSE.r = r;
	SRT_LIGHT_DIFFUSE.g = g;
	SRT_LIGHT_DIFFUSE.b = b;
}

void srtLightSpecular4(srtReal r, srtReal g, srtReal b, srtReal a) {
	SRT_LIGHT_SPECULAR.a = a;
	SRT_LIGHT_SPECULAR.r = r;
	SRT_LIGHT_SPECULAR.g = g;
	SRT_LIGHT_SPECULAR.b = b;
}
#endif