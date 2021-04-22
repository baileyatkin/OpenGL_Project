#include "GLUTCallbacks.h"
#include "AssessmentScene.h"

namespace GLUTCallbacks
{
	namespace
	{
		AssessmentScene* assessmentScene = nullptr;
	}

	void Init(AssessmentScene* gl)
	{
		assessmentScene = gl;
	}

	void Display()
	{
		if (assessmentScene != nullptr)
		{
			assessmentScene->Display();
		}
	}

	void Timer(int preferredRefresh)
	{
		int updateTime = glutGet(GLUT_ELAPSED_TIME);
		assessmentScene->Update();
		updateTime = glutGet(GLUT_ELAPSED_TIME) - updateTime;
		glutTimerFunc(preferredRefresh - updateTime, GLUTCallbacks::Timer, preferredRefresh);
	}

	void Keyboard(unsigned char key, int x, int y)
	{
		assessmentScene->Keyboard(key, x, y);
	}
}
