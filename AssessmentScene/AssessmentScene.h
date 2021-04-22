#pragma once
#include <Windows.h>
#include <time.h>
#include <string>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "GLUTCallbacks.h"
#include "Structures.h"
#include "Cube.h"
#include "MeshLoader.h"

#define REFRESHRATE 16

using namespace std;

class AssessmentScene
{
public:
	AssessmentScene(int argc, char* argv[]);
	~AssessmentScene(void);

	void Display();
	void Update();
	void Keyboard(unsigned char key, int x, int y);
	void InitObjects();
	void InitGL(int argc, char* argv[]);
	void InitLighting();
	void DisplayTime(string textToDisplay);
	string GetTimeString();

private:
	Camera* camera;
	Cube* cube;
	Vector4* _lightPosition;
	Lighting* _lightData;
	static unsigned char timer[];
	int menu;
	time_t start;
};

