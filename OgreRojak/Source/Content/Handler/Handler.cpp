#include "stdafx.h"
#include "Handler.h"

#include "System/EntryPoint/OgreRojak.h"
#include "System/OgreHandler/OgreHandler.h"
#include "System/Audio/Audio.h"
#include "System/Physics/Physics.h"
#include "../Map/Content_Map.h"
#include "../Interface/Screen.h"
#include "../Interface/GameOver.h"

unsigned int Content_Handler :: Level_ID = 0;
unsigned int Content_Handler :: Level_TOTAL = 4;

Content_Handler :: Content_Handler()
:	System_Thread(), mbLoaded(false), 
	m_pSceneManager(NULL), m_pCamera(NULL), m_pViewPort(NULL), m_pGameOverScreen(NULL), m_fTimeElapsed(0), _background(NULL)
{
	m_pSceneManager = SmartPtr<Ogre::SceneManager>(System_OgreHandler::Instance()->Root()->createSceneManager(Ogre::ST_GENERIC, "Content_SceneManager"));
	ASSERT(m_pSceneManager.get(), "Error Creating SceneManager");

	m_pSceneManager->setAmbientLight(Ogre::ColourValue(0.4f, 0.4f, 0.4f));
	
	Ogre::Camera * Cam = m_pSceneManager->createCamera("Game_Cam");

	ASSERT(Cam, "Error Creating Camera");

	Cam->setFarClipDistance(1000);
	Cam->setNearClipDistance(1);
	Cam->setAspectRatio(4.0f / 3.0f);
	
	Cam->setPosition(Ogre::Vector3(0, 50, -200));
	Cam->lookAt(Ogre::Vector3(0, 50, 200));
	
	m_pViewPort = SmartPtr<Ogre::Viewport>(System_OgreHandler::Instance()->Window()->addViewport(Cam, 1));
	ASSERT(m_pViewPort.get(), "Error Creating View Port");
	m_pViewPort->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	m_pCamera = SmartPtr<System_Camera>(new System_Camera(Cam));

	Ogre::Light * DirLight = m_pSceneManager->createLight("Sun");
	DirLight->setType(Ogre::Light::LT_POINT);
	DirLight->setPosition(Ogre::Vector3(500, 800, 500));
	DirLight->setDirection(Ogre::Vector3(-1, -1, -1));
	DirLight->setDiffuseColour(1, 1, 1);

	m_Text = new System_OverlayText("Handler Text", "bluehigh");
	m_TimeText = m_Text->AddTextBox("TimeElpased", "Time Elapsed : %f", 250, 40, 16, Ogre::ColourValue::White);
	m_Text->m_pOverlay->hide();

	_background = System_Audio::Instance()->LoadFile("Assets/Audio/In_game.wav", true);
	_background->setLoopCount(-1);

	_CompleteLevel = System_Audio::Instance()->LoadFile("Assets/Audio/Complete.wav");
	
}

Content_Handler :: ~Content_Handler()
{
	delete m_Text;
	m_pGameOverScreen = NULL;
	m_pCamera.reset(NULL);
	m_pCamera.release();
	System_OgreHandler::Instance()->Window()->removeViewport(0);
	m_pViewPort.release();
	m_pSceneManager.release();

	_background->release();
	_CompleteLevel->release();
}

void Content_Handler :: Unload()
{
	/* Release data */
	System_Thread::mbEnded = false;
	System_Thread::Begin();
}

void Content_Handler :: Load(const std::string &DefnitionFile)
{
	mbEnded = mbLoaded = false;
	System_Thread::Begin();
}

bool Content_Handler :: ThreadProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return System_Thread::ThreadProc(uMsg, wParam, lParam);
	/*switch(uMsg)
	{
	default:
		return System_Thread::ThreadProc(uMsg, wParam, lParam);
	}*/
}

void Content_Handler :: Work(const float &Interval)
{
	m_pSceneManager->setFindVisibleObjects(false);
	
	//Sleep(500);
	if(!mbLoaded)
	{
		// DO I/O etc
		Initialize();
		Sleep(1000);
		m_Text->m_pOverlay->show();
	}
	else
	{
		Uninitialize();
		Sleep(1000);
	}
	mbLoaded = !mbLoaded;
	m_pSceneManager->setFindVisibleObjects(true);
	System_Thread::mbEnded = true;	// End the thread
}

