#pragma once

class System_OgreHandler : public Abstract_Single <System_OgreHandler>
{
	static	CRITICAL_SECTION	RenderBlocker;
	friend class Abstract_Single <System_OgreHandler>;
	friend int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int);

	bool Initialize();
protected:
	HWND							m_hWnd;

	SmartPtr<Ogre::Root>			m_pRoot;
	SmartPtr<Ogre::RenderWindow>	m_pRenderWindow;

	System_OgreHandler();
public:
	inline static int	IsRenderBlocked()	{	return (TryEnterCriticalSection(&System_OgreHandler::RenderBlocker) != 0);	}
	inline static void	BlockRender()		{	EnterCriticalSection(&System_OgreHandler::RenderBlocker);   }
	inline static void	UnblockRender()		{	LeaveCriticalSection(&System_OgreHandler::RenderBlocker);	}

	static bool Shutdown();

	inline Ogre::Root *			Root()		const { return m_pRoot.get(); }
	inline Ogre::RenderWindow *	Window()	const { return m_pRenderWindow.get(); } 

	SmartPtr<Ogre::SceneManager>	Display_SceneManager;
	SmartPtr<Ogre::Camera>			Display_Camera;
	SmartPtr<Ogre::Viewport>		Display_ViewPort;
};