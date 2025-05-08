#include "stdafx.h"

#include "OgreHandler.h"

SmartPtr <System_OgreHandler>	Abstract_Single<System_OgreHandler> :: m_pInstance(NULL);
CRITICAL_SECTION System_OgreHandler :: RenderBlocker;

System_OgreHandler :: System_OgreHandler()
:	m_pRoot(NULL), m_pRenderWindow(NULL), 
	Display_SceneManager(NULL), Display_Camera(NULL), Display_ViewPort(NULL)
	//Interface_System(NULL), Interface_Renderer(NULL)
{
	Label = "System_OgreHandler";
}

bool System_OgreHandler :: Initialize()
{
	InitializeCriticalSection(&System_OgreHandler::RenderBlocker);
	m_pRoot = SmartPtr<Ogre::Root>(new Ogre::Root("Plugins/Plugins.ini"));
	if(!m_pRoot.get()) return false;


	Ogre::RenderSystem * RSys = m_pRoot->getRenderSystemByName("Direct3D9 Rendering Subsystem");
	RSys->setConfigOption("Full Screen", "no");
	RSys->setConfigOption("Video Mode", "640 x 480 @ 32-bit colour");
	RSys->setConfigOption("Floating-point mode", "fastest");
	m_pRoot->setRenderSystem(RSys);

	m_pRenderWindow = SmartPtr<Ogre::RenderWindow>(m_pRoot->initialise(true, APP_TITLE));
	if(!m_pRenderWindow.get())
		return false;
	m_pRenderWindow->getCustomAttribute("WINDOW", &m_hWnd);

	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

    HICON hIcon = NULL;				// handle to the main window's large icon
	HICON hIconSmall = NULL;		// handle to the main window's small icon

	hIcon		= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OGREROJAK));
	hIconSmall	= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	hIcon		= (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_OGREROJAK), IMAGE_ICON, GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	hIconSmall	= (HICON)LoadImage(hInstance, MAKEINTRESOURCE(IDI_SMALL), IMAGE_ICON, GetSystemMetrics(SM_CXSMICON), GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SendMessage(m_hWnd, WM_SETICON, (WPARAM)ICON_BIG, (LPARAM)hIcon);
	SendMessage(m_hWnd, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hIconSmall);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Assets",				"FileSystem", "General");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Assets/Gui",			"FileSystem", "GUI");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Assets/Interface",	"FileSystem", "GUI");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Assets/Shaders",		"FileSystem", "Shaders");
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Assets/Primitives",	"FileSystem", "Primitives");

	try
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch(Ogre::Exception &e)
	{
		UNREFERENCED_PARAMETER(e);
		WriteCommandLine("E%s", e.what());
	}
	Display_SceneManager = SmartPtr<Ogre::SceneManager>(m_pRoot->createSceneManager(Ogre::ST_GENERIC, "Default_SceneManager"));
	
	if(!Display_SceneManager.get())
		return false;

	/* Lightings etc */
	Display_SceneManager->setAmbientLight(Ogre::ColourValue(0.4f, 0.4f, 0.4f));
	Display_Camera = SmartPtr<Ogre::Camera>(Display_SceneManager->createCamera("NO_CLIP"));
	if(!Display_Camera.get())
		return false;
	Display_Camera->setFarClipDistance(1000);
	Display_Camera->setNearClipDistance(1);
	Display_Camera->setAspectRatio(4.0f / 3.0f);
	

	Display_Camera->setPosition(Ogre::Vector3(0, 50, -200));
	Display_Camera->lookAt(Ogre::Vector3(0, 50, 200));
	
	Display_ViewPort = SmartPtr<Ogre::Viewport>(m_pRenderWindow->addViewport(Display_Camera.get()));
	if(!Display_ViewPort.get())
		return false;
	Display_ViewPort->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	Ogre::Light * DirLight = Display_SceneManager->createLight("Sun");
	DirLight->setType(Ogre::Light::LT_POINT);
	DirLight->setPosition(Ogre::Vector3(100, 50, -100));
	DirLight->setDirection(Ogre::Vector3(1, -1, 1));
	DirLight->setDiffuseColour(0.4f, 0.4f, 0.4f);
	Display_SceneManager->setFindVisibleObjects(false);
	return true;
}

bool System_OgreHandler :: Shutdown()
{
	m_pInstance->Display_SceneManager.release();
	m_pInstance->Display_Camera.release();
	m_pInstance->Display_ViewPort.release();

	m_pInstance->m_pRenderWindow->removeAllListeners();
	m_pInstance->m_pRenderWindow->removeAllViewports();
	m_pInstance->m_pRenderWindow.release();

	m_pInstance->m_pRoot.reset(NULL);
	m_pInstance->m_pRoot.release();

	DeleteCriticalSection(&System_OgreHandler::RenderBlocker);
	return true;
}