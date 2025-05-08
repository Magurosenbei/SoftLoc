#pragma once


class System_Physics_CollisionMesh
{
	BtOgre::BtTriMesh		*	m_pShape;
public:
	System_Physics_CollisionMesh();
	~System_Physics_CollisionMesh();

	inline	btCollisionShape *	CollisionShape()	{	return m_pShape;	}
	
	bool	Create(Ogre::Entity	*	Entity, const btVector3 & Scale);
};