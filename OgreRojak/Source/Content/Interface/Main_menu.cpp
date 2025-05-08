#include "stdafx.h"
#include "Main_menu.h"

Main_menu::Main_menu()
:	Menu_scenemanager(NULL)
{
	local_InputHandler = System_OISHandler::Instance();
}

Main_menu::~Main_menu()
{
	local_InputHandler = NULL;
	Menu_scenemanager = NULL;
	Menu_viewport = NULL;

	delete m_play; m_play = NULL;
	delete m_exit; m_exit = NULL;
	delete m_options; m_options = NULL;
	delete m_options_menu; m_options_menu = NULL;
	delete m_bar; m_bar = NULL;

	_buttons->release();
	_background->release();	
}

void Main_menu	::	Initialise()
{
	Menu_state = Play;
	tochange = Play;

	Active = Animation = false;

	Menu_scenemanager = System_OgreHandler::Instance()->Root()->createSceneManager(Ogre::ST_GENERIC, "Menu scenemanager");

	m_play = new System_Overlay2D("Menu_Buttons");
	m_exit = new System_Overlay2D("Menu_Buttons 1 ");
	m_options = new System_Overlay2D("Menu_Buttons 2 ");
	m_options_menu  = new System_Overlay2D("Options Menu");
	m_bar = new System_Overlay2D("Bar");
	
	scale1 = 260;
	scale2 = 0.5;
	frameplay = 0;
	positionx1 = 260; positionx2 = 520;positionx3 = 50;
	positiony1 = 200; positiony2 = 140;positiony3 = 140;
	scale1 = 128; scale2 = 78; scale3 = 78;

	Barpos = 330;
	_Options = false;
	volume = 250;
	//Creating Loading page here and set it showing
	//....................... 
	Load();
}

bool Main_menu	::	Load()
{
	//Create the camera
	Ogre::Camera * camera = Menu_scenemanager->createCamera("NO_CLIP");
	camera->setPosition(Ogre::Vector3(0, 0, -200));
	camera->lookAt(Ogre::Vector3(0, 0, 200));


	//Create the background
	Ogre::Plane PLane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"Floor", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		PLane, 300, 300, 1, 1, true,  1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::Entity * Floor = Menu_scenemanager->createEntity("floor", "Floor");
	Menu_scenemanager->getRootSceneNode()->createChildSceneNode()->attachObject(Floor);
	Floor->getParentNode()->rotate(Ogre::Vector3(1, 0, 0), Ogre::Radian(Ogre::Degree(-90)));
	Floor->setMaterialName("Background");
	
	
	camera->setPosition(Ogre::Vector3(0, 50, -200));
	camera->lookAt(Ogre::Vector3(0, 50, 200));

	Menu_viewport = System_OgreHandler::Instance()->Window()->addViewport(camera, 10);
	Menu_viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0, 0));

	//Create Lighting etc etc
	Menu_scenemanager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light * DirLight = Menu_scenemanager->createLight("Sun");
	DirLight->setType(Ogre::Light::LT_POINT);
	DirLight->setPosition(Ogre::Vector3(0, 100, -100));
	DirLight->setDirection(Ogre::Vector3(1, -1, 1));
	DirLight->setDiffuseColour(0.4f, 0.4f, 0.4f);
	
	// Add my sphere :D
	Ogre::Entity * Sphere = Menu_scenemanager->createEntity("sphere", "sphere.mesh");
	Menu_scenemanager->getRootSceneNode()->createChildSceneNode()->attachObject(Sphere);
	Sphere->getParentNode()->setPosition(Ogre::Vector3(0, 50, 0));
	Sphere->getParentNode()->scale(Ogre::Vector3(3, 3, 3));
	Sphere->setMaterialName("TF2NPR");
	//
	// Add buttons
		// --create the containers//
	m_options_menu->AddElement("Options_Menu", "Options_menu", 125, 200,
										  400, 200);
	m_bar->AddElement("Bar", "Options_bar", 160, 320,
										  330, 30);
	m_play->AddElement("Button_Start", "Play", 260, 200,
										  128, 128);
	m_exit->AddElement("Button_Quit", "Exit", 520, 140,
										 78, 78);
	m_options->AddElement("Button_Options", "Options", 50, 140,
										  78, 78);
	m_play->m_pOverlay->show();
	m_play->m_pOverlay->setZOrder(0);
	m_exit->m_pOverlay->show();
	m_exit->m_pOverlay->setZOrder(0);
	m_options->m_pOverlay->show();
	m_options->m_pOverlay->setZOrder(0);

	m_options_menu->m_pOverlay->setZOrder(300);
	m_bar->m_pOverlay->setZOrder(450);

	_buttons     = System_Audio::Instance()->LoadFile("Assets/Audio/sound24.mp3");
	_background =  System_Audio::Instance()->LoadFile("Assets/Audio/Menu_background.wav", true);
	_background->setLoopCount(-1);


	_backgroundC = System_Audio::Instance()->RegisterChannel(_background);
	Active = true;

	return true;	
}

