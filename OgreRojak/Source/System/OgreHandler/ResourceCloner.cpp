#include "stdafx.h"
#include "ResourceCloner.h"

System_ResourceCloner :: System_ResourceCloner(
	const std::string	& FileName,
	Ogre::SceneManager	* RegisterSceneManager)
:	m_pOriginalSceneManager(RegisterSceneManager)
{
	size_t it = FileName.find(".mesh");
	ASSERT(it > 0, "FileName Have no .mesh in the name")
	m_Identifier = FileName.substr(0, it);
	System_OgreHandler::BlockRender();
		m_pOriginal = SmartPtr<Ogre::Entity>(m_pOriginalSceneManager->createEntity(m_Identifier, FileName));
	System_OgreHandler::UnblockRender();
	ASSERT(m_pOriginal.get(), "No Entity Created")
}

System_ResourceCloner :: ~System_ResourceCloner()
{
	ReleaseAllClones();
	m_pOriginalSceneManager->destroyEntity(m_pOriginal.get());
	m_pOriginal.release();
	m_pOriginalSceneManager.release();
}

Ogre::Entity *	System_ResourceCloner :: Clone()
{
	size_t	Que = m_Identifiers.size() + 1;
	Ogre::Entity	*	Object = NULL;
	std::string TAG = System_Utility::FormatText("Clone_%i_%s", Que, m_Identifier.c_str());

	System_OgreHandler::BlockRender();
		m_pOriginal->getMesh()->clone(TAG + ".mesh", m_Identifier + "_CLONE");
		Object = m_pOriginalSceneManager->createEntity(TAG, TAG + ".mesh");
	System_OgreHandler::UnblockRender();

	m_Identifiers.push_back(TAG);
	return Object;
}

Ogre::Entity * System_ResourceCloner :: ReferenceCopy()
{
	return m_pOriginal.get();
}

bool System_ResourceCloner :: ReleaseAllClones()
{
	Ogre::Entity	*	Hold;
	for(int i = 0; i < m_Identifiers.size(); i++)
	{
		// Need to be revised
		Hold = m_pOriginalSceneManager->getEntity(m_Identifiers[i]);
		ASSERT(Hold, "Clone Target Lost")
		Hold->detatchFromParent();
		Ogre::MeshManager::getSingletonPtr()->remove(Hold->getMesh()->getHandle());
		m_pOriginalSceneManager->destroyEntity(Hold);
	}
	Hold = NULL;
	m_Identifiers.clear();
	
	//Ogre::ResourceGroupManager::getSingletonPtr()->unloadResourceGroup(m_Identifier + "_CLONE");
	WriteCommandLine("Clones of %s has successuflly Released", m_Identifier.c_str());
	return true;
}