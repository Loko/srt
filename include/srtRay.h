#ifndef H_SRT_RAY
#define H_SRT_RAY

#include "srtShapes.h"

typedef struct {
	srtVector3 origin;
	srtVector3 direction;
} srtRay;

/* Taken from RTCD */
int srtRay_Sphere(srtRay *r, srtSphere *s, srtReal *t, srtVector3 *pt, srtVector3 *normal) {
	srtVector3 m = srtVec3_Sub(&r->origin, &s->c);
	srtReal b = srtVec3_Dot(&m, &r->direction);
    srtReal c = srtVec3_Dot(&m, &m) - s->r * s->r;
	if (c > 0.0f && b > 0.0f)
		return 0;
	srtReal discr = b * b - c;
	
	if (discr < 0)
		return 0;
	
	/*
	discr = srtSqrt(discr);
	srtReal il = -b - discr;
	srtReal i2 = -b + discr;
	int hitVal = 0;
	if (i2 > 0) {
		if (il < 0) {
			*t = i2;
			hitVal = -1;
		} else {
			*t = il;
			hitVal = 1;
		}
		
		if (*t < 0.0f)
			*t = 0.0f;
		
		pt->x = r->direction.x * (*t) + r->origin.x;
		pt->y = r->direction.y * (*t) + r->origin.y;
		pt->z = r->direction.z * (*t) + r->origin.z;
		*normal = srtVec3_Sub(pt, &s->c);
		srtVec3_Normalize(normal);
	}
	return hitVal;
	*/
	
	*t = -b - srtSqrt(discr);
	
	if (*t < 0.0f)
		*t = 0.0f;
	
	pt->x = r->direction.x * (*t) + r->origin.x;
	pt->y = r->direction.y * (*t) + r->origin.y;
	pt->z = r->direction.z * (*t) + r->origin.z;
	*normal = srtVec3_Sub(pt, &s->c);
	srtVec3_Normalize(normal);
	return 1;
}

/* site online source here */
int srtRay_Plane(srtRay *r, srtVector3 *pn, srtReal pd, srtReal *t) {
	srtReal cosAlpha = srtVec3_Dot(&r->direction, pn);
	if (cosAlpha == 0.0) {
		return 0;
	}
	srtReal deltaD = pd - srtVec3_Dot(&r->origin, pn);
	*t = deltaD / cosAlpha;
	return (*t >= 0.0);
}


int srtRay_Polygon(srtRay *r, srtPolygon *p, srtReal *t, srtVector3 *pt, srtVector3 *normal) {
	if (srtRay_Plane(r, &p->planeNormal, p->planeDistance, t)) {
		srtVector3 length = srtVec3_Mult(&r->direction, *t);
		*pt = srtVec3_Add(&r->origin, &length);
		if (srtPoly_ContainsPt(p, pt)) {
			srtReal pDist = srtVec3_Dot(&p->planeNormal, &r->origin) + p->planeDistance;
			if (pDist >= 0.0) {
				*normal = p->planeNormal;
			} else {
				normal->x = -p->planeNormal.x;
				normal->y = -p->planeNormal.y;
				normal->z = -p->planeNormal.z;
			}
			return 1;
		}
	}
	return 0;
}

/* Used in ray OBB tests using a ray transformed into the space of the OBB */
int srtRay_AABB(srtRay *r, srtVector3 *min, srtVector3 *max, srtReal *t, srtVector3 *pt, srtVector3 *normal) {
	int inside = 1;
		
	srtReal xt, xn;
	if (r->origin.x < min->x) {
		xt = min->x - r->origin.x;
		if (xt > r->direction.x) return 0;
		xt /= r->direction.x;
		inside = 0;
		xn = -1.0f;
	} else if (r->origin.x > max->x) {
		xt = max->x - r->origin.x;
		if (xt < r->direction.x) return 0;
		xt /= r->direction.x;
		inside = 0;
		xn = 1.0f;
	} else {
		xt = -1.0f;
	}
		
	srtReal yt, yn;
	if (r->origin.y < min->y) {
		yt = min->y - r->origin.y;
		if (yt > r->direction.y) return 0;
		yt /= r->direction.y;
		inside = 0;
		yn = -1.0f;
	} else if (r->origin.y > max->y) {
		yt = max->y - r->origin.y;
		if (yt < r->direction.y) return 0;
		yt /= r->direction.y;
		inside = 0;
		yn = 1.0f;
	} else {
		yt = -1.0f;
	}
		
	srtReal zt, zn;
	if (r->origin.z < min->z) {
		zt = min->z - r->origin.z;
		if (zt > r->direction.z) return 0;
		zt /= r->direction.z;
		inside = 0;
		zn = -1.0f;
	} else if (r->origin.z > max->z) {
		zt = max->z - r->origin.z;
		if (zt < r->direction.z) return 0;
		zt /= r->direction.z;
		inside = 0;
		zn = 1.0f;
	} else {
		zt = -1.0f;
	}
	
	if (inside) {
		return 0;
	}
		
	/* determine slab normal */
	int which = 0;
	*t = xt;
	if (yt > *t) {
		which = 1;
		*t = yt;
	}
	if (zt > *t) {
		which = 2;
		*t = zt;
	}
	
	switch (which) {

		case 0: /* intersect with yz plane */
		{
			float y = r->origin.y + r->direction.y * (*t);
			if (y < min->y || y > max->y) return 0;
			float z = r->origin.z + r->direction.z * (*t);
			if (z < min->z || z > max->z) return 0;

			normal->x = xn;
			normal->y = 0.0f;
			normal->z = 0.0f;

		} break;

		case 1: /* intersect with xz plane */
		{
			float x = r->origin.x + r->direction.x * (*t);
			if (x < min->x || x > max->x) return 0;
			float z = r->origin.z + r->direction.z * (*t);
			if (z < min->z || z > max->z) return 0;

			normal->x = 0.0f;
			normal->y = yn;
			normal->z = 0.0f;

		} break;

		case 2: /* intersect with xy plane */
		{
			float x = r->origin.x + r->direction.x * (*t);
			if (x < min->x || x > max->x) return 0;
			float y = r->origin.y + r->direction.y * (*t);
			if (y < min->y || y > max->y) return 0;

			normal->x = 0.0f;
			normal->y = 0.0f;
			normal->z = zn;

		} break;
	}
	
	srtVec3_Normalize(normal);
	/**t = *t * SRT_REAL_MAX;*/
	pt->x = r->origin.x + r->direction.x * (*t);
	pt->y = r->origin.y + r->direction.y * (*t);
	pt->z = r->origin.z + r->direction.z * (*t);
	return 1;
}

