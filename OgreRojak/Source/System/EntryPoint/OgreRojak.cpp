#include "stdafx.h"
#include "OgreRojak.h"

#include "System/OgreHandler/OgreHandler.h"
#include "System/Audio/Audio.h"
#include "System/Physics/Physics.h"
#include "../../Content/Interface/Main_menu.h"
#include "../../Content/Interface/GameOver.h"


bool APP_STATE_PHY = true;	//	This will turn on / off physics

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

int APIENTRY _tWinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif
	
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	MSG msg; 	msg.wParam = NULL;
	HACCEL hAccelTable;
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OGREROJAK));

	System_HiResTimer	local_clock;						// Timer
	float				Interval(0.0f), Difference(0.0f);
	bool				bExit = false;

	System_OgreHandler	* local_System_Graphic	= System_OgreHandler::Instance();
	System_OISHandler	* local_System_Input	= System_OISHandler::Instance();
	System_Audio		* local_System_Audio	= System_Audio::Instance();
	System_Physics		* local_System_Physics	= System_Physics::Instance();
	Main_menu			* menu  = new Main_menu();
	bool	Loaded = false;
	bool	Loaded2 = false;

	//FMOD::Sound * BGMSound = local_System_Audio->LoadFile("../Assets/Audio/EXEC_FLIP_ARPHAGE_..mp3", true);
	//FMOD::Channel * BGMChannel = local_System_Audio->RegisterChannel(BGMSound);

	Content_Screen_GameOver	*	GameOvr =	new Content_Screen_GameOver;
	Content_Screen_Loading	*	LoadScr	=	new Content_Screen_Loading;
	Content_Handler			*	Handler	=	new Content_Handler;

	Handler->m_pGameOverScreen = GameOvr;
	
	GameOvr->Initialize("NULL");
	GameOvr->Hide();
	LoadScr->Initialize("NULL");
	LoadScr->Hide();
	/* This chunk should be in Load but for sake of convience during development was put here */
	//System_CEGUIInterface	*	test_Interface	= new System_CEGUIInterface(local_System_Graphic->Display_SceneManager.get());

	System_DebugDisplay	*	local_System_Debug = System_DebugDisplay::Instance();

	while (!bExit)
	{
		Ogre::WindowEventUtilities::messagePump();
		if(!local_System_Graphic->Window()->isActive())
		{
			SleepEx(500, true);
			continue;
		}
		local_clock.Start();
		local_System_Input->UpdateControls();
		local_System_Audio->Step(Interval);
		if(KeyDown(VK_ESCAPE))
			g_sGAME_STAT = UNLOAD;

		switch(g_sAPP_STAT)
		{
		case APP_PHASE::SPLASH:
			// As the name suggest, just a simple 2D overlay that show some simple stuff, CMs, Ads etc
			break;
		case APP_PHASE::MENU:
			// Make sure that the menu states reset themselves before exiting to other Phases,
			// So that other phases can just directly call to jump into another phase
			if(!Loaded)
			{
				Loaded = true;
				menu->Initialise();	
			}
			menu->Step(0.16f);
			Handler->Level_ID = 0;
			Handler->TimeReset();
			break;
		case APP_PHASE::ENDING:
			// End of the game, there might be another GaneOver Phase.
			// usually lead to high score
			break;

		case APP_PHASE::QUIT:
			// Exit the program
			bExit = true;
			break;

		case APP_PHASE::GAME:
			// Proccess Game Only
			switch(g_sGAME_STAT)
			{
			case GAME_PHASE::LOAD_NEXT:
				if(!LoadScr->IsVisible())
				{

					APP_STATE_PHY = false;
					LoadScr->Show();
					local_System_Graphic->Display_SceneManager->setFindVisibleObjects(false);
					Handler->Unload();	
				}
				else
				{
					LoadScr->Step(0.16f);
					if(Handler->Ended())
					{
						LoadScr->Hide();
						if(Handler->Level_ID < Handler->Level_TOTAL)
						{
							g_sGAME_STAT = GAME_PHASE::LOAD;
							
						}
						else
						{
							// Game Over
							menu->Switch_inGame(false);
							g_sAPP_STAT = APP_PHASE::MENU;
							g_sGAME_STAT = GAME_PHASE::LOAD;
						}
					}
				}
				break;

			case GAME_PHASE::LOAD:
				// Start the loading Thread if not started,	set 2D to loading screen and wait for completion
				// When load complete set the bottom line
				menu->Switch_inGame(true);
				if(!LoadScr->IsVisible())
				{
					APP_STATE_PHY = false;
					LoadScr->Show();
					local_System_Graphic->Display_SceneManager->setFindVisibleObjects(false);
					Handler->Load("NULL");
				}
				else
				{
					
					LoadScr->Step(0.16f);
					if(Handler->Ended())
					{
						LoadScr->Hide();
				
						g_sGAME_STAT = PLAY;
						local_System_Graphic->Display_SceneManager->setFindVisibleObjects(true);
						APP_STATE_PHY = true;
					}
				}
				break;

			case GAME_PHASE::UNLOAD:
				// Opposite of load
				if(!LoadScr->IsVisible())
				{
					APP_STATE_PHY = false;
					LoadScr->Show();
					local_System_Graphic->Display_SceneManager->setFindVisibleObjects(false);
					Handler->Unload();	
				}
				else
				{
					LoadScr->Step(0.16f);
					if(Handler->Ended())
					{
						LoadScr->Hide();
						menu->Switch_inGame(false);

						// Change this state to any phase, usually menu but for sake of testing set to quit
						g_sAPP_STAT = APP_PHASE::MENU;
						g_sGAME_STAT = GAME_PHASE::LOAD;
					}
				}
				break;

			case GAME_PHASE::PAUSE:
				break;

			case GAME_PHASE::PLAY:
				// Game Logic Here
				// Examples of what should be above this section
				Handler->Step(Interval);
				// Please Process all other data before this section, the bottom section is strictly restricted
				// Only going to apply 2 section, support most computers Duo Core
				break;
			}
			break;
		}
		
		#pragma omp parallel if(APP_STATE_PHY)
		{
			#pragma omp sections
			{
				#pragma omp section
				{
					if(System_OgreHandler::IsRenderBlocked())
					{
						//System_OgreHandler::BlockRender();
						try
						{
							local_System_Graphic->m_pRoot->renderOneFrame();
						}
						catch(Ogre::Exception & e)
						{
							UNREFERENCED_PARAMETER(e);
							WriteCommandLine("*** --- Rendering Exception : %s", e.getFullDescription().c_str());
						}
						System_OgreHandler::UnblockRender();
					}
				}
				#pragma omp section
				{
					if(APP_STATE_PHY)
						local_System_Physics->UpdatePhysics(Interval);
				}
			}
			#pragma omp barrier
		}
		// Find out the interval of loop
		Interval = local_clock.End();
		local_System_Debug->Step(Interval);
		Difference = 16 - Interval;
		// Slow down the loop to prevent CPU overhead/overheat
		// the value is usually 0 ~ 1 assuming that Vsync is active
		if(Difference > 0)
			SleepEx(Difference, true);
	}
	while(!Handler->Ended())
		Sleep(32);

	delete LoadScr;
	delete GameOvr;
	//delete test_Interface;
	
	delete Handler;
	delete menu;
	if(!local_System_Debug->Shutdown())
		MessageBoxA(NULL, "Error Occuered during Shutdown", "ExitPoint Error", MB_ICONERROR | MB_OK);

	if(!local_System_Graphic->Shutdown())
		MessageBoxA(NULL, "Error Occuered during Shutdown", "ExitPoint Error", MB_ICONERROR | MB_OK);
	
	if(!local_System_Input->Shutdown())
		MessageBoxA(NULL, "Error Occuered during Shutdown", "ExitPoint Error", MB_ICONERROR | MB_OK);

	if(!local_System_Physics->Shutdown())
		MessageBoxA(NULL, "Error Occuered during Shutdown", "ExitPoint Error", MB_ICONERROR | MB_OK);
	
	if(!local_System_Audio->Shutdown())
		MessageBoxA(NULL, "Error Occuered during Shutdown", "ExitPoint Error", MB_ICONERROR | MB_OK);
	return static_cast<int>(msg.wParam);
}