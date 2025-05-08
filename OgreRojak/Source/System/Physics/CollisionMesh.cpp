#include "stdafx.h"
#include "System/Physics/Physics.h"
#include "CollisionMesh.h"

System_Physics_CollisionMesh :: System_Physics_CollisionMesh()
: m_pShape(NULL)
{
}


System_Physics_CollisionMesh :: ~System_Physics_CollisionMesh()
{
	if(m_pShape) 
		m_pShape = NULL;
}

bool System_Physics_CollisionMesh :: Create(Ogre::Entity  *Entity, const btVector3 & Scale)
{
	m_pShape = (BtOgre::BtTriMesh *)System_Physics::Instance()->GetCollisionShape(Entity->getMesh()->getName(), NULL);
	// return if the shape already exist
	if(m_pShape)
	{
		WriteCommandLine("Collision Mesh : %s Exists, Returning Reference", Entity->getMesh()->getName().c_str());
		return true;
	}
	else
	{
		BtOgre::StaticMeshToShapeConverter Convert(Entity);
		m_pShape  = (BtOgre::BtTriMesh *)Convert.createTrimesh();

		WriteCommandLine("Collision Mesh : %s Created", Entity->getMesh()->getName().c_str());
		std::string Key = System_Utility::FormatText("ColMesh %s SX:%f SY:%f SZ:%f", Entity->getName().c_str(), Scale.m_floats[0], Scale.m_floats[1], Scale.m_floats[2]);

		m_pShape = (BtOgre::BtTriMesh *)System_Physics::Instance()->GetCollisionShape(Key, m_pShape);

		m_pShape->setLocalScaling(Scale);
	}

	return true;
}