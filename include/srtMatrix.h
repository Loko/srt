#ifndef H_SRT_MATRIX
#define H_SRT_MATRIX

#include "srtVector.h"

typedef srtReal srtMatrix44[16];

const srtMatrix44 SRT_MATRIX44_IDENTITY = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};

void srtMat44_Add(const srtMatrix44 a, const srtMatrix44 b, srtMatrix44 sum) {
	int i;
	for (i = 0; i < 16; ++i) {
		sum[i] = a[i] + b[i];
	}
}

void srtMat44_Mult(const srtMatrix44 a, const srtMatrix44 b, srtMatrix44 product) {
	product[0] = a[0]* b[0] + a[1]*b[4] + a[2]*b[8] + a[3]*b[12];
	product[1] = a[0]*b[1] + a[1]*b[5] + a[2]*b[9] + a[3]*b[13];
    product[2] = a[0]*b[2] + a[1]*b[6] + a[2]*b[10] + a[3]*b[14];       
	product[3] = a[0]*b[3] + a[1]*b[7] + a[2]*b[11] + a[3]*b[15];
 
    product[4] = a[4]*b[0] + a[5]*b[4] + a[6]*b[8] + a[7]*b[12];
	product[5] = a[4]*b[1] + a[5]*b[5] + a[6]*b[9] + a[7]*b[13];
	product[6] = a[4]*b[2] + a[5]*b[6] + a[6]*b[10] + a[7]*b[14];
	product[7] = a[4]*b[3] + a[5]*b[7] + a[6]*b[11] + a[7]*b[15];

	product[8] = a[8]*b[0] + a[9]*b[4] + a[10]*b[8] + a[11]*b[12];
	product[9] = a[8]*b[1] + a[9]*b[5] + a[10]*b[9] + a[11]*b[13];
	product[10] = a[8]*b[2] + a[9]*b[6] + a[10]*b[10] + a[11]*b[14];
	product[11] = a[8]*b[3] + a[9]*b[7] + a[10]*b[11] + a[11]*b[15];

	product[12] = a[12]*b[0] + a[13]*b[4] + a[14]*b[8] + a[15]*b[12];
	product[13] = a[12]*b[1] + a[13]*b[5] + a[14]*b[9] + a[15]*b[13];
	product[14] = a[12]*b[2] + a[13]*b[6] + a[14]*b[10] + a[15]*b[14];
	product[15] = a[12]*b[3] + a[13]*b[7] + a[14]*b[11] + a[15]*b[15];
}

