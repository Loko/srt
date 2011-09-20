#ifndef H_SRT_COLOR
#define H_SRT_COLOR

#include "srtReal.h"
#include "stdio.h"

typedef struct {
	srtReal a, r, g, b;
} srtColor;

const srtColor SRT_RED = 	 {1.0f, 1.0f, 0.0f, 0.0f};
const srtColor SRT_GREEN =   {1.0f, 0.0f, 1.0f, 0.0f};
const srtColor SRT_BLUE = 	 {1.0f, 0.0f, 0.0f, 1.0f};
const srtColor SRT_WHITE =   {1.0f, 1.0f, 1.0f, 1.0f};
const srtColor SRT_BLACK =	 {1.0f, 0.0f, 0.0f, 0.0f};
const srtColor SRT_ZERO =    {0.0f, 0.0f, 0.0f, 0.0f};
const srtColor SRT_YELLOW =  {1.0f, 1.0f, 1.0f, 0.0f};
const srtColor SRT_PURPLE =  {1.0f, 1.0f, 0.0f, 1.0f};

srtColor srtColor_Mult(const srtColor const *a, const srtColor const *b) {
	srtColor c = {a->a * b->a, a->r * b->r, a->g * b->g, a->b * b->b};
	return c;
}

srtColor srtColor_Mult_Scalar(const srtColor const *a, srtReal s) {
	srtColor c = {a->a * s, a->r * s, a->g * s, a->b * s};
	return c;
}

srtColor srtColor_Add(const srtColor const *a, const srtColor const *b) {
	srtColor c = {a->a + b->a, a->r + b->r, a->g + b->g, a->b + b->b};
	return c;
}

void srtColor_Saturate(srtColor *c) {
	if (c->a < 0.0f) c->a = 0.0f;
	else if (c->a > 1.0f) c->a = 1.0f;
	
	if (c->r < 0.0f) c->r = 0.0f;
	else if (c->r > 1.0f) c->r =1.0f;
	
	if (c->g < 0.0f) c->g = 0.0f;
	else if (c->g > 1.0f) c->g =1.0f;
	
	if (c->b < 0.0f) c->b = 0.0f;
	else if (c->b > 1.0f) c->b =1.0f;
}

int srtColor_Equals(const srtColor const *a, const srtColor const *b) {
	if (a->a != b->a)
		return 0;
	if (a->r != b->r)
		return 0;
	if (a->g != b->g)
		return 0;
	if (a->b != b->b)
		return 0;
	return 1;
}

void srtColor_Print(const srtColor const *c) {
	printf("{ %f, %f, %f, %f }", c->a, c->r, c->g, c->b);
}

unsigned int srtColor_MapRGBA(const srtColor const *c) {
	unsigned char val;
	unsigned int packed_color = 0;
	
	val = (unsigned char)(c->a * 255.0);
	packed_color = val << 24;
	
	val = (unsigned char)(c->r * 255.0);
	packed_color += val << 16;
	
	val = (unsigned char)(c->g * 255.0);
	packed_color += val << 8;
	
	val = (unsigned char)(c->b * 255.0);
	packed_color += val;
	
	return packed_color;
}

#endif