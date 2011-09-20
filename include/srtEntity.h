#ifndef H_SRT_ENTITY
#define H_SRT_ENTITY

#include "srtMaterial.h"
#include "srtShapes.h"
#include "srtDynamicArray.h"

typedef int (*srtRaycastFunctionPtr)(srtRay*, void*, srtReal*, srtVector3*, srtVector3*);

int srtSphereRaycastFunction(srtRay* r, void *sphere, srtReal *t, srtVector3 *pt, srtVector3 *normal) {
	return srtRay_Sphere(r, sphere, t, pt, normal);
}

int srtPolyRaycastFunction(srtRay *r, void *polygon, srtReal *t, srtVector3 *pt, srtVector3 *normal) {
	return srtRay_Polygon(r, polygon, t, pt, normal);
}

int srtBoxRaycastFunction(srtRay *r, void *box, srtReal *t, srtVector3 *pt, srtVector3 *normal) {
	return srtRay_Box(r, box, t, pt, normal);
}

srtRaycastFunctionPtr SRT_RAYCAST_FUNCTIONS[3] = {&srtSphereRaycastFunction, &srtPolyRaycastFunction, &srtBoxRaycastFunction};

const int SRT_SPHERE_TYPE = 0;
const int SRT_POLYGON_TYPE = 1;
const int SRT_BOX_TYPE = 2;

typedef struct {
	srtMaterial *mat;
	void *shape;
	int shapeType;
	/* pointer to custom illumination/shader method? */
} srtEntity;

srtDynamicArray* SRT_ENTITY_ARRAY;

#endif