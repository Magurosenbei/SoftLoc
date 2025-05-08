#include "stdafx.h"
#include "System/Physics/Physics.h"
#include "System/Physics/CollisionMesh.h"
#include "Obstacle.h"

Content_Obstacle :: Content_Obstacle()
: Content_DisplayPhysicsObj(), m_ColMesh(NULL), m_HasDisplay(false), m_HasPhysics(true)
{
	m_OriginalTransform.setIdentity();
}

Content_Obstacle :: ~Content_Obstacle()
{
	if(m_ColMesh)
	{
		delete m_ColMesh;
		m_ColMesh = NULL;
	}
	if(m_pBody)
	{
		System_Physics::Instance()->World()->removeRigidBody(btRigidBody::upcast(m_pBody));
		delete m_pBody;
		m_pBody = NULL;
	}
}

bool Content_Obstacle :: Initialize(Ogre::Entity * Entity)
{
	return false;
}


bool Content_Obstacle :: Create(	Ogre::Entity * Display, Ogre::Entity * Collision,
									const btVector3	& Position,	const btVector3 & Scale,
									const btQuaternion	& Quaternion, const int & ObstacleType)
{
	m_bTriggered = false;
	m_fTimePassed = 0.0f;
	m_fRestTime = 500.0f;
	m_ObstacleType = ObstacleType;
	if(Display)
	{
		m_pEntity = SmartPtr<Ogre::Entity>(Display);
		m_pCurrentNode->attachObject(m_pEntity.get());
		m_HasDisplay = true;
	}
	btCollisionShape  * Shape(NULL);
	std::string Key;

	if(!Collision)
	{
		Key = System_Utility::FormatText("SQ SX:%f SY:%f SZ:%f", Scale.m_floats[0], Scale.m_floats[1], Scale.m_floats[2]);
		Shape = System_Physics::Instance()->GetCollisionShape(Key, NULL);
		// Create the box if don't exist
		if(!Shape)
		{
			// Width from end 0 to end 1
			Shape = new btBoxShape(Scale * 0.5f);
			Shape = System_Physics::Instance()->GetCollisionShape(Key, Shape);
		}
		m_pBody = new btRigidBody(0, NULL, Shape);
	}
	else
	{
		m_ColMesh = new System_Physics_CollisionMesh;

		System_OgreHandler::BlockRender();
		if(!m_ColMesh->Create(Collision, Scale))
		{
			MessageBoxA(NULL, "MAP CREATION ERROR", "Unable to create Collision Mesh", MB_OK | MB_ICONERROR);
		}
		System_OgreHandler::UnblockRender();
		Shape = m_ColMesh->CollisionShape();
		
		m_pBody = new btRigidBody(0.0f, NULL, m_ColMesh->CollisionShape());
	}
	m_OriginalTransform.setIdentity();
	m_OriginalTransform.setOrigin(Position);
	m_OriginalTransform.setRotation(Quaternion);

	m_pBody->setWorldTransform(m_OriginalTransform);
	m_pBody->setCollisionFlags(m_pBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	m_pBody->setActivationState(DISABLE_DEACTIVATION);
	System_Physics::Instance()->World_Soft()->addRigidBody(btRigidBody::upcast(m_pBody));
	m_bPhysicsActivated = true;
	
	if(m_HasDisplay)
	{
		m_pCurrentNode->scale(Scale.m_floats[0], Scale.m_floats[1], Scale.m_floats[2]);
		m_pCurrentNode->setPosition(Position.m_floats[0], Position.m_floats[1], Position.m_floats[2]);
		m_pCurrentNode->setOrientation(Quaternion.getW(), Quaternion.getX(), Quaternion.getY(), Quaternion.getZ());
		#ifdef _DEBUG
		m_pCurrentNode->showBoundingBox(true);
		#endif
	}

	return true;
}



bool Content_Obstacle :: CheckCollide(btBroadphaseProxy * Target,btSoftBody	*	Original)
{
	//if(m_bTriggered) return false;
	btBroadphasePair * Pair;
	Pair = System_Physics::Instance()->World()->getPairCache()->findPair(Target, m_pBody->getBroadphaseHandle());
	if(!Pair) return false;

	btManifoldArray Contacts;
	if(!Pair->m_algorithm) return false;
	Pair->m_algorithm->getAllContactManifolds(Contacts);
	if(Contacts.size() < 1)
		return false;

	btPersistentManifold * Pt;
	float Direction;
	bool Collided = false;
	for(int i = 0; i < Contacts.size() && !Collided; i++)
	{	
		Pt = Contacts[i];
		Direction = (Pt->getBody0() == m_pBody)? btScalar(1.0) : btScalar(-1.0);
		for(int j = 0; j < Pt->getNumContacts() && !Collided; j++)
		{
			if(Pt->getContactPoint(j).getDistance() < 0.0f)
				Collided = true;
		}
	}
	if(!Collided) return false;
	
	// Play sound etc
	//if(!m_bTriggered)
	{
		//m_pBody->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
		
		switch(m_ObstacleType)
		{
		case 1://needle
			break;
		case 2://hotpad
			if(Original->m_cfg.kPR > 3000)
				Original->m_cfg.kPR -= 1000;
			Original->m_materials[0]->m_kAST = 0.05f;
			Original->m_materials[0]->m_kLST = 0.01f;
			Original->m_materials[0]->m_kVST = 0.03f;
			break;
		case 3://coldpad
			if(Original->m_cfg.kPR < 50000)
				Original->m_cfg.kPR += 1000;
			Original->m_materials[0]->m_kAST = 0.8f;
			Original->m_materials[0]->m_kLST = 0.8f;
			Original->m_materials[0]->m_kVST = 0.8f;
			break;
		}
	}

	m_bTriggered = true;
			
	return true;
	
	
}	

void Content_Obstacle :: Step(const float &Interval, const btTransform & Transform, const btVector3 & Point)
{
	btTransform NewTransform;

	NewTransform = m_OriginalTransform;
	NewTransform.setOrigin(NewTransform.getOrigin() - Point); 
	NewTransform = Transform * NewTransform;
	NewTransform.setOrigin(NewTransform.getOrigin() + Point); 

	m_pBody->setWorldTransform(NewTransform);
	if(m_HasDisplay)
	{
		btQuaternion Ref_Rotation = NewTransform.getRotation();
		btVector3 Ref_Position = NewTransform.getOrigin();
		m_pCurrentNode->setPosition(Ref_Position.m_floats[0],Ref_Position.m_floats[1], Ref_Position.m_floats[2]);
		m_pCurrentNode->setOrientation(Ref_Rotation.getW(), Ref_Rotation.getX(), Ref_Rotation.getY(), Ref_Rotation.getZ());
	}

	if(m_bTriggered)
	{
		if(m_fTimePassed < m_fRestTime)
		{
			m_fTimePassed += Interval;
			// Do something .....
		}
		else
		{
			m_bTriggered = false;
			m_fTimePassed = 0.0f;
			//m_pBody->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT);
		}
	}
	//else
	//{
	//	// Do something
	//	



	//}
}