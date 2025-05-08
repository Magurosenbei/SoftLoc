#pragma once

/*	This Container Holds all information of the map				*/
/*	Shapes and bodies are separated to save memory				*/
/*	Another Holder for the Graphical Data might be necessary	*/

class Content_Obstacle;
class Content_RigidBalls;
class Content_Interactive_STARTEND;
class Content_Map
{
	SmartPtr<Ogre::SceneNode>						m_pMapRoot;
	SmartPtr<Ogre::SceneManager>					m_pSceneManager;

	btAlignedObjectArray	<Content_RigidBalls	*>	m_SubBalls;
	btAlignedObjectArray	<Content_Obstacle	*>	m_Obstacles;
	btAlignedObjectArray	<Content_Obstacle	*>	m_Walls;

	void	ExtractFromElement(	XMLElement		*	Element,
								std::string		& outId,
								std::string		& outMeshFile,
								std::string		& outCollisionFile,
								btVector3		& outPosition,
								btVector3		& outScale,
								btQuaternion	& outQuaternion);

	void	ExtractFromElement(	XMLElement		*	Element,	
								btVector3		& outPosition,
								btVector3		& outScale,
								btQuaternion	& outQuaternion);

	void	ExtractWalls(XMLElement * WallRoot);
	void	ExtractObstacles(XMLElement * SpecialRoot);

protected:
	btTransform	m_CurrentTransform;		// the orientation of the current map
	btVector3	m_ViewCenter;			// Point looking at

	bool		m_bReachGoal;

	// Not really necessary
	// They all share same memory 
	inline btVector3		convertVector(Ogre::Vector3  vector) {return btVector3(vector.x, vector.y, vector.z);}
	inline Ogre::Vector3	convertVector(btVector3 * vector)	  {return Ogre::Vector3(vector->getX(), vector->getY(), vector->getZ());}
public:
	Content_Map(Ogre::SceneManager	*	Manager);
	virtual ~Content_Map();

	Content_Interactive_STARTEND	*	m_pStartEnd;

	inline	bool		ReachedGoal()		const	{	return m_bReachGoal;	}

	inline	btVector3	ViewCenter()		const	{	return m_ViewCenter;	}
	inline	btTransform	CurrentTransform()	const	{	return m_CurrentTransform;	}



	/* Only Call these during Load/Unload Phase, usually called inside ContentHandler	*/
	virtual bool	Load(const std::string	&	FilePath);
	virtual bool	UnLoad();
	
	/*	Call This EveryFrame update	*/
	virtual void	Step(const float & Interval, const float & Cam_Angle, const btVector3 & BallPosition, btCollisionObject	* Target, btSoftBody * Original);
};