bool Content_Handler :: Initialize()
{
	System_OgreHandler	* local_System_Graphic	= System_OgreHandler::Instance();
	System_Physics		* local_System_Physics	= System_Physics::Instance();
	// Call all add to scene etc
	m_pMap = new Content_Map(m_pSceneManager.get());

	std::string Path = System_Utility::FormatText("Assets/Maps/Map_%i.xml", Content_Handler::Level_ID++);

	m_pMap->Load(Path);
	//m_pMap->Load("../Assets/Maps/Map_1.xml");

	m_pBallCloner = new System_ResourceCloner("Sphere HiDef.mesh", m_pSceneManager.get());
	//m_pBallCloner = new System_ResourceCloner("SphereR10.mesh", m_pSceneManager.get());

	Content_Deformable_Object * Ball = new Content_Deformable_Object(NULL);
	Ball->AttachObject(m_pSceneManager->getRootSceneNode()->createChildSceneNode("Ball1"));
	Ball->Initialize(m_pBallCloner->Clone());
	Ball->SoftBody()->translate(m_pMap->m_pStartEnd->StartPoint());
	local_System_Physics->World_Soft()->addSoftBody(Ball->SoftBody());
	m_SoftBodies.push_back(Ball);

	return true;
}

bool Content_Handler :: Uninitialize()
{
	_backgroundC->stop();
	m_pGameOverScreen->Hide();
	m_Text->m_pOverlay->hide();

	System_OgreHandler	* local_System_Graphic	= System_OgreHandler::Instance();
	System_Physics		* local_System_Physics	= System_Physics::Instance();
	// Call all to remove from scene
	System_OgreHandler::BlockRender();
	m_pSceneManager->setFindVisibleObjects(false);
	System_OgreHandler::UnblockRender();

	System_OgreHandler::BlockRender();
	m_pMap->UnLoad();
	System_OgreHandler::UnblockRender();
	delete m_pMap;
	m_pMap = NULL;
	// Unload data
	// No need feed text, just free memory etc
	for(int i = 0; i < m_SoftBodies.size(); i++)
	{
		local_System_Physics->World_Soft()->removeSoftBody(m_SoftBodies[i]->SoftBody());
		delete m_SoftBodies[i];
		m_SoftBodies[i] = NULL;
	}
	delete m_pBallCloner;
	m_pBallCloner = NULL;
	m_SoftBodies.clear();
	System_OgreHandler::BlockRender();
	m_pSceneManager->clearScene();
	Ogre::Light * DirLight = m_pSceneManager->createLight("Sun");
	DirLight->setType(Ogre::Light::LT_POINT);
	DirLight->setPosition(Ogre::Vector3(500, 800, 500));
	DirLight->setDirection(Ogre::Vector3(-1, -1, -1));
	DirLight->setDiffuseColour(1, 1, 1);
	System_OgreHandler::UnblockRender();
	local_System_Physics->ClearShapes();

	m_pCamera->ResetAngle();
	return true;
}

void Content_Handler :: Step(const float & Interval)
{
	bool Rslt;
	_backgroundC->isPlaying(&Rslt);
	if(!Rslt)
		_backgroundC = System_Audio::Instance()->RegisterChannel(_background);

	std::string Text = System_Utility::FormatText("Time Elapsed : %f", m_fTimeElapsed);
	m_TimeText->setCaption(Text);

	const btVector3 & BallPos = m_SoftBodies[0]->CenterPointbt();
	const Ogre::Vector3 & NodePos = m_SoftBodies[0]->Node()->getPosition();

	System_OISHandler * Input = System_OISHandler::Instance();

	if(!KeyDown(VK_SPACE))
	{
		m_pCamera->Registered_Camera->setPosition(NodePos + Ogre::Vector3(0, 0, 150));
		m_pCamera->Registered_Camera->lookAt(NodePos);
	}

	m_pCamera->Step(Interval);

	m_SoftBodies[0]->MergeData();

	if(!m_pMap->ReachedGoal())
	{
		m_fTimeElapsed += Interval * 0.001f;
	}
	else
	{
		if(!m_pGameOverScreen->IsVisible())
		{
			m_Text->m_pOverlay->hide();
			m_pGameOverScreen->Show();
			static_cast<Content_Screen_GameOver *>(m_pGameOverScreen)->SetTimeText(m_fTimeElapsed);
			_CompleteLevelC = System_Audio::Instance()->RegisterChannel(_CompleteLevel);
		}
		if(m_pGameOverScreen->IsVisible())
		{
			m_pGameOverScreen->Step(Interval);
			if(!m_pGameOverScreen->IsVisible())
				g_sGAME_STAT = GAME_PHASE::LOAD_NEXT;
		}
	}

	m_pMap->Step(Interval, m_pCamera->RollAngle(), BallPos, m_SoftBodies[0]->Ghost(), m_SoftBodies[0]->SoftBody());
}