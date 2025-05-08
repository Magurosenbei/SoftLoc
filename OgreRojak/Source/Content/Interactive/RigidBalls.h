#pragma once

class Content_RigidBalls	: public Content_DisplayPhysicsObj
{
protected:
	virtual bool	Initialize(Ogre::Entity * Entity);
public:
	Content_RigidBalls();
	virtual ~Content_RigidBalls();
	
	virtual bool	Create(Ogre::Entity	*	Display, const btVector3 & SpawnPoint, const float & Scale);
	
	virtual void Step(const float & Interval);
};