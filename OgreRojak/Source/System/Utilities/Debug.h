#pragma once
/* Displays Information only */

class System_DebugDisplay	:	public Abstract_Single<System_DebugDisplay>
{
	SmartPtr<System_OverlayText>			m_pText;
	SmartPtr<Ogre::TextAreaOverlayElement>	m_pFPS;
	SmartPtr<Ogre::TextAreaOverlayElement>	m_pFrameInterval;

	float			TimePassed;
	unsigned int	FrameCount;
public:
	System_DebugDisplay();
	virtual ~System_DebugDisplay();

	inline System_OverlayText * TextWriter() const { return m_pText.get(); }

	virtual bool Initialize();
	static	bool Shutdown();

	void	Step(const float & Interval);
};