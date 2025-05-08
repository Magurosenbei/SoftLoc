#pragma once

/* Load , unload all content here */
class Content_Map;
class Content_Wall;
class Content_Screen;

class Content_Handler : public System_Thread
{
	
	bool	mbLoaded;	// If content has already loaded
protected:
	virtual bool	ThreadProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void	Work(const float & Interval);		// Loading done in this function

	SmartPtr<Ogre::SceneManager>						m_pSceneManager;
	SmartPtr<Ogre::Viewport>							m_pViewPort;
	SmartPtr<System_Camera>								m_pCamera;
	
	System_ResourceCloner	*							m_pBallCloner;
	btAlignedObjectArray <Content_Deformable_Object *>	m_SoftBodies;
	Content_Map				*							m_pMap;

	float												m_fTimeElapsed;

	System_OverlayText				*					m_Text;
	Ogre::TextAreaOverlayElement	*					m_TimeText;	
	int volume;
	FMOD::Sound *   _background;
	FMOD::Channel * _backgroundC;

	FMOD::Sound *   _CompleteLevel;
	FMOD::Channel * _CompleteLevelC;
public:
	Content_Screen	*	m_pGameOverScreen;

	static	unsigned int Level_ID;
	static	unsigned int Level_TOTAL;

	Content_Handler();
	~Content_Handler();

	inline	void		TimeReset()				{	m_fTimeElapsed = 0.0f;	}
	inline	const float	TimeElapsed()	const	{	return m_fTimeElapsed;	}
	inline	const bool	ContentLoaded() const	{	return mbLoaded;		}	// Whether content has finish loading
	inline	void		SetVolume( int vol)		{ volume = vol;}
	
	/* Load/Unload */
	void	Load(const std::string & DefnitionFile);	// Load up data, starts a thread to do all I/O
	void	Unload();									// free up memory

	bool	Initialize();								// Add stuff to scene manager
	bool	Uninitialize();								// remove stuff from scene manager


	void	Step(const float & Interval);				
	// Updates All Objects, Merging of Physics data and Grahpic data can be done here
};