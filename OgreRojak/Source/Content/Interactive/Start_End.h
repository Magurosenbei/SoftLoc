#pragma once

class System_Physics;

class Content_Interactive_STARTEND : public Content_DisplayObject
{
protected:
	btTransform		m_StartPoint;
	btTransform		m_EndPoint;
	btTransform		m_DisplayPoint;
	btVector3		m_HalfExtents;

	btQuaternion	m_Quaternion;

	btGhostObject	*	m_pEnd;
	btBoxShape		*	m_pShape;

	SmartPtr<System_Physics> m_pPhysicsSys;

public:
	Content_Interactive_STARTEND(const btVector3 & Start, const btVector3 & End, const btVector3 & Display, const btVector3 & Extents, const btQuaternion & Quaternion);
	virtual ~Content_Interactive_STARTEND();


	bool	Initialize(Ogre::Entity	*	Flag);

	inline	btVector3 StartPoint() const { return m_StartPoint.getOrigin(); } 
	inline	btVector3 EndPoint() const { return m_EndPoint.getOrigin(); }

	bool	IsAtEnd(btBroadphaseProxy	*	Target);

	void	Step(const btTransform & Transform, const btVector3 & Point);
};