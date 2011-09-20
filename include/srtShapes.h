#ifndef H_SRT_SHAPES
#define H_SRT_SHAPES

#include "srtVector.h"
#include "srtDynamicArray.h"
#include "srtMatrix.h"

typedef struct {
	srtVector3 c;
	srtReal r;
} srtSphere;

typedef struct {
	srtVector3 *v;
	int N;
	srtVector3 planeNormal;
	srtReal planeDistance;
} srtPolygon;

typedef struct {
	srtVector3 c;	/* world space center */
	srtVector3 r;   /* world space extents */
	srtMatrix44 xform;
	srtMatrix44 invTranspose;
} srtBox;

void srtPoly_Plane(srtVector3 *v, int N, srtVector3 *centroid, srtVector3 *pn, srtReal *pd) {
	srtVector3 d1 = srtVec3_Sub(&v[1], &v[0]);
	srtVector3 d2 = srtVec3_Sub(&v[N - 1], &v[0]);
	*pn = srtVec3_Cross(&d1, &d2);
	srtVec3_Normalize(pn);
	*pd = srtVec3_Dot(pn, centroid);
}

int srtTri_IsCCW(srtVector3 *a, srtVector3 *b, srtVector3 *c) {
	return ((a->x - b->x) * (b->z - c->z) - (b->x - c->x) * (a->z - b->z) < 0.0);
}

srtReal srtTri_Area(srtVector3 *v0, srtVector3 *v1, srtVector3 *v2) {
	srtVector3 d0 = srtVec3_Sub(v1, v0);
	srtVector3 d1 = srtVec3_Sub(v2, v0);
	srtVector3 r = srtVec3_Cross(&d0, &d1);
	return (srtSqrt((r.x*r.x + r.y*r.y + r.z*r.z)) * 0.5);
}

const srtReal SRT_ONE_THIRD = 1.0 / 3.0;

srtVector3 srtTri_Centroid(srtVector3 *v0, srtVector3 *v1, srtVector3 *v2) {
	srtVector3 centroid = {(v0->x + v1->x + v2->x) * SRT_ONE_THIRD, (v0->y + v1->y + v2->y) * SRT_ONE_THIRD,  (v0->z + v1->z + v2->z) * SRT_ONE_THIRD};
	return centroid;
}

srtVector3 srtPoly_Centroid(srtVector3 *v, int N) {
	int i;
	srtReal totalArea = 0.0f;
	srtVector3 centroid = SRT_VECTOR3_ZERO;
	for (i = 1; i < N - 1; ++i) {
		srtReal tarea = srtTri_Area(v, v + i, v + i + 1);
		srtVector3 tcentroid = srtTri_Centroid(v, v + i, v + i + 1);
		tcentroid = srtVec3_Mult(&tcentroid, tarea);
		centroid = srtVec3_Add(&centroid, &tcentroid);
		totalArea += tarea;
	}
	srtReal factor = 1.0 / totalArea;
	return srtVec3_Mult(&centroid, factor);
}

int srtPoly_ContainsPt(srtPolygon *p, srtVector3 *pt) {
	int low = 0, high = p->N;
	do {
		int mid = (low + high) / 2;
		if (srtTri_IsCCW(p->v, p->v + mid, pt))
			low = mid;
		else
			high = mid;
	} while (low + 1 < high);

	if (low == 0 || high == p->N)
		return 0;
	else
		return srtTri_IsCCW(p->v + low, p->v + high, pt);
}

srtDynamicArray *SRT_SPHERE_ARRAY;
srtDynamicArray *SRT_POLYGON_ARRAY;
srtDynamicArray *SRT_BOX_ARRAY;

#endif