/* Ray OBB test, operates on an AABB and transforms the results properly */
int srtRay_Box(srtRay *r, srtBox *b, srtReal *t, srtVector3 *pt, srtVector3 *normal) {
	
	/* local min and max */
	srtVector3 min = {-b->r.x, -b->r.y, -b->r.z};
	srtVector3 max = {b->r.x, b->r.y, b->r.z};
	
	/* transform ray into space of the aabb 
	 * use invPos and invRot for ray origin
	 * use invRotation for ray direction
	 */
	srtMatrix44 tmat;
	srtMatrix44 invPos;
	srtMat44_Translation(tmat, b->c.x, b->c.y, b->c.z);
	srtMat44_Inverse(tmat, invPos);
		
	srtVector3 to = srtMat44_Transform_Point(&r->origin, invPos);
	to = srtMat44_Transform_Point(&to, b->invTranspose);
	srtVector3 td = srtMat44_Transform_Point(&r->direction, b->invTranspose);
	
	/* currently the woo aabb algorithm needs to use non-normalized ray 
	 * directions, so an arbitrarily large number is used
	 */
	srtVector3 dmax = srtVec3_Mult(&td, 5000);
	srtRay tr = {to, dmax};
	
	/* need to transform the normals and point back to world space */
	int intersectsAABB = srtRay_AABB(&tr, &min, &max, t, pt, normal);
	if (intersectsAABB) {
		
		printf("Normal Before Transformation");
		srtVec3_Print(normal);
		printf("\n");
		/*
		srtMatrix44 reverseXform;
		
		srtMatrix44 ptTmat, rptTmat;
		srtMat44_Translation(ptTmat, pt->x, pt->y, pt->z);
		srtMat44_Translation(rptTmat, -pt->x, -pt->y, -pt->z);
		int i;
		for (i = 0; i < 16; ++i) {
			reverseXform[i] = -b->xform[i];
			reverseTmat[i] = -tmat[i];
		}*/
		/*
		srtVector3 tn = srtMat44_Transform_Point(normal, b->xform);
		normal->x = tn.x;
		normal->y = tn.y;
		normal->z = tn.z;
		
		srtMatrix44 fullTransform;
		int idx;
		for (idx = 0; idx < 12; ++idx) {
			fullTransform[idx] = b->xform[idx]; 
		}
		for (idx = 12; idx < 16; ++idx) {
			fullTransform[idx] = tmat[idx];
		}
		*/
		/*srtMat44_Add(tmat, b->xform, fullTransform);*/
		/*srtMat44_Mult(fullTransform, ptTmat, fullTransform);*/
		srtVector3 tpt =  srtMat44_Transform_Point(pt, tmat);
		tpt = srtMat44_Transform_Point(&tpt, b->xform);
		/*tpt = srtMat44_Transform_Point(&tpt, reverseXform);*/
		
		/*tpt = srtMat44_Transform_Point(&tpt, b->invTranspose);*/
		/*
		pt->x = tpt.x;
		pt->y = tpt.y;
		pt->z = tpt.z;
		*/
		/*
		pt->x = r->origin.x + r->direction.x * (*t);
		pt->y = r->origin.y + r->direction.y * (*t);
		pt->z = r->origin.z + r->direction.z * (*t);
		*/
		srtVec3_Normalize(normal);
		printf("Normal After Transformation");
		srtVec3_Print(normal);
		printf("\n");
	}
	return intersectsAABB;
}

#endif