#pragma once

//class Main_menu
//{
//	bool Active;
//	bool Animation;
//	Ogre::SceneManager  *	Menu_scenemanager;
//	Ogre::Viewport		*	Menu_viewport;
//	System_Overlay2D	*	m_play;
//	System_Overlay2D	*	test;
//
//	Ogre::ParticleSystem * Psys;
//
//	enum States{Play, Exit, Options};
//	States Menu_state;
//
//protected:
//	 bool Load();
//	 bool Unload();
//public:
//	 Main_menu();
//	 ~Main_menu();
//	 void Initialise();
//	 void Deinitialise();
//	 //---------------------//
//	 void Step(float Interval);
//	 void Switch_inGame(bool change);
//	 void Handle_State();
//};


class Main_menu
{
	bool Active;
	bool Animation;
	Ogre::SceneManager  *	Menu_scenemanager;
	Ogre::Viewport		*	Menu_viewport;
	System_Overlay2D	*	m_play;
	System_Overlay2D	*	m_exit;
	System_Overlay2D	*	m_options;
	System_Overlay2D	*	m_options_menu;
	System_Overlay2D	*	m_bar;

	enum States{Play, Exit, Options};
	States Menu_state;
	States tochange;

	float positionx1, positiony1;
	float positionx2, positiony2;
	float positionx3, positiony3;
	float scale1, scale2, scale3;
	float frameplay;
	float Barpos;
	int volume;

	bool _Options;

	System_OISHandler	*	local_InputHandler;
	
	FMOD::Sound *   _buttons;
	FMOD::Sound *   _background;
	FMOD::Channel * _backgroundC;
	FMOD::Channel * buttons;


protected:
	 bool Load();
	 bool Unload();
public:
	inline int getVolume() {return volume;}
	 Main_menu();
	 ~Main_menu();
	 void Initialise();
	 void Deinitialise();
	 //---------------------//
	 void Step(float Interval);
	 void Switch_inGame(bool change);
	 void Handle_State();
	 void Open_Audio_Options();
	 void Open_Exit_Options();
};