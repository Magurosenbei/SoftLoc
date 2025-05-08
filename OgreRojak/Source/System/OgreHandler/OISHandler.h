#pragma once

class System_OISHandler : public Abstract_Single<System_OISHandler>
{
	friend class Abstract_Single <System_OISHandler>;
	friend int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int);

	bool Initialize();

	bool					mKeyBuffer[256];
	OIS::MouseState			mLastMouseState;
protected:
	OIS::InputManager	*	m_pInput_Manager;
	OIS::Keyboard		*	Input_Keyboard;
	OIS::Mouse			*	Input_Mouse;
	OIS::JoyStick		*	Input_Controller;
public:
	System_OISHandler();
	
	/* Accessors for current state */
	inline			OIS::Mouse		*	MouseDevice()	const	{ return Input_Mouse; }
	inline const	OIS::MouseState &	Mouse()			const	{ return Input_Mouse->getMouseState(); }
	inline			OIS::Keyboard	*	Keyboard()		const	{ return Input_Keyboard; }
	inline			OIS::JoyStick	*	Controller()	const	{ return Input_Controller; }
	/* Keyboad typical Functions */
	inline	bool	KeyPressed(const OIS::KeyCode & key) const { return Input_Keyboard->isKeyDown(key) && !mKeyBuffer[key]; }
	inline	bool	KeyReleased(const OIS::KeyCode & key) const { return !Input_Keyboard->isKeyDown(key) && mKeyBuffer[key]; }
	
	/* Mouse typical Functions */
	inline const	OIS::MouseState &	Mouse_Previous() const	{ return mLastMouseState; }
	inline	bool	MouseButtonPressed(const OIS::MouseButtonID & button) const { return Mouse().buttonDown(button) && !mLastMouseState.buttonDown(button); }
	inline	bool	MouseButtonReleased(const OIS::MouseButtonID & button) const { return !Mouse().buttonDown(button) && mLastMouseState.buttonDown(button); }
	void			UpdateControls();

	static bool Shutdown();
};