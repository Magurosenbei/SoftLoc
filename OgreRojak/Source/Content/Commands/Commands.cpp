#include "stdafx.h"
#include "commands.h"

#define MAX_COMMAND 3

Content_Commands :: Content_Commands()
{
	mKeys.push_back(OIS::KC_UP);
	mKeys.push_back(OIS::KC_DOWN);
	mKeys.push_back(OIS::KC_LEFT);
	mKeys.push_back(OIS::KC_RIGHT);
}

Content_Commands :: ~Content_Commands()
{
	Registered_Input.release();
}

void Content_Commands :: Step(const float &Interval)
{
	if(!Registered_Input.get())
		Registered_Input = SmartPtr<System_OISHandler>(System_OISHandler::Instance());
	
	bool DEF[4] = { false, false, false, false };
	bool Nothing = true;
	int totalpressed = 0;
	for(size_t i = 0; i < mKeys.size(); i++)
	{
		DEF[i] = Registered_Input->Keyboard()->isKeyDown(mKeys[i]);
		if(DEF[i])
		{
			Nothing = false;
			totalpressed++;
		}
	}
	if(Nothing) return;
	unsigned int Value = 0;
	if(totalpressed == 1)
	{
		if(DEF[0])
			Value = 8;
		else if(DEF[1])
			Value = 2;
		else if(DEF[2])
			Value = 4;
		else
			Value = 6;
		goto RESOLVE;
	}
	if(DEF[0] && DEF[2])
		Value =  7;
	else if(DEF[0] && DEF[3])
		Value = 9;
	else if(DEF[1] && DEF[2])
		Value = 1;
	else if(DEF[1] && DEF[3])
		Value = 3;
RESOLVE:
	if(mCommandStack.size() < 1)
		mCommandStack.push_back(Value);
	else if(mCommandStack.back() != Value)
		mCommandStack.push_back(Value);
	if(mCommandStack.size() > MAX_COMMAND)
	{
		WriteCommandLine("%i %i %i", mCommandStack[0], mCommandStack[1], mCommandStack[2]);
		mCommandStack.clear();
	}
}