void Main_menu::Deinitialise()
{
}

void Main_menu::Step(float Interval)
{
	if(Animation)
	{
		if(Menu_state == tochange)
		{
			Animation = false;
			return;
		}

		if(Menu_state == Play)
		{
			if(tochange == Exit)
			{
				if(frameplay != 52)
				{
					m_play->m_pPanel->getChild("Play")->setPosition(positionx1-= 4, positiony1-= 1.15);
					m_play->m_pPanel->getChild("Play")->setDimensions(scale1-= 0.5, scale1 -= 0.5);
					m_exit->m_pPanel->getChild("Exit")->setPosition(positionx2-= 5.2, positiony2 += 1.15);
					m_exit->m_pPanel->getChild("Exit")->setDimensions(scale2 += 0.5, scale2 += 0.5);
					if(frameplay > 5 && frameplay < 45)
						m_options->m_pOverlay->hide();
					else
						m_options->m_pOverlay->show();

					m_options->m_pPanel->getChild("Options")->setPosition(positionx3 += 9.0 , positiony3);
					m_options->m_pPanel->getChild("Options")->setDimensions(scale3, scale3);
					frameplay++;
				}
				else
				{
					frameplay = 0;
					scale3 = scale1 = 78;
					scale2 = 128;
					positionx1 = 50;
					positiony1 = 140;
					positionx2 = 260;
					positiony2 = 200;
					positionx3 = 520;
					positiony3 = 140;
					Animation = false;
					Menu_state = Exit;
				}
			
			}
			else
			{
				if(frameplay != 52)
				{
					m_play->m_pPanel->getChild("Play")->setPosition(positionx1+= 5.2, positiony1-= 1.15);
					m_play->m_pPanel->getChild("Play")->setDimensions(scale1-= 0.5, scale1 -= 0.5);
					m_options->m_pPanel->getChild("Options")->setPosition(positionx3 += 4, positiony3 += 1.15);
					m_options->m_pPanel->getChild("Options")->setDimensions(scale3 += 0.5, scale3 += 0.5 );
					
					if(frameplay > 5 && frameplay < 45)
						m_exit->m_pOverlay->hide();
					else
						m_exit->m_pOverlay->show();
					m_exit->m_pPanel->getChild("Exit")->setPosition(positionx2 -= 9.0, positiony2);
					m_exit->m_pPanel->getChild("Exit")->setDimensions(scale2 , scale2);
					frameplay++;
				}
				else
				{
					frameplay = 0;
					scale2 = scale1 = 78;
					scale3 = 128;
					positionx1 = 520;
					positiony1 = 140;
					positionx2 = 50;
					positiony2 = 140;
					positionx3 = 260;
					positiony3 = 200;
					Animation = false;
					Menu_state = Options;
				}
			}
		}
		else if(Menu_state == Exit)
		{
			if(tochange == Play)
			{
				if(frameplay != 52)
				{
					m_exit->m_pPanel->getChild("Exit")->setPosition(positionx2+= 5.2, positiony2-= 1.15);
					m_exit->m_pPanel->getChild("Exit")->setDimensions(scale2-= 0.5, scale2 -= 0.5);
					m_play->m_pPanel->getChild("Play")->setPosition(positionx1 += 4, positiony1 += 1.15);
					m_play->m_pPanel->getChild("Play")->setDimensions(scale1 += 0.5, scale1 += 0.5 );
					
					if(frameplay > 5 && frameplay < 45)
						m_options->m_pOverlay->hide();
					else
						m_options->m_pOverlay->show();
					m_options->m_pPanel->getChild("Options")->setPosition(positionx3 -= 9.0, positiony3);
					m_options->m_pPanel->getChild("Options")->setDimensions(scale3 , scale3);
					frameplay++;
				}
				else
				{
					frameplay = 0;
					scale2 = scale3 = 78;
					scale1 = 128;
					positionx1 = 260;
					positiony1 = 200;
					positionx2 = 520;
					positiony2 = 140;
					positionx3 = 50;
					positiony3 = 140;
					Animation = false;
					Menu_state = Play;
				}
			
			}
			else
			{
				if(frameplay != 52)
				{
					m_exit->m_pPanel->getChild("Exit")->setPosition(positionx2 -= 4, positiony2-= 1.15);
					m_exit->m_pPanel->getChild("Exit")->setDimensions(scale2-= 0.5, scale2 -= 0.5);
					m_options->m_pPanel->getChild("Options")->setPosition(positionx3-= 5.2, positiony3 += 1.15);
					m_options->m_pPanel->getChild("Options")->setDimensions(scale3 += 0.5, scale3 += 0.5);
					if(frameplay > 5 && frameplay < 45)
						m_play->m_pOverlay->hide();
					else
						m_play->m_pOverlay->show();

					m_play->m_pPanel->getChild("Play")->setPosition(positionx1 += 9.0, positiony1);
					m_play->m_pPanel->getChild("Play")->setDimensions(scale1, scale1);
					frameplay++;
				}
				else
				{
					frameplay = 0;
					scale2 = scale1 = 78;
					scale3 = 128;
					positionx1 = 520;
					positiony1 = 140;
					positionx2 = 50;
					positiony2 = 150;
					positionx3 = 260;
					positiony3 = 200;
					Animation = false;
					Menu_state = Options;
				}
			}
		}
		else
		{
			if(tochange == Play){
				if(frameplay != 52)
				{
					m_options->m_pPanel->getChild("Options")->setPosition(positionx3-= 4, positiony3-= 1.15);
					m_options->m_pPanel->getChild("Options")->setDimensions(scale3-= 0.5, scale3 -= 0.5);
					m_play->m_pPanel->getChild("Play")->setPosition(positionx1-= 5.2, positiony1 += 1.15);
					m_play->m_pPanel->getChild("Play")->setDimensions(scale1 += 0.5, scale1 += 0.5);
					if(frameplay > 5 && frameplay < 45)
						m_exit->m_pOverlay->hide();
					else
						m_exit->m_pOverlay->show();

					m_exit->m_pPanel->getChild("Exit")->setPosition(positionx2 += 9.0, positiony2);
					m_exit->m_pPanel->getChild("Exit")->setDimensions(scale2, scale2);
					frameplay++;
				}
				else
				{
					frameplay = 0;
					scale3 = scale1 = 78;
					scale1 = 128;
					positionx1 = 260;
					positiony1 = 200;
					positionx2 = 520;
					positiony2 = 140;
					positionx3 = 50;
					positiony3 = 140;
					Animation = false;
					Menu_state = Play;
				}
			}
			else
			{
				if(frameplay != 52)
				{
					m_options->m_pPanel->getChild("Options")->setPosition(positionx3+= 5.2, positiony3 -= 1.15);
					m_options->m_pPanel->getChild("Options")->setDimensions(scale3-= 0.5, scale3 -= 0.5);
					m_exit->m_pPanel->getChild("Exit")->setPosition(positionx2 += 4, positiony2 += 1.15);
					m_exit->m_pPanel->getChild("Exit")->setDimensions(scale2 += 0.5, scale2 += 0.5);
					
					if(frameplay > 5 && frameplay < 45)
						m_play->m_pOverlay->hide();
					else
						m_play->m_pOverlay->show();

					m_play->m_pPanel->getChild("Play")->setPosition(positionx1 -= 9.0, positiony1);
					m_play->m_pPanel->getChild("Play")->setDimensions(scale1, scale1);
					frameplay++;
				}
				else
				{
					frameplay = 0;
					scale3 = scale1 = 78;
					scale2 = 128;
					positionx1 = 50;
					positiony1 = 140;
					positionx2 = 260;
					positiony2 = 200;
					positionx3 = 520;
					positiony3 = 140;
					Animation = false;
					Menu_state = Exit;
				}
			}
		
		}
		return;
	}
	else
	{
		if(local_InputHandler->KeyPressed(OIS::KC_ESCAPE))
		{
			if(_Options == true)
				Open_Audio_Options();
			else
				g_sAPP_STAT = QUIT;
		}
		if(local_InputHandler->KeyPressed(OIS::KC_RETURN))
		{
			Handle_State();
		}
		if(local_InputHandler->KeyPressed(OIS::KC_LEFT))
		{
			if(_Options)
			{
				if(Barpos <= 0)
					return;
				else
					Barpos -= 33;
				m_bar->m_pPanel->getChild("Options_bar")->setDimensions(Barpos, 30);
				(volume == 0)?  volume = 0 : volume-= 25;
				_backgroundC->setVolume(volume);
				buttons = System_Audio::Instance()->RegisterChannel(_buttons);
				buttons->setVolume(volume);
				return;
			}
			Animation = true;
			if(tochange == Play)
				tochange = Exit;
			else if(tochange == Options)
				tochange = Play;
			else{
				tochange = Options;
			}
			buttons = System_Audio::Instance()->RegisterChannel(_buttons);
			buttons->setVolume(volume);
		}
		if(local_InputHandler->KeyPressed(OIS::KC_RIGHT))
		{
			if(_Options)
			{
				if(Barpos >= 330)
					return;
				else
					Barpos += 33;
				m_bar->m_pPanel->getChild("Options_bar")->setDimensions(Barpos, 30);
				(volume <= 250)? volume+= 25: volume = 0;
				_backgroundC->setVolume(volume);
				buttons = System_Audio::Instance()->RegisterChannel(_buttons);
				buttons->setVolume(volume);
				return;
			}
			Animation = true;
			if(tochange == Play)
				tochange = Options;
			else if(tochange == Options)
				tochange = Exit;
			else{
				tochange = Play;
			}
			buttons = System_Audio::Instance()->RegisterChannel(_buttons);
			buttons->setVolume(volume);
		}
	}
}
void Main_menu::Switch_inGame(bool change)
{
	if(!Menu_scenemanager) return;

	if(change)
	{
		System_OgreHandler::Instance()->Window()->removeViewport(10);
		m_play->m_pOverlay->hide();
		m_exit->m_pOverlay->hide();
		m_options->m_pOverlay->hide();

		_backgroundC->stop();
	}
	else
	{
		//_background =  System_Audio::Instance()->LoadFile("Menu_background.mp3", true);
		//_background->setLoopCount(-1);
		_backgroundC = System_Audio::Instance()->RegisterChannel(_background);
	
		Menu_viewport = System_OgreHandler::Instance()->Window()->addViewport(Menu_scenemanager->getCamera("NO_CLIP"), 10);
		Menu_viewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
		m_play->m_pOverlay->show();
		m_exit->m_pOverlay->show();
		m_options->m_pOverlay->show();
	}
}
void Main_menu::Handle_State()
{
	//m_play->m_pOverlay->hide();
	if(Menu_state == Play)
	{
		_backgroundC->stop();
		m_play->m_pOverlay->hide();
		m_options->m_pOverlay->hide();
		m_exit->m_pOverlay->hide();
		g_sAPP_STAT = GAME;
	}
	if(Menu_state == Exit)
		g_sAPP_STAT = QUIT;
	if(Menu_state == Options)
		Open_Audio_Options();
}
void Main_menu::Open_Audio_Options()
{
	if(!_Options)
	{
		_Options = true;
		m_options_menu->m_pOverlay->show();
		m_bar->m_pOverlay->show();
	}
	else
	{
		_Options = false;
		m_options_menu->m_pOverlay->hide();
		m_bar->m_pOverlay->hide();
	}
}