#include "stdafx.h"
#include "System/Physics/Physics.h"

#include "Obstacle.h"
#include "Wall.h"

Content_Wall :: Content_Wall()
: Content_Obstacle()
{
	m_OriginalTransform.setIdentity();
	m_bStaticObject = true;
	m_bPhysicsActivated = true;
}

Content_Wall :: ~Content_Wall()
{
}


void Content_Wall :: Step(const btTransform & Transform, const btVector3 & Point)
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
}

bool Content_Wall :: CheckCollide(btBroadphaseProxy * Target, btSoftBody	*	Original)
{
	btBroadphasePair * Pair(NULL);
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
	return Collided;
}