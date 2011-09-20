#ifndef H_SRT_SCENE
#define H_SRT_SCENE

#include "srtEntity.h"
#include "srtLighting.h"
#include "srtAssert.h"
#include "srtMatrix.h"
#include "srtMaterial.h"



const int SRT_BEGUN_STATE = 1;
const int SRT_ENDED_STATE = 0;
int SRT_SCENE_STATE = 0;

void srtBeginScene(void) {
	SRT_ASSERT_MSG(SRT_SCENE_STATE == SRT_ENDED_STATE, "Scene already in begin state!");
	SRT_SCENE_STATE = SRT_BEGUN_STATE;
	
	/* reset materials */
	srtMatReset();
	srtDynamicArray_Delete(SRT_MATERIAL_ARRAY);
	SRT_MATERIAL_ARRAY = srtDynamicArray_Create(4);
	
	void *defMatPtr = malloc(sizeof(srtMaterial));
	defMatPtr = (void *)&SRT_DEFAULT_MATERIAL;  
	srtDynamicArray_PushBack(SRT_MATERIAL_ARRAY, defMatPtr);
	
	/* reset shapes */
	srtDynamicArray_Delete(SRT_SPHERE_ARRAY);
	SRT_SPHERE_ARRAY = srtDynamicArray_Create(4);
	
	srtDynamicArray_Delete(SRT_POLYGON_ARRAY);
	SRT_POLYGON_ARRAY = srtDynamicArray_Create(4);
	
	srtDynamicArray_Delete(SRT_BOX_ARRAY);
	SRT_BOX_ARRAY = srtDynamicArray_Create(4);
	
	/* reset entities */
	srtDynamicArray_Delete(SRT_ENTITY_ARRAY);
	SRT_ENTITY_ARRAY = srtDynamicArray_Create(4);
}

void srtEndScene(void) {
	SRT_ASSERT_MSG(SRT_SCENE_STATE == SRT_BEGUN_STATE, "Scene already in end state!");
	SRT_SCENE_STATE = SRT_ENDED_STATE;
}

/* Recursive depth */
#define SRT_DEFAULT_RECURSIVE_DEPTH 6
int SRT_RECURSIVE_DEPTH = SRT_DEFAULT_RECURSIVE_DEPTH;

void srtRecursiveDepth(int depth) {
	SRT_ASSERT_MSG(SRT_SCENE_STATE, "Recursive depth can only be set before beginning the scene!");
	SRT_ASSERT_MSG(depth > 0, "Recursive Depth Must Be Greater Than Zero!");
	SRT_RECURSIVE_DEPTH = depth;
}

/* Super sampling, 4xAA only at the moment */
int SRT_SUPERSAMPLING_ENABLED = 0;

void srtSuperSamplingEnabled(int enabled) {
	SRT_SUPERSAMPLING_ENABLED = enabled;
}

/* Two main transform matrices */
srtMatrix44 SRT_MODELVIEW_TRANSFORM = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
srtMatrix44 SRT_PROJECTION_TRANSFORM = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

/* Matrix modes */
int SRT_MODELVIEW = 0;
int SRT_PROJECTION = 1;
int SRT_MATRIX_MODE = 0;

void srtMatrixMode(int mode) {
	SRT_ASSERT_MSG(mode == SRT_MODELVIEW || mode == SRT_PROJECTION, "Unknown Matrix Mode!  Use SRT_MODELVIEW or SRT_PROJECTION");
	SRT_MATRIX_MODE = mode;
}

/* identity */
void srtLoadIdentity(void) {
	srtReal *targetMatrix;
	if (SRT_MATRIX_MODE == SRT_MODELVIEW)
		targetMatrix = SRT_MODELVIEW_TRANSFORM;
	else
		targetMatrix = SRT_PROJECTION_TRANSFORM;
	
	targetMatrix[0] = 1.0;
	targetMatrix[1] = 0.0;
	targetMatrix[2] = 0.0;
	targetMatrix[3] = 0.0;
	
	targetMatrix[4] = 0.0;
	targetMatrix[5] = 1.0;
	targetMatrix[6] = 0.0;
	targetMatrix[7] = 0.0;
	
	targetMatrix[8] = 0.0;
	targetMatrix[9] = 0.0;
	targetMatrix[10] = 1.0;
	targetMatrix[11] = 0.0;
	
	targetMatrix[12] = 0.0;
	targetMatrix[13] = 0.0;
	targetMatrix[14] = 0.0;
	targetMatrix[15] = 1.0;
}

