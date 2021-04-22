#pragma once
class AssessmentScene;

namespace GLUTCallbacks
{
	void Init(AssessmentScene* gl);

	void Display();

	void Timer(int preferredRefresh);

	void Keyboard(unsigned char key, int x, int y);
}

