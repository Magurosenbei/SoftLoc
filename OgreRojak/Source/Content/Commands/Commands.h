#pragma once

/* For 236 214 etc Control sequence, double taps not implemented yet */

class Content_Commands
{
	SmartPtr<System_OISHandler>	Registered_Input;
	std::vector<OIS::KeyCode>	mKeys;	
	std::vector<unsigned int>	mCommandStack;
public:
	Content_Commands();
	virtual ~Content_Commands();

	void Step(const float & Interval);
	inline std::vector<unsigned int>	Commands() const	{ return mCommandStack; }
	inline void							ClearCommands()		{ mCommandStack.clear(); }
};