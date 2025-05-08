#include "stdafx.h"
#include "interface.h"

System_CEGUIInterface :: System_CEGUIInterface(Ogre::SceneManager * Manager)
:	Registered_SceneManager(Manager), Registered_Input(NULL),
	Interface_System(NULL), Interface_Renderer(NULL), Interface_RootWindow(NULL)
{
}

System_CEGUIInterface :: ~System_CEGUIInterface()
{
	Registered_Input.release();
	Registered_SceneManager.release();
	Interface_RootWindow.release();
	if(Interface_System.get())
	{
		Interface_System.reset(NULL);
		Interface_System.release();
	}
	if(Interface_Renderer.get())
	{
		Interface_Renderer.reset(NULL);
		Interface_Renderer.release();
	}
}

bool System_CEGUIInterface :: InitializeLayout(const std::string & Layout, const std::string & Scheme)
{
	Interface_Renderer = SmartPtr<CEGUI::OgreCEGUIRenderer>(new CEGUI::OgreCEGUIRenderer(
						System_OgreHandler::Instance()->Window(), Ogre::RENDER_QUEUE_OVERLAY, 
						false, 3000, Registered_SceneManager.get()));

	Interface_System = SmartPtr<CEGUI::System>(new CEGUI::System(Interface_Renderer.get()));
	
	CEGUI::SchemeManager::getSingleton().loadScheme(Scheme.c_str(), "GUI");
	
	Interface_System->setDefaultMouseCursor("TaharezLook", "MouseArrow");	// have to replace

	CEGUI::MouseCursor::getSingleton().setImage(CEGUI::System::getSingleton().getDefaultMouseCursor());
	Interface_System->setGUISheet(CEGUI::WindowManager::getSingleton().loadWindowLayout(Layout.c_str()));

	if(!Registered_Input.get())
		Registered_Input = SmartPtr<System_OISHandler>(System_OISHandler::Instance());
	Registered_Input->Keyboard()->setEventCallback(this);
	Registered_Input->MouseDevice()->setEventCallback(this);
	return true;
}

void System_CEGUIInterface :: Step(const float &Interval)
{
	// Do something ?
}

bool System_CEGUIInterface :: mouseMoved(const OIS::MouseEvent & arg)
{
	Interface_System->injectMouseMove (arg.state.X.rel, arg.state.Y.rel);
	return true;
}	

bool System_CEGUIInterface :: mousePressed(const OIS::MouseEvent & arg, OIS::MouseButtonID id)
{
	Interface_System->injectMouseButtonDown(CEGUI::MouseButton(id));
	return true;
}

bool System_CEGUIInterface :: mouseReleased(const OIS::MouseEvent & arg, OIS::MouseButtonID id)
{
	Interface_System->injectMouseButtonUp(CEGUI::MouseButton(id));
	return true;
}

bool System_CEGUIInterface :: keyPressed(const OIS::KeyEvent & arg)
{
	Interface_System->injectKeyDown(arg.key);
	return true;
}

bool System_CEGUIInterface :: keyReleased(const OIS::KeyEvent & arg)
{	
	Interface_System->injectKeyUp(arg.key);
	return true;
}