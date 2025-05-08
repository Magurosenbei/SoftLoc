#include "stdafx.h"
#include "OISHandler.h"

SmartPtr <System_OISHandler>	Abstract_Single<System_OISHandler> :: m_pInstance(NULL);

System_OISHandler :: System_OISHandler()
:	m_pInput_Manager(NULL), Input_Keyboard(NULL), Input_Mouse(NULL), Input_Controller(NULL)
{
	Label = "System_OISHandler";
}

bool System_OISHandler :: Initialize()
{
	try
	{
		OIS::ParamList params;
		unsigned int Hwnd(0);
		System_OgreHandler::Instance()->Window()->getCustomAttribute("WINDOW", &Hwnd);
		std::ostringstream HwndStr;
		HwndStr << Hwnd;
		params.insert(std::make_pair("WINDOW", HwndStr.str()));
		params.insert(std::make_pair("w32_mouse", "DISCL_NONEXCLUSIVE"));
		params.insert(std::make_pair("w32_mouse", "DISCL_FOREGROUND"));

		m_pInput_Manager = OIS::InputManager::createInputSystem(params);
		
		
		if(!m_pInput_Manager) return false;
		if(m_pInput_Manager->numKeyboards() < 1) 
			throw OIS::Exception(OIS::E_InvalidParam, "There is no Keyboard", 1, NULL);	// No Keyboard
		if(m_pInput_Manager->numMice() < 1) 
			throw OIS::Exception(OIS::E_InvalidParam, "There is no Mouse", 1, NULL);

		Input_Keyboard	= static_cast<OIS::Keyboard *>(m_pInput_Manager->createInputObject(OIS::OISKeyboard, true));
		if(!Input_Keyboard) return false;
		Input_Mouse		= static_cast<OIS::Mouse *>(m_pInput_Manager->createInputObject(OIS::OISMouse, true));
		Input_Mouse->getMouseState().width = System_OgreHandler::Instance()->Window()->getWidth();
		Input_Mouse->getMouseState().height = System_OgreHandler::Instance()->Window()->getHeight();
		if(!Input_Mouse) return false;

		//Input_Controller = static_cast<OIS::JoyStick *>(m_pInput_Manager->createInputObject(OIS::OISJoyStick, true));
	}
	catch(OIS::Exception & e)
	{
		MessageBoxA(NULL, e.eText, "OIS startup Error", MB_ICONERROR | MB_OK);
		return false;
	}
	return true;
}

bool System_OISHandler :: Shutdown()
{
	m_pInstance->m_pInput_Manager->destroyInputObject(m_pInstance->Input_Keyboard);
	m_pInstance->m_pInput_Manager->destroyInputObject(m_pInstance->Input_Mouse);
	m_pInstance->m_pInput_Manager->destroyInputObject(m_pInstance->Input_Controller);
	
	m_pInstance->Input_Keyboard = NULL;
	m_pInstance->Input_Mouse = NULL;
	m_pInstance->Input_Controller = NULL;

	OIS::InputManager::destroyInputSystem(m_pInstance->m_pInput_Manager);
	m_pInstance->m_pInput_Manager = NULL;
	return true;
}

void System_OISHandler :: UpdateControls()
{
	Input_Keyboard->copyKeyStates((char *)mKeyBuffer);
	Input_Keyboard->capture();

	mLastMouseState = Input_Mouse->getMouseState();
	Input_Mouse->capture();
}