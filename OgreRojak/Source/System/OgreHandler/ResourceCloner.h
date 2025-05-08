#pragma once


/* Due to the hassle of NameTags in Ogre, created this thing to "COPY" meshes */
/* Mainly used for SoftBodies	*/

class System_ResourceCloner
{
	btAlignedObjectArray	<std::string>			m_Identifiers;
	SmartPtr				<Ogre::Entity>			m_pOriginal;
	SmartPtr				<Ogre::SceneManager>	m_pOriginalSceneManager;

	std::string				m_Identifier;
public:
	System_ResourceCloner(	const std::string	&	FileName,
							Ogre::SceneManager	*	RegisterSceneManager);
	~System_ResourceCloner();
	
	//	Clone the entity in Mesh Data (use more memory, must for SoftBodies)
	Ogre::Entity	*	Clone();				
	
	//	return a reference to the original (returns pointer so many objects can use the same model)
	Ogre::Entity	*	ReferenceCopy();		

	//	unload all the clones leaving only the original, deleting this instance does the same thing.
	bool				ReleaseAllClones();
};