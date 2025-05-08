#include "stdafx.h"
#include "Debug.h"

SmartPtr <System_DebugDisplay>	Abstract_Single<System_DebugDisplay> :: m_pInstance(NULL);

System_DebugDisplay :: System_DebugDisplay()
: m_pText(NULL), m_pFPS(NULL), m_pFrameInterval(NULL), TimePassed(0), FrameCount(0)
{
}

System_DebugDisplay :: ~System_DebugDisplay()
{
}

bool System_DebugDisplay :: Initialize()
{
	m_pText = SmartPtr<System_OverlayText>(new System_OverlayText("Debug", "bluehigh"));
	m_pFPS = SmartPtr<Ogre::TextAreaOverlayElement>(m_pText->AddTextBox("FPS", "FPS : 0", 15, 10, 16, Ogre::ColourValue::White));
	m_pFrameInterval = SmartPtr<Ogre::TextAreaOverlayElement>(m_pText->AddTextBox("Interval", "Interval : 0", 15, 20, 16, Ogre::ColourValue::White));
	return true;
}

bool System_DebugDisplay :: Shutdown()
{
	m_pInstance->m_pFrameInterval.release();
	m_pInstance->m_pFPS.release();

	m_pInstance->m_pText.reset(NULL);
	m_pInstance->m_pText.release();

	m_pInstance.reset(NULL);
	m_pInstance.release();
	return true;
}

void System_DebugDisplay :: Step(const float &Interval)
{
	if(TimePassed > 1.0f)
	{
		m_pFPS->setCaption(System_Utility::FormatText("FPS : %i", FrameCount));
		m_pFrameInterval->setCaption(System_Utility::FormatText("Interval : %f", Interval));
		TimePassed = 0.0f;
		FrameCount = 0;
	}
	TimePassed += Interval * 0.001f;
	FrameCount++;
}