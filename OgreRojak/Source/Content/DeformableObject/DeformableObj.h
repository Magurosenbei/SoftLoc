#pragma once

class Content_Deformable_Object : public Content_DisplayPhysicsObj
{
	btSoftBody						*	m_pSoftBody;
	btPairCachingGhostObject		*	m_pGhost;

	btVector3	m_Position;	// Choose bt's due to __m128 SIMD
	btVector3	m_kDivider;
	
	SmartPtr <System_Camera>	Registered_Camera;

	btAlignedObjectArray<btVector3>		m_PreviousVertex;
	btAlignedObjectArray<btVector3>		m_PreviousNormal;
public:
	Content_Deformable_Object(System_Camera * Sys_Cam);
	virtual ~Content_Deformable_Object();

	inline btSoftBody * SoftBody() const {	return m_pSoftBody; }
	inline btGhostObject * Ghost() const {	return m_pGhost; }

	/* Returns a calculated Center Point of the Mesh, *Warning : Updates during MergeData */
	inline const btVector3	CenterPointbt() const { return m_Position; }
	inline const float	*	CenterPointf() const { return m_Position.m_floats; }

	virtual bool	Initialize(Ogre::Entity * Entity);
	virtual void	AttachObject(Ogre::SceneNode * node);
	virtual void	MergeData();
};