void srtMat44_Identity(srtMatrix44 matrix) {
	matrix[0] = 1.0f;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;
	
	matrix[4] = 0.0f;
	matrix[5] = 1.0f;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;
	
	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = 1.0f;
	matrix[11] = 0.0f;
	
	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

void srtMat44_Translation(srtMatrix44 matrix, srtReal tx, srtReal ty, srtReal tz) {
	matrix[0] = 1.0f;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;
	
	matrix[4] = 0.0f;
	matrix[5] = 1.0f;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;
	
	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = 1.0f;
	matrix[11] = 0.0f;
	
	matrix[12] = tx;
	matrix[13] = ty;
	matrix[14] = tz;
	matrix[15] = 1.0f;
}

void srtMat44_Scale(srtMatrix44 matrix, srtReal sx, srtReal sy, srtReal sz) {
	matrix[0] = sx;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;
	
	matrix[4] = 0.0f;
	matrix[5] = sy;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;
	
	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = sz;
	matrix[11] = 0.0f;
	
	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

void srtMat44_RotationY(srtMatrix44 matrix, srtReal ry) {
	srtReal c = srtCos(ry);
	srtReal s = srtSin(ry);
	matrix[0] = c;
	matrix[1] = 0.0f;
	matrix[2] = -s;
	matrix[3] = 0.0f;
	
	matrix[4] = 0.0f;
	matrix[5] = 1.0f;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;
	
	matrix[8] = s;
	matrix[9] = 0.0f;
	matrix[10] = c;
	matrix[11] = 0.0f;
	
	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

void srtMat44_RotationZ(srtMatrix44 matrix, srtReal rz) {
	srtReal c = srtCos(rz);
	srtReal s = srtSin(rz);
	matrix[0] = c;
	matrix[1] = s;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;
	
	matrix[4] = -s;
	matrix[5] = c;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;
	
	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = 1.0f;
	matrix[11] = 0.0f;
	
	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

void srtMat44_RotationX(srtMatrix44 matrix, srtReal rx) {
	srtReal c = srtCos(rx);
	srtReal s = srtSin(rx);
	matrix[0] = 1.0f;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;
	
	matrix[4] = 0.0f;
	matrix[5] = c;
	matrix[6] = s;
	matrix[7] = 0.0f;
	
	matrix[8] = 0.0f;
	matrix[9] = -s;
	matrix[10] = c;
	matrix[11] = 0.0f;
	
	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}

int srtMat44_Inverse(const srtMatrix44 matrix, srtMatrix44 inverse) {
	srtMatrix44 inv;
	float det;
	int i;

	inv[0] = matrix[5]*matrix[10]*matrix[15] - matrix[5]*matrix[11]*matrix[14] - matrix[9]*matrix[6]*matrix[15]
	+ matrix[9]*matrix[7]*matrix[14] + matrix[13]*matrix[6]*matrix[11] - matrix[13]*matrix[7]*matrix[10];
	
	inv[4] = -matrix[4]*matrix[10]*matrix[15] + matrix[4]*matrix[11]*matrix[14] + matrix[8]*matrix[6]*matrix[15]
	- matrix[8]*matrix[7]*matrix[14] - matrix[12]*matrix[6]*matrix[11] + matrix[12]*matrix[7]*matrix[10];
	
	inv[8] = matrix[4]*matrix[9]*matrix[15] - matrix[4]*matrix[11]*matrix[13] - matrix[8]*matrix[5]*matrix[15]
	+ matrix[8]*matrix[7]*matrix[13] + matrix[12]*matrix[5]*matrix[11] - matrix[12]*matrix[7]*matrix[9];
	
	inv[12] = -matrix[4]*matrix[9]*matrix[14] + matrix[4]*matrix[10]*matrix[13] + matrix[8]*matrix[5]*matrix[14]
	- matrix[8]*matrix[6]*matrix[13] - matrix[12]*matrix[5]*matrix[10] + matrix[12]*matrix[6]*matrix[9];
	
	inv[1] = -matrix[1]*matrix[10]*matrix[15] + matrix[1]*matrix[11]*matrix[14] + matrix[9]*matrix[2]*matrix[15]
	- matrix[9]*matrix[3]*matrix[14] - matrix[13]*matrix[2]*matrix[11] + matrix[13]*matrix[3]*matrix[10];
	
	inv[5] = matrix[0]*matrix[10]*matrix[15] - matrix[0]*matrix[11]*matrix[14] - matrix[8]*matrix[2]*matrix[15]
	+ matrix[8]*matrix[3]*matrix[14] + matrix[12]*matrix[2]*matrix[11] - matrix[12]*matrix[3]*matrix[10];
	
	inv[9] = -matrix[0]*matrix[9]*matrix[15] + matrix[0]*matrix[11]*matrix[13] + matrix[8]*matrix[1]*matrix[15]
	- matrix[8]*matrix[3]*matrix[13] - matrix[12]*matrix[1]*matrix[11] + matrix[12]*matrix[3]*matrix[9];
	
	inv[13] = matrix[0]*matrix[9]*matrix[14] - matrix[0]*matrix[10]*matrix[13] - matrix[8]*matrix[1]*matrix[14]
	+ matrix[8]*matrix[2]*matrix[13] + matrix[12]*matrix[1]*matrix[10] - matrix[12]*matrix[2]*matrix[9];
	
	inv[2] = matrix[1]*matrix[6]*matrix[15] - matrix[1]*matrix[7]*matrix[14] - matrix[5]*matrix[2]*matrix[15]
	+ matrix[5]*matrix[3]*matrix[14] + matrix[13]*matrix[2]*matrix[7] - matrix[13]*matrix[3]*matrix[6];
	
	inv[6] = -matrix[0]*matrix[6]*matrix[15] + matrix[0]*matrix[7]*matrix[14] + matrix[4]*matrix[2]*matrix[15]
	- matrix[4]*matrix[3]*matrix[14] - matrix[12]*matrix[2]*matrix[7] + matrix[12]*matrix[3]*matrix[6];
	
	inv[10] = matrix[0]*matrix[5]*matrix[15] - matrix[0]*matrix[7]*matrix[13] - matrix[4]*matrix[1]*matrix[15]
	+ matrix[4]*matrix[3]*matrix[13] + matrix[12]*matrix[1]*matrix[7] - matrix[12]*matrix[3]*matrix[5];
	
	inv[14] = -matrix[0]*matrix[5]*matrix[14] + matrix[0]*matrix[6]*matrix[13] + matrix[4]*matrix[1]*matrix[14]
	- matrix[4]*matrix[2]*matrix[13] - matrix[12]*matrix[1]*matrix[6] + matrix[12]*matrix[2]*matrix[5];
	
	inv[3] = -matrix[1]*matrix[6]*matrix[11] + matrix[1]*matrix[7]*matrix[10] + matrix[5]*matrix[2]*matrix[11]
	- matrix[5]*matrix[3]*matrix[10] - matrix[9]*matrix[2]*matrix[7] + matrix[9]*matrix[3]*matrix[6];
	
	inv[7] = matrix[0]*matrix[6]*matrix[11] - matrix[0]*matrix[7]*matrix[10] - matrix[4]*matrix[2]*matrix[11]
	+ matrix[4]*matrix[3]*matrix[10] + matrix[8]*matrix[2]*matrix[7] - matrix[8]*matrix[3]*matrix[6];
	
	inv[11] = -matrix[0]*matrix[5]*matrix[11] + matrix[0]*matrix[7]*matrix[9] + matrix[4]*matrix[1]*matrix[11]
	- matrix[4]*matrix[3]*matrix[9] - matrix[8]*matrix[1]*matrix[7] + matrix[8]*matrix[3]*matrix[5];
	
	inv[15] = matrix[0]*matrix[5]*matrix[10] - matrix[0]*matrix[6]*matrix[9] - matrix[4]*matrix[1]*matrix[10]
	+ matrix[4]*matrix[2]*matrix[9] + matrix[8]*matrix[1]*matrix[6] - matrix[8]*matrix[2]*matrix[5];

	det = matrix[0]*inv[0] + matrix[1]*inv[4] + matrix[2]*inv[8] + matrix[3]*inv[12];
	if (det == 0)
        return 0;

	det = 1.0 / det;

	for (i = 0; i < 16; i++)
        inverse[i] = inv[i] * det;

	return 1;
}

void srtMat44_Transpose(const srtMatrix44 matrix, srtMatrix44 transpose) {
	transpose[0] = matrix[0];
	transpose[1] = matrix[4];
	transpose[2] = matrix[8];
	transpose[3] = matrix[12];
	
	transpose[4] = matrix[1];
	transpose[5] = matrix[5];
	transpose[6] = matrix[9];
	transpose[7] = matrix[13];
	
	transpose[8] = matrix[2];
	transpose[9] = matrix[6];
	transpose[10] = matrix[10];
	transpose[11] = matrix[14];
	
	transpose[12] = matrix[3];
	transpose[13] = matrix[7];
	transpose[14] = matrix[11];
	transpose[15] = matrix[15];
}

srtVector3 srtMat44_Transform_Point(const srtVector3 const *v, const srtMatrix44 xform) {
	srtVector3 result;
	result.x = xform[0] * v->x + xform[4] * v->y + xform[8] * v->z + xform[12];
	result.y = xform[1] * v->x + xform[5] * v->y + xform[9] * v->z + xform[13];
	result.z = xform[2] * v->x + xform[6] * v->y + xform[10] * v->z + xform[14];
	return result;
}

srtVector3 srtMat44_Transform_Normal(const srtVector3 const *v, const srtMatrix44 xform) {
	srtVector3 result;
	result.x = xform[0] * v->x + xform[4] * v->y + xform[8] * v->z;
	result.y = xform[1] * v->x + xform[5] * v->y + xform[9] * v->z;
	result.z = xform[2] * v->x + xform[6] * v->y + xform[10] * v->z;
	return result;
}

void srtMat44_Print(srtMatrix44 matrix) {
	printf("{ %f, %f, %f, %f  \n", matrix[0], matrix[4], matrix[8], matrix[12]);
	printf("  %f, %f, %f, %f  \n", matrix[1], matrix[5], matrix[9], matrix[13]);
	printf("  %f, %f, %f, %f  \n", matrix[2], matrix[6], matrix[10], matrix[14]);
	printf("  %f, %f, %f, %f }\n", matrix[3], matrix[7], matrix[11], matrix[15]);
}

/* still gotta add rot matrix functions */

#endif