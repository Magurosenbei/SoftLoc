#include "stdafx.h"
#include "System/Physics/Physics.h"

#include "Start_End.h"


Content_Interactive_STARTEND :: Content_Interactive_STARTEND(const btVector3 & Start, const btVector3 & End, const btVector3 & Display, const btVector3 & Extents, const btQuaternion & Quaternion)
: m_HalfExtents(Extents), m_Quaternion(Quaternion), m_pEnd(NULL), m_pPhysicsSys(NULL)
{
	m_StartPoint.setIdentity();
	m_DisplayPoint.setIdentity();
	m_EndPoint.setIdentity();

	m_pPhysicsSys = SmartPtr<System_Physics>(System_Physics::Instance());
	std::string Key = System_Utility::FormatText("SQ SX:%f SY:%f SZ:%f", Extents.m_floats[0], Extents.m_floats[1], Extents.m_floats[2]);

	m_pShape = (btBoxShape *)m_pPhysicsSys->GetCollisionShape(Key, new btBoxShape(Extents * 0.5f));

	m_DisplayPoint.setOrigin(Display);
	m_StartPoint.setOrigin(Start);
	m_EndPoint.setOrigin(End);
	m_EndPoint.setRotation(Quaternion);

	m_pEnd = new btGhostObject;
	m_pEnd->setCollisionShape(m_pShape);
	m_pEnd->setWorldTransform(m_EndPoint);
	m_pEnd->setCollisionFlags(btCollisionObject::CO_GHOST_OBJECT);

	m_pPhysicsSys->World_Soft()->addCollisionObject(m_pEnd, btBroadphaseProxy::SensorTrigger);
}

Content_Interactive_STARTEND :: ~Content_Interactive_STARTEND()
{
	m_pPhysicsSys->World_Soft()->removeCollisionObject(m_pEnd);
	delete m_pEnd;
	m_pShape = NULL;
	m_pPhysicsSys.release();
}

bool Content_Interactive_STARTEND :: Initialize(Ogre::Entity * Flag)
{
	m_pEntity = SmartPtr<Ogre::Entity>(Flag);
	m_pCurrentNode->attachObject(m_pEntity.get());
	m_pEntity->setMaterialName("TF2NPR_Flag");
	m_pCurrentNode->setVisible(true);
	return true;
}

bool Content_Interactive_STARTEND :: IsAtEnd(btBroadphaseProxy *Target)
{
	btBroadphasePair * Pair;
	Pair = m_pPhysicsSys->World_Soft()->getPairCache()->findPair(Target, m_pEnd->getBroadphaseHandle());
	if(!Pair) return false;
	return true;
}

void Content_Interactive_STARTEND :: Step(const btTransform & Transform, const btVector3 & Point)
{
	btTransform NewTransform;

	NewTransform = m_EndPoint;
	NewTransform.setOrigin(NewTransform.getOrigin() - Point); 
	NewTransform = Transform * NewTransform;
	NewTransform.setOrigin(NewTransform.getOrigin() + Point); 
	m_pEnd->setWorldTransform(NewTransform);

	NewTransform = m_DisplayPoint;
	NewTransform.setOrigin(NewTransform.getOrigin() - Point); 
	NewTransform = Transform * NewTransform;
	NewTransform.setOrigin(NewTransform.getOrigin() + Point); 

	btQuaternion Ref_Rotation = NewTransform.getRotation();
	btVector3 Ref_Position = NewTransform.getOrigin();
	m_pCurrentNode->setPosition(Ref_Position.m_floats[0],Ref_Position.m_floats[1], Ref_Position.m_floats[2]);
	m_pCurrentNode->setOrientation(Ref_Rotation.getW(), Ref_Rotation.getX(), Ref_Rotation.getY(), Ref_Rotation.getZ());
}