/* custom matrix */
void srtLoadMatrix(srtMatrix44 matrix) {
	srtReal *targetMatrix;
	if (SRT_MATRIX_MODE == SRT_MODELVIEW)
		targetMatrix = SRT_MODELVIEW_TRANSFORM;
	else
		targetMatrix = SRT_PROJECTION_TRANSFORM;
	
	targetMatrix[0] = matrix[0];
	targetMatrix[1] = matrix[1];
	targetMatrix[2] = matrix[2];
	targetMatrix[3] = matrix[3];
	
	targetMatrix[4] = matrix[4];
	targetMatrix[5] = matrix[5];
	targetMatrix[6] = matrix[6];
	targetMatrix[7] = matrix[7];
	
	targetMatrix[8] = matrix[8];
	targetMatrix[9] = matrix[9];
	targetMatrix[10] = matrix[10];
	targetMatrix[11] = matrix[11];
	
	targetMatrix[12] = matrix[12];
	targetMatrix[13] = matrix[13];
	targetMatrix[14] = matrix[14];
	targetMatrix[15] = matrix[15];
}

/* set multiply current matrix */
void srtMultMatrix(srtMatrix44 matrix) {
	srtReal *targetMatrix;
	if (SRT_MATRIX_MODE == SRT_MODELVIEW)
		targetMatrix = SRT_MODELVIEW_TRANSFORM;
	else
		targetMatrix = SRT_PROJECTION_TRANSFORM;
	
	targetMatrix[0] = targetMatrix[0]* matrix[0] + targetMatrix[1]*matrix[4] + targetMatrix[2]*matrix[8] + targetMatrix[3]*matrix[12];
	targetMatrix[1] = targetMatrix[0]*matrix[1] + targetMatrix[1]*matrix[5] + targetMatrix[2]*matrix[9] + targetMatrix[3]*matrix[13];
    targetMatrix[2] = targetMatrix[0]*matrix[2] + targetMatrix[1]*matrix[6] + targetMatrix[2]*matrix[10] + targetMatrix[3]*matrix[14];       
	targetMatrix[3] = targetMatrix[0]*matrix[3] + targetMatrix[1]*matrix[7] + targetMatrix[2]*matrix[11] + targetMatrix[3]*matrix[15];
 
    targetMatrix[4] = targetMatrix[4]*matrix[0] + targetMatrix[5]*matrix[4] + targetMatrix[6]*matrix[8] + targetMatrix[7]*matrix[12];
	targetMatrix[5] = targetMatrix[4]*matrix[1] + targetMatrix[5]*matrix[5] + targetMatrix[6]*matrix[9] + targetMatrix[7]*matrix[13];
	targetMatrix[6] = targetMatrix[4]*matrix[2] + targetMatrix[5]*matrix[6] + targetMatrix[6]*matrix[10] + targetMatrix[7]*matrix[14];
	targetMatrix[7] = targetMatrix[4]*matrix[3] + targetMatrix[5]*matrix[7] + targetMatrix[6]*matrix[11] + targetMatrix[7]*matrix[15];

	targetMatrix[8] = targetMatrix[8]*matrix[0] + targetMatrix[9]*matrix[4] + targetMatrix[10]*matrix[8] + targetMatrix[11]*matrix[12];
	targetMatrix[9] = targetMatrix[8]*matrix[1] + targetMatrix[9]*matrix[5] + targetMatrix[10]*matrix[9] + targetMatrix[11]*matrix[13];
	targetMatrix[10] = targetMatrix[8]*matrix[2] + targetMatrix[9]*matrix[6] + targetMatrix[10]*matrix[10] + targetMatrix[11]*matrix[14];
	targetMatrix[11] = targetMatrix[8]*matrix[3] + targetMatrix[9]*matrix[7] + targetMatrix[10]*matrix[11] + targetMatrix[11]*matrix[15];

	targetMatrix[12] = targetMatrix[12]*matrix[0] + targetMatrix[13]*matrix[4] + targetMatrix[14]*matrix[8] + targetMatrix[15]*matrix[12];
	targetMatrix[13] = targetMatrix[12]*matrix[1] + targetMatrix[13]*matrix[5] + targetMatrix[14]*matrix[9] + targetMatrix[15]*matrix[13];
	targetMatrix[14] = targetMatrix[12]*matrix[2] + targetMatrix[13]*matrix[6] + targetMatrix[14]*matrix[10] + targetMatrix[15]*matrix[14];
	targetMatrix[15] = targetMatrix[12]*matrix[3] + targetMatrix[13]*matrix[7] + targetMatrix[14]*matrix[11] + targetMatrix[15]*matrix[15];
}

