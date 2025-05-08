#include "stdafx.h"
#include "ContentHeader.h"

Content_DisplayObject :: Content_DisplayObject()
: m_pCurrentNode(NULL), m_pEntity(NULL)
{
}

Content_DisplayObject :: ~Content_DisplayObject()
{
	//m_pCurrentNode.reset(NULL);
	//m_pCurrentNode->detachAllObjects();
	if(m_pEntity.get())
		m_pCurrentNode->detachObject(m_pEntity.get());
	//m_pCurrentNode->getParent()->removeChild(m_pCurrentNode.get());
	m_pCurrentNode.release();
	//System_OgreHandler::Instance()->Display_SceneManager->destroyEntity(m_pEntity.get());
	//m_pEntity.reset(NULL);
	m_pEntity.release();
}

void Content_DisplayObject :: AttachObject(Ogre::SceneNode *node)
{
	// Save Parent Node
	m_pCurrentNode = SmartPtr<Ogre::SceneNode>(node);
	// Attach the object to the child node
	//m_pCurrentNode->attachObject(m_pEntity.get());
}

void Content_DisplayObject :: DetachObject()
{
	m_pCurrentNode->detachAllObjects();
	m_pCurrentNode->getParent()->removeChild(m_pCurrentNode.get());
	m_pCurrentNode.release();
}


Content_PhysicsObject :: Content_PhysicsObject()
:m_pBody(NULL), m_bPhysicsActivated(false), m_bStaticObject(false)
{
}

Content_PhysicsObject :: ~Content_PhysicsObject()
{
	if(m_pBody)
	{
		delete m_pBody;
		m_pBody = NULL;
	}
}

void Content_PhysicsObject :: ActivatePhysics(const bool &OnOff)
{
	m_bPhysicsActivated = OnOff;
	m_pBody->setActivationState(m_bPhysicsActivated);
}