#include "AssessmentScene.h"
#include <iostream>

AssessmentScene::AssessmentScene(int argc, char* argv[])
{
	start = time(0);

	InitGL(argc, argv);
	InitObjects();
	InitLighting();
	glutMainLoop();
}

void AssessmentScene::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glEnable(GL_DEPTH_TEST);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bailey Atkin assessment scene");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);

	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0, 1000);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

}

void AssessmentScene::InitLighting()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2;
	_lightData->Ambient.y = 0.2;
	_lightData->Ambient.z = 0.2;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;
}

void AssessmentScene::InitObjects()
{
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"penguins.raw", 512, 512);

	camera = new Camera();
	camera->eye.x = 5.0f; camera->eye.y = 5.0f; camera->eye.z = -5.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
	cube = new Cube(cubeMesh, texture, 0.0f, 0.0f, 0.0f);
}

void AssessmentScene::DisplayTime(string textToDisplay)
{
	glPushMatrix();
	glTranslatef(0.0, 3.0, 0.0);
	glScalef(0.01, 0.01, 1);
	glColor3f(1.0, 1.0, 1.0);
	for (auto ch : textToDisplay)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, ch);
	}
	glPopMatrix();
}

string AssessmentScene::GetTimeString()
{
	double seconds_since_start = difftime(time(0), start);
	int seconds = int(seconds_since_start);
	int minutes = 0;
	while (seconds > 60)
	{
		minutes += 1;
		seconds -= 60;
	}
	string timeString = std::to_string(minutes) + "m " + std::to_string(seconds) + "s";

	return timeString;
}

void AssessmentScene::Display()
{
	string timeString = GetTimeString();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//DRAW OBJECTS HERE
	cube->Draw();
	DisplayTime(timeString);

	glFlush();
	glutSwapBuffers();
}

void AssessmentScene::Update()
{

	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.z));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	cube->Update();
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera->center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();
}

void AssessmentScene::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'e')
		camera->eye.z -= 0.5;

	if (key == 'q')
		camera->eye.z += 0.5;

	if (key == ' ')
	{
		if (cube->rotating)
			cube->rotating = false;
		else
			cube->rotating = true;
	}

	if (key == 'a')
		cube->repositionCube(0);

	if (key == 'd')
		cube->repositionCube(1);

	if (key == 'w')
		cube->repositionCube(2);

	if (key == 's')
		cube->repositionCube(3);
}

AssessmentScene::~AssessmentScene(void)
{

}