/* set multiply translation matrix */
void srtTranslate(srtReal x, srtReal y, srtReal z) {
	srtMatrix44 tmat;
	srtMat44_Translation(tmat, x, y, z);
	srtMultMatrix(tmat);
}

/* set multiply scaling matrix */
void srtScale(srtReal x, srtReal y, srtReal z) {
	srtMatrix44 smat;
	srtMat44_Scale(smat, x, y, z);
	srtMultMatrix(smat);
}

/* set multiply axis angle rotation matrix */
void srtRotate(srtReal degrees, srtReal x, srtReal y, srtReal z) {
	srtReal xSq = x*x;
	srtReal ySq = y*y;
	srtReal zSq = z*z;
	srtReal magSq = xSq + ySq + zSq;
	
	SRT_ASSERT_MSG(abs(magSq - 1.0) <= SRT_REAL_EPSILON, "A unit vector must be used for srtRotate");
	
	srtReal radians = degreesToRadians(degrees);
	
	srtReal s = srtSin(radians);
	srtReal c = srtCos(radians);
	srtReal omc = 1.0 - c;
	
	printf("S: %f\nC: %f\nOMC: %f\n", s, c, omc);
	
	srtReal xomc = x * omc;
	srtReal yomc = y * omc;
	srtReal zomc = z * omc;
	
	srtReal xxomc = x * xomc;
	srtReal yyomc = y * yomc;
	srtReal zzomc = z * zomc;
	srtReal xyomc = x * yomc;
	srtReal yzomc = y * zomc;
	srtReal zxomc = z * xomc;
	
	srtReal xs = s * x;
	srtReal ys = s * y;
	srtReal zs = s * z;
	
	srtMatrix44 rmat;
	rmat[0] = xxomc + c;
	rmat[1] = xyomc + zs;
	rmat[2] = zxomc - ys;
	rmat[3] = 0.0;
	
	rmat[4] = xyomc - zs;
	rmat[5] = yyomc + c;
	rmat[6] = yzomc + xs;
	rmat[7] = 0.0;
	
	rmat[8] = zxomc + ys;
	rmat[9] = yzomc - xs;
	rmat[10] = zzomc + c;
	rmat[11] = 0.0;
	
	rmat[12] = 0.0;
	rmat[13] = 0.0;
	rmat[14] = 0.0;
	rmat[15] = 1.0;
	
	printf("Projection Matrix: ");
	srtMat44_Print(rmat);
	
	srtMultMatrix(rmat);
}

/* creates a sphere modified by the modelview matrix with the current material */
void srtCreateSphere(const srtVector3 * const c, srtReal radius) {
	srtSphere *s;
	s = malloc(sizeof(srtSphere));
	s->c = srtMat44_Transform_Point(c, SRT_MODELVIEW_TRANSFORM);
	
	/* Need to use the inverse transpose and subtract to find scale values? */
	srtReal maxRadiusScale = srtMax(srtMax(SRT_MODELVIEW_TRANSFORM[0], SRT_MODELVIEW_TRANSFORM[5]), SRT_MODELVIEW_TRANSFORM[10]);
	s->r = radius * maxRadiusScale;
	
	srtDynamicArray_PushBack(SRT_SPHERE_ARRAY, s);
	
	srtMaterial *m = srtMatPtr();
	
	srtEntity *e;
	e = malloc(sizeof(srtEntity));
	e->mat = m;
	e->shape = s;
	e->shapeType = SRT_SPHERE_TYPE;
	
	srtDynamicArray_PushBack(SRT_ENTITY_ARRAY, e);
	/* push the entity */
}

