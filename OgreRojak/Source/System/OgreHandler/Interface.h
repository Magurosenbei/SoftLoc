#pragma once

class System_CEGUIInterface : public OIS::MouseListener, public OIS::KeyListener
{
	SmartPtr<Ogre::SceneManager>		Registered_SceneManager;
	SmartPtr<System_OISHandler>			Registered_Input;
protected:
	SmartPtr<CEGUI::System>				Interface_System;
	SmartPtr<CEGUI::OgreCEGUIRenderer>	Interface_Renderer;
	SmartPtr<CEGUI::Window>				Interface_RootWindow;
public:
	System_CEGUIInterface(Ogre::SceneManager * Manager);
	~System_CEGUIInterface();

	bool InitializeLayout(const std::string & Layout, const std::string & Scheme);

	void Step(const float & Interval);

	/* Input Events */
	bool mouseMoved(const OIS::MouseEvent & arg);
	bool mousePressed(const OIS::MouseEvent & arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent & arg, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent &arg);
	bool keyReleased(const OIS::KeyEvent &arg);
};