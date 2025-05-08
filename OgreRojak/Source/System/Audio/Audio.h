#pragma once

class System_Audio : public Abstract_Single <System_Audio> 
{
	friend int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int);
	friend class Abstract_Single <System_Audio>;
	bool Initialize();
	
protected:
	SmartPtr <FMOD::System> m_pSystem;
	System_Audio();
public:
	static bool Shutdown();

	void _3D_EarPosition(float * xyz);	// Must only contain 3 components of float data

	FMOD::Sound		*	LoadFile(const std::string & FilePath, bool _Stream = false, bool _3D = false);
	FMOD::Channel	*	RegisterChannel(FMOD::Sound * SND);
	
	virtual void Step(const float & Interval);
};