/* creates a sphere with all scalar arguments */
void srtCreateSphere4(srtReal x, srtReal y, srtReal z, srtReal radius) {
	srtVector3 c = {x, y, z};
	srtCreateSphere(&c, radius);
}

/* Creates a polygon with the vertices modified by the model view matrix and the current material
 * Please use convex ccw polygons
 */
void srtCreatePolygon(const srtVector3 const *v, int N) {
	SRT_ASSERT_MSG(N >= 3, "Polygon must have at least 3 vertices!");
	
	srtVector3 *tv;
	tv = malloc(N * sizeof(srtVector3));
	
	SRT_ASSERT(tv);
	
	int i;
	for (i = 0; i < N; ++i) {
		tv[i] = srtMat44_Transform_Point(v + i, SRT_MODELVIEW_TRANSFORM);
	}
	
	/* Derive plane from polygon normal and distance */
	srtVector3 centroid = srtPoly_Centroid(tv, N);
	
	srtVector3 pn;
	srtReal pd;
	srtPoly_Plane(tv, N, &centroid, &pn, &pd);
	
	srtPolygon *poly;
	poly = malloc(sizeof(srtPolygon));
	poly->v = tv;
	poly->N = N;
	poly->planeNormal = pn;
	poly->planeDistance = pd;
	
	srtDynamicArray_PushBack(SRT_POLYGON_ARRAY, poly);
	
	srtMaterial *m = srtMatPtr();
	
	srtEntity *e;
	e = malloc(sizeof(srtEntity));
	e->mat = m;
	e->shape = poly;
	e->shapeType = SRT_POLYGON_TYPE;
	
	srtDynamicArray_PushBack(SRT_ENTITY_ARRAY, e);	
}

/* transform can contain rotation only! */
void srtCreateBox(srtVector3 *c, srtVector3 *r, srtMatrix44 transform) {
	
	/*srtMatrix44 xform;
	srtMat44_Mult(transform, SRT_MODELVIEW_TRANSFORM, xform);*/
	
	srtMatrix44 inverseSceneTranspose, sceneTranspose;
		
	/* subtract transform by inverse transpose to get the scaling factors only */
	srtMat44_Transpose(SRT_MODELVIEW_TRANSFORM, sceneTranspose);
	srtMat44_Inverse(sceneTranspose, inverseSceneTranspose);

	
	srtReal bsx = 1.0 + SRT_MODELVIEW_TRANSFORM[0] - inverseSceneTranspose[0];
	srtReal bsy = 1.0 + SRT_MODELVIEW_TRANSFORM[5] - inverseSceneTranspose[5];
	srtReal bsz = 1.0 + SRT_MODELVIEW_TRANSFORM[10] - inverseSceneTranspose[10];
	
	/* modify c by scene transform and r by scaling factors */
	srtVector3 tc = srtMat44_Transform_Point(c, SRT_MODELVIEW_TRANSFORM);
	srtVector3 tr = {r->x * bsx, r->y * bsy, r->z * bsz};
	
	srtMatrix44 boxTransform, inverseBoxTransform;
	srtMat44_Mult(transform, inverseSceneTranspose, boxTransform);
	srtMat44_Inverse(boxTransform, inverseBoxTransform);
	
	
	/* strip translation from  */
	/*
	inverseBoxTransform[12] = 0.0;
	inverseBoxTransform[13] = 0.0;
	inverseBoxTransform[14] = 0.0;
	inverseBoxTransform[15] = 1.0;
	*/
	/*srtMatrix44 inverseBoxTranspose;*/
	
	srtBox *b;
	b = malloc(sizeof(srtBox));
	b->c = tc;
	b->r = tr;
	
	int i;
	for (i = 0; i < 16; ++i) {
		b->xform[i] = transform[i];
		b->invTranspose[i] = inverseBoxTransform[i];
	}
	
	/*
	b->invTranspose[12] = 0.0f;
	b->invTranspose[13] = 0.0f;
	b->invTranspose[14] = 0.0f;
	b->invTranspose[15] = 1.0f;
	*/
	
	srtDynamicArray_PushBack(SRT_BOX_ARRAY, b);
	
	srtMaterial *m = srtMatPtr();
	srtEntity *e;
	e = malloc(sizeof(srtEntity));
	e->mat = m;
	e->shape = b;
	e->shapeType = SRT_BOX_TYPE;
	
	printf("Box C: ");
	srtVec3_Print(&b->c);
	printf("\n");
	
	printf("Box R: ");
	srtVec3_Print(&b->r);
	printf("\n");
	
	srtMat44_Print(b->xform);
	srtMat44_Print(b->invTranspose);
	
	srtDynamicArray_PushBack(SRT_ENTITY_ARRAY, e);	

	
	/*SRT_ASSERT(tc);*/
}

