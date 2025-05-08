#pragma once

/*	
	An Typical Object is split into 2 parts, Graphic and Physics, 
	Logic maybe split out also resulting in 3 parts.

	Graphical Data should be updated by Physics data at the start before rendering
	This is to ensure that Display data is not changed while physics are calculating in background
	
*/

class Content_DisplayObject
{
protected:
	SmartPtr <Ogre::Entity> 		m_pEntity;	// instance of mesh etc.
	SmartPtr <Ogre::SceneNode>		m_pCurrentNode;	// Child Node , this node
public:	
	Content_DisplayObject();
	virtual ~Content_DisplayObject();

	virtual void AttachObject(Ogre::SceneNode * node);
	virtual void DetachObject();

	inline Ogre::SceneNode *	Node()			const { return m_pCurrentNode.get(); }
	inline Ogre::Entity *		Entity()		const { return m_pEntity.get(); }
};

class Content_PhysicsObject
{
protected:
	bool	m_bPhysicsActivated;
	bool	m_bStaticObject;

	btCollisionObject *	m_pBody;	// New this with btRigid or btSoftBody
public:
	Content_PhysicsObject();
	virtual ~Content_PhysicsObject();
	/* Accessor */
	inline bool PhyiscsActivated()	const { return m_bPhysicsActivated; }
	inline bool IsAStaticObject()	const { return m_bStaticObject; }
	
	//inline btMotionState *		MotionState() { return m_pBody->getMotionState(); }
	inline btCollisionObject *	Body()		  { return m_pBody; }

	/* Modifier */
	virtual void ActivatePhysics(const bool & OnOff);
};

class Content_DisplayPhysicsObj
	: public Content_DisplayObject, public Content_PhysicsObject
{
protected:
	
public:
	Content_DisplayPhysicsObj()
		:Content_DisplayObject(), Content_PhysicsObject(){};
	~Content_DisplayPhysicsObj(){}

	virtual bool	Initialize(Ogre::Entity * Entity) = 0;
	//virtual bool Create(Ogre::SceneNode * node, const std::string & Name);
};