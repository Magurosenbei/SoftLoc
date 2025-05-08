#pragma once


class Content_Obstacle;

class Content_Wall : public Content_Obstacle
{
public:
	Content_Wall();
	virtual ~Content_Wall();

	/*virtual bool	Create(	Ogre::Entity * Display, Ogre::Entity * Collision,
							const btVector3	& Position,	const btVector3 & Scale,
							const btQuaternion	& Quaternion);
*/

	virtual void	Step(const btTransform & Transform, const btVector3 & Point);
	virtual bool	CheckCollide(btBroadphaseProxy	*	Target, btSoftBody * Original);
};