/* helper function that determines if the shadow ray reaches the light source, calculates occluding transmission if not */
int srtShadowRayReachesLight(srtVector3 *point, srtVector3 *d, srtReal distanceToLight, srtEntity *ignore, srtReal *occludingTransmission) {
	unsigned int count = srtDynamicArray_Count(SRT_ENTITY_ARRAY);
	
	srtRay r = {*point, *d};
	srtReal minDist = SRT_REAL_MAX;
	
	void *vIgnore = (void *)ignore;
	
	srtVector3 pt, n;
	srtReal distance = SRT_REAL_MAX;
	int i;

	
	for (i = 0; i < count; ++i) {
		if (SRT_ENTITY_ARRAY->buffer[i] == vIgnore)
			continue;
		if (SRT_RAYCAST_FUNCTIONS[((srtEntity*)SRT_ENTITY_ARRAY->buffer[i])->shapeType](&r, ((srtEntity*)SRT_ENTITY_ARRAY->buffer[i])->shape, &distance, &pt, &n)) {
			if (distance < minDist) {
				minDist = distance;
				*occludingTransmission = ((srtEntity*)SRT_ENTITY_ARRAY->buffer[i])->mat->transmission;
			}
		}
	}
	
	return distanceToLight < minDist;
}

srtVector3 imagePlane, cameraPosition;

/* Main recursive function of scene drawing
 * Applies phong illumination until no object is 
 * hit by the ray or the max recursive depth is reached
 */
