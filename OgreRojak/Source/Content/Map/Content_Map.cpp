#include "stdafx.h"
#include "Content_Map.h"
#include "System/Physics/Physics.h"
#include "../Obstacle/Obstacle.h"
#include "../Obstacle/Wall.h"
#include "../Interactive/RigidBalls.h"


Content_Map :: Content_Map(Ogre::SceneManager * Manager)
: m_pStartEnd(NULL), m_bReachGoal(false)
{
	m_pSceneManager = SmartPtr<Ogre::SceneManager>(Manager);
	m_pMapRoot = SmartPtr<Ogre::SceneNode>(m_pSceneManager->getRootSceneNode()->createChildSceneNode("MapRoot"));
}

Content_Map :: ~Content_Map()
{
	delete m_pStartEnd;
	m_pMapRoot.release();
	m_pSceneManager.release();
}

bool Content_Map :: Load(const std::string & FilePath)
{
	XML File(FilePath.c_str());
	if(!File.IntegrityTest() || File.ParseStatus() != 0)
		return false;
	File.CompressMemory();
	XMLElement * Root = File.GetRootElement(), * Reference;

	
	btVector3 Start, Goal, FlagPoint, GoalExtents;
	btQuaternion GoalQuater;

	Reference = Root->FindElementZ("StartPoint");
	Start = btVector3(	Reference->FindVariableZ("x")->GetValueFloat(),
						Reference->FindVariableZ("y")->GetValueFloat(),
						Reference->FindVariableZ("z")->GetValueFloat());

	Reference = Root->FindElementZ("GoalPoint");
	Goal = btVector3(	Reference->FindVariableZ("x")->GetValueFloat(),
						Reference->FindVariableZ("y")->GetValueFloat(),
						Reference->FindVariableZ("z")->GetValueFloat());

	Reference = Root->FindElementZ("FlagPosition");
	FlagPoint = btVector3(	Reference->FindVariableZ("x")->GetValueFloat(),
							Reference->FindVariableZ("y")->GetValueFloat(),
							Reference->FindVariableZ("z")->GetValueFloat());


	Reference = Root->FindElementZ("GoalExtents");
	GoalExtents = btVector3(	Reference->FindVariableZ("x")->GetValueFloat(),
								Reference->FindVariableZ("y")->GetValueFloat(),
								Reference->FindVariableZ("z")->GetValueFloat());

	Reference = Root->FindElementZ("GoalRotation");
	GoalQuater = btQuaternion(	Reference->FindVariableZ("x")->GetValueFloat(),
								Reference->FindVariableZ("y")->GetValueFloat(),
								Reference->FindVariableZ("z")->GetValueFloat());
	
	
	m_pStartEnd = new Content_Interactive_STARTEND(Start, Goal, FlagPoint, GoalExtents, GoalQuater);
	m_pStartEnd->AttachObject(m_pMapRoot->createChildSceneNode("Flag"));
	System_OgreHandler::BlockRender();
	m_pStartEnd->Initialize(m_pSceneManager->createEntity("FlagPole", "Flag.mesh"));
	System_OgreHandler::UnblockRender();

	
	Reference = Root->FindElementZ("Walls");
	ExtractWalls(Reference);
	Reference = Root->FindElementZ("Special");
	ExtractObstacles(Reference);

	//Setup physics for the ground
	return true;
}

bool Content_Map :: UnLoad()
{
	for(int i = 0; i < m_Walls.size(); i++)
	{	
		delete m_Walls[i];
		m_Walls[i] = NULL;
	}
	m_Walls.clear();

	for(int i = 0; i < m_Obstacles.size(); i++)
	{	
		delete m_Obstacles[i];
		m_Obstacles[i] = NULL;
	}
	m_Obstacles.clear();
	
	return true;
}

void Content_Map :: Step(
const float &Interval, 
const float & Cam_angle, 
const btVector3 & BallPosition,
btCollisionObject	*	Target,
btSoftBody			*	Original)
{	
	m_ViewCenter = BallPosition;
	btTransform	Rotation;
	Rotation.setIdentity();

	btQuaternion Quater(btVector3(0, 0, 1), Cam_angle);
	Rotation.setRotation(Quater);

	m_CurrentTransform = Rotation;

	btVector3 RotateOffSet(0, -5, 0);
	(Cam_angle > 0 && Cam_angle != 0)?  RotateOffSet.setX(-20.0f) : RotateOffSet.setX(20.0f);

	btTransform		Reference;
	btQuaternion	Ref_Rotation;
	btVector3		Ref_Position;

	m_pStartEnd->Step(Rotation, BallPosition + RotateOffSet);
	
	bool BallTouchWall = false;

	int i = 0, j = 0;

	for(i = 0; i < m_Walls.size(); i++)
		m_Walls[i]->Step(Interval, Rotation, BallPosition + RotateOffSet);

	for(j = 0; j < m_Obstacles.size(); j++)
		m_Obstacles[j]->Step(Interval, Rotation, BallPosition + RotateOffSet);


	bool HitWall = false;
	for(i = 2; i < m_Walls.size(); i++)
	{
		if(!m_Walls[i]->CheckCollide(Target->getBroadphaseHandle(),Original)) continue;
		HitWall = true; 
		break;
	}
	if(!HitWall)
	{
		btTransform	Gravity;
		Gravity.setIdentity();
		Gravity.setOrigin(btVector3(0, -9.8f, 0));
		Quater.setRotation(btVector3(0, 0, 1), -Cam_angle);
		Rotation.setRotation(Quater);
		Gravity = Rotation * Gravity;
		System_Physics::Instance()->World_Soft_Info()->m_gravity = Gravity.getOrigin();
	}

	for(j = 0; j < m_Obstacles.size(); j++)
	{
		m_Obstacles[j]->CheckCollide(Target->getBroadphaseHandle(), Original);
	}
	if(!m_bReachGoal)
		m_bReachGoal = m_pStartEnd->IsAtEnd(Target->getBroadphaseHandle());

	if(m_bReachGoal)
	{
		unsigned int NumberOfSubsInGoal = 0;
		for(i = 0; i < m_SubBalls.size(); i++)
		{
			if(m_pStartEnd->IsAtEnd(m_SubBalls[i]->Body()->getBroadphaseHandle()))
				NumberOfSubsInGoal++;
		}
		// Use this to calculate score.
	}
}