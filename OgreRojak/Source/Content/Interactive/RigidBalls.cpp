#include "stdafx.h"
#include "Rigidballs.h"

#include "System/Physics/Physics.h"

Content_RigidBalls :: Content_RigidBalls()
:Content_DisplayPhysicsObj()
{
}

Content_RigidBalls :: ~Content_RigidBalls()
{
	if(m_pBody)
	{
		System_Physics::Instance()->World()->removeRigidBody(btRigidBody::upcast(m_pBody));
	}
}

bool Content_RigidBalls :: Initialize(Ogre::Entity *Entity)
{
	if(!Entity) return false;
	m_pEntity = SmartPtr<Ogre::Entity>(Entity);
	m_pCurrentNode->attachObject(m_pEntity.get());
	return true;
}

bool Content_RigidBalls :: Create(Ogre::Entity	*	Display, const btVector3 & SpawnPoint, const float & Scale)
{
	if(!Initialize(Display)) return false;
	std::string Key = System_Utility::FormatText("BALL R:%f", 10.0f * Scale);

	btCollisionShape * Shape = System_Physics::Instance()->GetCollisionShape(Key, NULL);
	if(!Shape)
		Shape = System_Physics::Instance()->GetCollisionShape(Key, new btSphereShape(10.0f * Scale));

	m_pBody = new btRigidBody(50.0f, NULL, Shape);

	m_pBody->setActivationState(DISABLE_DEACTIVATION);

	btTransform Spawn;
	Spawn.setIdentity();
	Spawn.setOrigin(SpawnPoint);
	m_pBody->setWorldTransform(Spawn);

	m_pCurrentNode->setPosition(SpawnPoint.m_floats[0], SpawnPoint.m_floats[1], SpawnPoint.m_floats[2]);
	m_pCurrentNode->setScale(Scale, Scale ,Scale);

	System_Physics::Instance()->World()->addRigidBody(btRigidBody::upcast(m_pBody));

	m_bPhysicsActivated = true;
	return true;
}

void Content_RigidBalls :: Step(const float &Interval)
{
	
}