srtColor srtIlluminate(srtRay *r, int rdepth, srtEntity *ignore) {
	int i;
	
	srtVector3 intersectionPoint, normal;
	srtReal distance;
	srtReal minDist = SRT_REAL_MAX;
	srtEntity *obj = NULL;
	int hitResult = 0;
	
	unsigned int count = srtDynamicArray_Count(SRT_ENTITY_ARRAY);
	for (i = 0; i < count; ++i) {
		if (((srtEntity *)(SRT_ENTITY_ARRAY->buffer[i])) == ignore)
			continue;
		srtVector3 n, pt;
		srtReal t;
		srtEntity *curEntity = (srtEntity*)SRT_ENTITY_ARRAY->buffer[i];
		int h = SRT_RAYCAST_FUNCTIONS[curEntity->shapeType](r, curEntity->shape, &t, &pt, &n);
		if (h) {
			/*
			if (((srtEntity *)(SRT_ENTITY_ARRAY->buffer[i])) == ignore) {
				printf("Hit Result: %d\n", h);
				
			}
			*/
			if (t < minDist) {
				minDist = t;
				obj = curEntity;
				normal = n;
				intersectionPoint = pt;
				distance = t;
				hitResult = h;
			}
		}
	}
	
	if (obj == NULL)
		return SRT_CLEAR_COLOR;
		
	if (!SRT_LIGHTING_ENABLED)
		return obj->mat->ambient;
	
	/*normal = srtVec3_Mult(&normal, (srtReal)hitResult);*/
	srtVector3 source = srtVec3_Sub(&SRT_LIGHT_POSITION, &intersectionPoint);
	srtVector3 reflection = srtVec3_Reflect(&r->direction, &normal);
	srtVector3 view = srtVec3_Sub(&cameraPosition, &intersectionPoint);
	
	srtColor finalColor = srtColor_Mult(&obj->mat->ambient, &SRT_LIGHT_AMBIENT);
	
	srtReal occluderTransmission;
	srtReal distToLight = source.x*source.x + source.y*source.y + source.z*source.z;
	distToLight = srtSqrt(distToLight);
	srtVector3 sn = source;
	srtVec3_Normalize(&sn);
	
	int lightReached = srtShadowRayReachesLight(&intersectionPoint, &sn, distToLight, obj, &occluderTransmission);
	/*
	if (srtVec3_Dot(&sn, &normal) < 0.0)
		lightReached = srtShadowRayReachesLight(&intersectionPoint, &sn, distToLight, NULL, &occluderTransmission);
	else
		lightReached = srtShadowRayReachesLight(&intersectionPoint, &sn, distToLight, obj, &occluderTransmission);
	*/
	if (lightReached) {
		srtReal lsdn = srtVec3_Dot(&sn, &normal);
		srtColor objectDiffuse = srtColor_Mult(&SRT_LIGHT_DIFFUSE, &obj->mat->diffuse);
		if (lsdn > 0.0) {
			objectDiffuse = srtColor_Mult_Scalar(&objectDiffuse, lsdn);
			finalColor = srtColor_Add(&finalColor, &objectDiffuse);
		}
		
		if (!srtVec3_Equals(&view, &SRT_VECTOR3_ZERO)) {
			srtVector3 viewN = view;
			srtVec3_Normalize(&viewN);
			srtReal rdv = srtVec3_Dot(&reflection, &viewN);
			
			finalColor = srtColor_Mult_Scalar(&finalColor, 1.0f - obj->mat->transmission);
			
			if (rdv > 0.0f) {
				srtReal decay = pow(rdv, obj->mat->shininess);
				srtColor specularProduct = srtColor_Mult(&obj->mat->specular, &SRT_LIGHT_SPECULAR);
				srtColor objectSpecular = srtColor_Mult_Scalar(&specularProduct, decay);
				finalColor = srtColor_Mult_Scalar(&finalColor, 1.0f - obj->mat->transmission);
				finalColor = srtColor_Add(&finalColor, &objectSpecular);
			}
		}
	} else {
		srtReal lsdn = srtVec3_Dot(&sn, &normal);
		srtColor objectDiffuse = srtColor_Mult(&SRT_LIGHT_DIFFUSE, &obj->mat->diffuse);
		if (lsdn > 0.0) {
			objectDiffuse = srtColor_Mult_Scalar(&objectDiffuse, lsdn);
			objectDiffuse = srtColor_Mult_Scalar(&objectDiffuse, occluderTransmission);
			finalColor = srtColor_Add(&finalColor, &objectDiffuse);
		}
		
		if (!srtVec3_Equals(&view, &SRT_VECTOR3_ZERO)) {
			srtVector3 viewN = view;
			srtVec3_Normalize(&viewN);
			srtReal rdv = srtVec3_Dot(&reflection, &viewN);
						
			if (rdv > 0.0f) {
				srtReal decay = pow(rdv, obj->mat->shininess);
				srtColor specularProduct = srtColor_Mult(&obj->mat->specular, &SRT_LIGHT_SPECULAR);
				srtColor objectSpecular = srtColor_Mult_Scalar(&specularProduct, decay);
				objectSpecular = srtColor_Mult_Scalar(&objectSpecular, occluderTransmission);
				finalColor = srtColor_Mult_Scalar(&finalColor, 1.0f - obj->mat->transmission);
				finalColor = srtColor_Add(&finalColor, &objectSpecular);
			}
		}
	}
	
	
	if (rdepth < SRT_RECURSIVE_DEPTH) {
		srtRay reflectedRay = {intersectionPoint, reflection};
		if (obj->mat->reflectivity > 0.0f) {
			srtColor reflectedColor = srtIlluminate(&reflectedRay, rdepth + 1, obj);
			reflectedColor = srtColor_Mult_Scalar(&reflectedColor, obj->mat->reflectivity);
			finalColor = srtColor_Add(&finalColor, &reflectedColor);
		}
		int internalReflection = 0;
		if (obj->mat->transmission > 0.0f) {
			srtReal nit = 1.0f / obj->mat->transmission;
			/*srtReal nit;
			if (ignore)
				nit = ignore->mat->refraction / obj->mat->refraction;
			else
				nit = 1.0 / obj->mat->refraction;
			*/
			/*
			srtReal cosI = -srtVec3_Dot(&normal, &r->direction);
			srtReal cosT2 = 1.0 - n * n * (1.0 - cosI * cosI);
			if (cosT2 > 0.0) {
				srtVector3 tran = srtVec3_Mult(&r->direction, n);
				srtReal expr = n * cosI - srtSqrt(cosT2);
				srtVector3 nExpr = srtVec3_Mult(&normal, expr);
				tran = srtVec3_Add(&tran, &nExpr);
				srtVec3_Normalize(&tran);
				
				srtRay refractedRay = {intersectionPoint, tran};
				
				srtColor refractedColor = srtIlluminate(&refractedRay, rdepth + 1, obj);
				refractedColor = srtColor_Mult_Scalar(&refractedColor, obj->mat->transmission);
				finalColor = srtColor_Add(&finalColor, &refractedColor);
			}
			
			srtReal nit = 1.0f / obj->mat->transmission;
			*/
			srtVector3 nitd = srtVec3_Mult(&r->direction, nit);
			srtVector3 negatedDirection = {-r->direction.x, -r->direction.y, -r->direction.z};
			srtVector3 negatedNormal = {-normal.x, -normal.y, -normal.z};
			srtReal dDotN = srtVec3_Dot(&negatedDirection, &normal);
			
			srtReal eq, discr;
			srtVector3 tran;
			if (dDotN >= 0.0f) {
				eq = nit * dDotN;
				discr = 1.0f + ((nit * nit) * ((dDotN * dDotN) - 1.0f));
				if (discr < 0.0f) {
					srtColor transmissiveColor = srtIlluminate(&reflectedRay, rdepth + 1, obj);
					transmissiveColor = srtColor_Mult_Scalar(&transmissiveColor, obj->mat->transmission);
					finalColor = srtColor_Add(&finalColor, &transmissiveColor);
					internalReflection = 1;
				} else {
					discr = sqrt(discr);
					tran = srtVec3_Mult(&normal, eq - discr);
					tran = srtVec3_Add(&tran, &nitd);
				}
			} else {
				dDotN = srtVec3_Dot(&negatedDirection, &negatedNormal);
				eq = nit * dDotN;
				discr = 1.0f + ((nit * nit) * ((dDotN * dDotN) - 1.0f));
				discr = sqrt(discr);
				tran = srtVec3_Mult(&negatedNormal, eq - discr);
				tran = srtVec3_Add(&tran, &nitd);
			} if (!internalReflection) {
				srtRay transmissionRay = {intersectionPoint, tran};
				srtColor transmissionColor = srtIlluminate(&transmissionRay, rdepth + 1, obj);
				transmissionColor = srtColor_Mult_Scalar(&transmissionColor, obj->mat->transmission);
				finalColor = srtColor_Add(&finalColor, &transmissionColor);
			}
		}
	}
	
	return finalColor;
}

