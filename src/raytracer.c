#include "srtAssert.h"
#include "srtBuffer.h"
#include "srtRay.h"
#include "srtScene.h"

void handleAssertFailure(const char *condition, const char *file, int line, const char *msg, ...) {
	printf("Assertion Failed: %s\n", condition);
	printf("In file:%s at line:%d\n", file, line);
	if (msg) {
		va_list argp;
		va_start(argp, msg);
		vprintf(msg, argp);
		va_end(argp);
	}
	exit(EXIT_FAILURE);
}

void shutdown_ray_tracer() {
	SDL_Quit();
}


void draw_raytracer() {
	srtLightingEnabled(1);
	srtSuperSamplingEnabled(1);
	
	/*srtPerspective(SRT_DEFAULT_FOV, 4.0 / 3.0, 1.0);*/
	
	srtMatrix44 rotMat;
	srtMat44_RotationY(rotMat, SRT_PI);
	srtVector3 test = SRT_VECTOR3_UNIT_Z;
	
	printf("Normal Before Normal Xform: ");
	srtVec3_Print(&test);
	printf("\n");
	
	srtMatrixMode(SRT_PROJECTION);
	/*
	srtMatrix44 camRotMat, camTransMat;
	srtMat44_RotationY(camRotMat, 0.0);
	srtMat44_Translation(camTransMat, 0.0, 0.0, 6.5);
	
	srtMatrix44 cameraTransform;
	srtMat44_Mult(camTransMat, camRotMat, cameraTransform);
	srtLoadMatrix(cameraTransform);
	*/
	
	srtTranslate(0.0, 0.0, 4.5);
	/*srtRotate(-25, 0, 1, 0);*/
	
	srtMatrixMode(SRT_MODELVIEW);
	
	
	test = srtMat44_Transform_Normal(&test, rotMat);
	
	printf("Normal After Normal Xfrom: ");
	srtVec3_Print(&test);
	printf("\n");
	
	srtMat44_Transform_Normal(&test, rotMat);
	
	srtMatrix44 sceneTransform;
	srtMat44_Translation(sceneTransform, 0.0, 1.95, 0.0);
	srtLoadMatrix(sceneTransform);
	srtLoadIdentity();
	
	srtLightAmbient4(0.065f, 0.065f, 0.065f, 0.15f);
	srtLightDiffuse4(0.35, 0.35, 0.35, 0.35);
	srtLightSpecular4(0.25, 0.25, 0.25, 0.85);
	srtLightPosition3(-1.0, 1.1, -0.75);
	
	srtClearColor3(0.05f, 0.05f, 0.05f);
	srtClear();
	srtBeginScene();
	
	/* polygon */
	srtVector3 v0 = {-4.0, -1.5, 1.0}; 
	srtVector3 v1 = {4.0, -1.5, 1.0};
	srtVector3 v2 = {4.0, -1.5, -18.0};
	srtVector3 v3 = {-4.0, -1.5, -18.0};
	srtVector3 verts[4] = {v0, v1, v2, v3};
	
	srtMatAmbient4(0.85, 0.85, 0.85, 0.85);
	srtMatDiffuse4(0.65, 0.575, 0.525, 0.65);
	srtMatSpecular4(0.1, 0.1, 0.1, 0.3);
	srtMatShininess(0.25);
	srtMatReflectivity(0.3);
	
	srtCreatePolygon(verts, 4);
	
	/* Red sphere */
	srtMatAmbient4(1.0, 0.0, 0.0, 1.0);
	srtMatDiffuse4(0.45, 0.45, 0.45, 0.75);
	srtMatSpecular4(0.3, 0.3, 0.3, 0.35);
	srtMatShininess(2.8);
	srtMatReflectivity(0.45);
	srtCreateSphere4(1.1, -0.85, -4.5, 0.65);

	/* blue sphere */
	srtMatAmbient4(0.05, 0.025, 0.9, 1.0);
	srtMatDiffuse4(0.2, 0.15, 0.6, 0.7);
	srtMatSpecular4(0.2, 0.125, 0.085, 0.35);
	srtMatShininess(2.0);
	srtCreateSphere4(-1.65f, -0.75, -5.25, 0.75);
	
	/* transparent sphere */
	srtMatAmbient4(0.23, 0.21, 0.25, 0.4);
	srtMatDiffuse4(0.195, 0.183, 0.22, 0.35);
	srtMatSpecular4(0.2, 0.2, 0.2, 0.15);
	srtMatReflectivity(0.02);
	srtMatTransmission(0.895);
	srtMatShininess(5.46);
	srtMatRefraction(1.15);
	srtCreateSphere4(-0.05, -0.55, -2.5, 0.95);
	
	/* green box */
	srtMatAmbient4(0.2, 0.35, 0.15, 0.2);
	srtMatDiffuse4(0.1, 0.35, 0.1, 0.325);
	srtMatSpecular4(0.15, 0.15, 0.15, 0.35);
	srtMatTransmission(0.0);
	srtMatReflectivity(0.0);
	srtMatShininess(2.3);
	
	srtVector3 bc = {0.65, -1.15, -1.05};
	srtVector3 br = {0.35, 0.35, 0.35};
	srtMatrix44 bxform;
	srtMat44_RotationY(bxform, -0.35f);
	
	/*srtCreateBox(&bc, &br, bxform);*/
	
	srtEndScene();
	
	srtVector3 cameraPos = {0, 0.0, 4.5};
	srtVector3 up = SRT_VECTOR3_UNIT_Y;
	srtVector3 right = SRT_VECTOR3_UNIT_X;
	
	srtDrawScene();
	srtPaintBuffer();
	srtFlip();
}


void run_raytracer() {
	draw_raytracer();
	int QUIT = 0;
	SDL_Event event;
	while (!QUIT) {
		Uint8 *keydown;
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				/* close button clicked */
				case SDL_QUIT:
					QUIT = 1;
					break;
			}
		}
	}
	shutdown_ray_tracer();
}

int main(int argc, char *argv[]) {
	g_srtOnAssertFailure = &handleAssertFailure;
	srtCreateWindow(800, 600, "SRT: SDL Ray Tracer");
	run_raytracer();
}