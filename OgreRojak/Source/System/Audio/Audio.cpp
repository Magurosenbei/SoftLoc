#include "stdafx.h"
#include "Audio.h"

SmartPtr <System_Audio>	Abstract_Single <System_Audio> :: m_pInstance(NULL);

System_Audio :: System_Audio()
:m_pSystem(NULL)
{
	Label = "System_Audio";
}

bool System_Audio :: Initialize()
{
	FMOD_RESULT Result;
	FMOD::System * sys;
	Result = FMOD::System_Create(&sys);
	if(Result != FMOD_OK) return false;
	m_pSystem = SmartPtr <FMOD::System>(sys);
	sys = NULL;
	Result = m_pSystem->init(16, FMOD_INIT_NORMAL, NULL);
	if(Result != FMOD_OK) return false;
	
	return true;
}

bool System_Audio :: Shutdown()
{
	if(!m_pInstance->m_pSystem.get()) return false;
	m_pInstance->m_pSystem->release();
	//m_pInstance->m_pSystem.reset(NULL);
	m_pInstance->m_pSystem.release();
	return true;
}

void System_Audio :: _3D_EarPosition(float * xyz)
{
	m_pSystem->set3DListenerAttributes(NULL, (FMOD_VECTOR *)xyz, NULL, NULL, NULL);
}

FMOD::Sound		*	System_Audio :: LoadFile(const std::string & FilePath, bool _Stream, bool _3D)
{
	FMOD::Sound * SND (NULL);
	FMOD_RESULT RSLT;
	if(_Stream)
		RSLT = m_pSystem->createStream(FilePath.c_str(), 
		(_3D)? FMOD_3D : FMOD_DEFAULT, NULL, &SND);
	else
		RSLT = m_pSystem->createSound(FilePath.c_str(), 
		(_3D)? FMOD_3D : FMOD_DEFAULT, NULL, &SND);
	if(RSLT != FMOD_OK) return NULL;
	return SND;
}

FMOD::Channel	*	System_Audio :: RegisterChannel(FMOD::Sound * SND)
{
	FMOD::Channel * CHL (NULL);
	FMOD_RESULT RSLT = m_pSystem->playSound(FMOD_CHANNEL_FREE, SND, false, &CHL);
	if(RSLT != FMOD_OK) return NULL;
	return CHL;
}

void System_Audio :: Step(const float & Interval)
{
	m_pSystem->update();
}