/* Renders the scene to the color buffer */
void srtDrawScene(void) {
	
	SRT_ASSERT_MSG(SRT_SCENE_STATE == SRT_ENDED_STATE, "Scene must be ended before drawing!");
	
	/* Transform camera position */
	cameraPosition = srtMat44_Transform_Point(&SRT_VECTOR3_ZERO, SRT_PROJECTION_TRANSFORM);
	
	/* Transform up, right, and forward vectors */
	srtVector3 cameraUp = srtMat44_Transform_Normal(&SRT_VECTOR3_UNIT_Y, SRT_PROJECTION_TRANSFORM);
	srtVector3 cameraRight = srtMat44_Transform_Normal(&SRT_VECTOR3_UNIT_X, SRT_PROJECTION_TRANSFORM);
	srtVector3 cameraForward = {0.0, 0.0, -1.0};
	cameraForward = srtMat44_Transform_Normal(&cameraForward, SRT_PROJECTION_TRANSFORM);
	
	/* center of the image plane */
	imagePlane.x = cameraPosition.x + cameraForward.x * SRT_IMAGE_PLANE_DISTANCE; 
	imagePlane.y = cameraPosition.y + cameraForward.y * SRT_IMAGE_PLANE_DISTANCE; 
	imagePlane.z = cameraPosition.z + cameraForward.z * SRT_IMAGE_PLANE_DISTANCE;
	
	int x, y;
	if (!SRT_SUPERSAMPLING_ENABLED) {
		for (x = 0; x < SRT_SCREEN_WIDTH; ++x) {
			
			/* Find x vector */
			srtReal twoC = (2 * x) / (srtReal)SRT_SCREEN_WIDTH;
			srtVector3 imgPlaneX = srtVec3_Mult(&cameraRight, -SRT_IMAGE_PLANE_WIDTH + SRT_IMAGE_PLANE_WIDTH * twoC);
			
			for (y = 0; y < SRT_SCREEN_HEIGHT; ++y) {
				
				/* Find y vector */
				srtReal twoR = (2 * y) / (srtReal)SRT_SCREEN_HEIGHT;
				srtVector3 imgPlaneY = srtVec3_Mult(&cameraUp, -SRT_IMAGE_PLANE_HEIGHT + SRT_IMAGE_PLANE_HEIGHT * twoR);
				
				/* Create screen -> image plane conversion */
				srtVector3 pixel = {imagePlane.x + imgPlaneX.x + imgPlaneY.x, imagePlane.y + imgPlaneX.y + imgPlaneY.y, imagePlane.z + imgPlaneX.z + imgPlaneY.z};
				srtVector3 direction = srtVec3_Sub(&pixel, &cameraPosition);
				srtVec3_Normalize(&direction);
				
				srtRay r = {cameraPosition, direction};
				
				/* Recursively determine the final picked color for this ray */
				srtColor c = srtIlluminate(&r, 1, NULL);
				
				/* Saturate and place in color buffer */
				srtColor_Saturate(&c);
				srtPutPixel(x, y, &c);
			}
		}
	} else {
		/* Use 4xAA with neighboring pixels and average the resulting color */
		const srtReal avg = 0.25;
		for (x = 0; x < SRT_SCREEN_WIDTH; ++x) {
			
			for (y = 0; y < SRT_SCREEN_HEIGHT; ++y) {
				
				srtReal fragX, fragY;
				srtColor csum = SRT_ZERO;
				for (fragX = x; fragX < x + 1.0; fragX += 0.5) {
					
					/* Find x vector */
					srtReal twoC = (2 * fragX) / (srtReal)SRT_SCREEN_WIDTH;
					srtVector3 imgPlaneX = srtVec3_Mult(&cameraRight, -SRT_IMAGE_PLANE_WIDTH + SRT_IMAGE_PLANE_WIDTH * twoC);
					
					for (fragY = y; fragY < y + 1.0; fragY += 0.5) {
						
						/* Find y vector */
						srtReal twoR = (2 * fragY) / (srtReal)SRT_SCREEN_HEIGHT;
						srtVector3 imgPlaneY = srtVec3_Mult(&cameraUp, -SRT_IMAGE_PLANE_HEIGHT + SRT_IMAGE_PLANE_HEIGHT * twoR);
						
						/* Create screen -> image plane conversion */
						srtVector3 pixel = {imagePlane.x + imgPlaneX.x + imgPlaneY.x, imagePlane.y + imgPlaneX.y + imgPlaneY.y, imagePlane.z + imgPlaneX.z + imgPlaneY.z};
						srtVector3 direction = srtVec3_Sub(&pixel, &cameraPosition);
						srtVec3_Normalize(&direction);
				
						srtRay r = {cameraPosition, direction};
						
						/* Recursively determine the final picked color for this ray */
						srtColor c = srtIlluminate(&r, 1, NULL);
						csum = srtColor_Add(&csum, &c);
					}
				}
				
				/* Average accumulated color */
				csum = srtColor_Mult_Scalar(&csum, avg);
				
				/* Saturate and place in color buffer */
				srtColor_Saturate(&csum);
				srtPutPixel(x, y, &csum);
			}
		}
	}
}


#endif