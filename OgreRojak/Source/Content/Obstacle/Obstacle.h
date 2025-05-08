#pragma once

class Content_TimeTriggeredObj
{
protected:
	float			m_fRestTime;
	float			m_fTimePassed;

	bool			m_bTriggered;
public:
	Content_TimeTriggeredObj()
		:	m_fRestTime(0.0f), m_fTimePassed(0.0f), m_bTriggered(false){}

	inline bool IsTriggered() const { return m_bTriggered; }
};

class System_Physics_CollisionMesh;
/* Implement Obstacle Here */
class Content_Obstacle : public Content_DisplayPhysicsObj
{
	virtual bool	Initialize(Ogre::Entity * Entity);
protected:
	System_Physics_CollisionMesh	*	m_ColMesh;

	btTransform		m_OriginalTransform;

	bool			m_bTriggered;
	bool			m_HasDisplay;
	bool			m_HasPhysics;
	int				m_ObstacleType;
	float			m_fTimePassed;
	float			m_fRestTime;

public:
	Content_Obstacle();
	virtual ~Content_Obstacle();

	bool	Create(	Ogre::Entity * Display, Ogre::Entity * Collision,
					const btVector3	& Position,	const btVector3 & Scale,
					const btQuaternion	& Quaternion, const int & m_ObstacleType);

	virtual bool CheckCollide(btBroadphaseProxy	*	Target,btSoftBody	*	Original);
	virtual void Step(const float &Interval, const btTransform & Transform, const btVector3 & Point);
};