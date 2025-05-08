#include "stdafx.h"
#include "Content_Map.h"
#include "../Obstacle/Obstacle.h"
#include "../Obstacle/Wall.h"

void	Content_Map::ExtractFromElement(	XMLElement		*	Element,	
											std::string		& outId,
											std::string		& outMeshFile,
											std::string		& outCollisionFile,
											btVector3		& outPosition,
											btVector3		& outScale,
											btQuaternion	& outQuaternion)
{
	// Grab Display Mesh File
	XMLVariable * Variable = Element->FindVariableZ("id");
	if(Variable)
	{
		outId.reserve(256);
		Variable->GetValue(&outId[0]);
		outId = outId.c_str();
	}

	Variable = Element->FindVariableZ("display");
	if(Variable)
	{
		outMeshFile.reserve(256);
		Variable->GetValue(&outMeshFile[0]);
		outMeshFile = outMeshFile.c_str();
	}
	// Grab Collision Mesh File
	Variable = Element->FindVariableZ("collision");
	if(Variable)
	{
		outCollisionFile.reserve(256);
		Variable->GetValue(&outCollisionFile[0]);
		outCollisionFile = outCollisionFile.c_str();
	}
	// Grab Orientation Details
	try
	{
		XMLElement * Refer = Element->FindElementZ("Position");
		outPosition = btVector3(Refer->FindVariableZ("x")->GetValueFloat(),
								Refer->FindVariableZ("y")->GetValueFloat(),
								Refer->FindVariableZ("z")->GetValueFloat());

		Refer = Element->FindElementZ("Scale");
		outScale	= btVector3(Refer->FindVariableZ("x")->GetValueFloat(),
								Refer->FindVariableZ("y")->GetValueFloat(),
								Refer->FindVariableZ("z")->GetValueFloat());

		Refer = Element->FindElementZ("Rotation");
		outQuaternion = btQuaternion(	Refer->FindVariableZ("x")->GetValueFloat(),
										Refer->FindVariableZ("y")->GetValueFloat(),
										Refer->FindVariableZ("z")->GetValueFloat());
	}
	catch(std::exception	& e)
	{
		e;
		WriteCommandLine("Error Reading XMLElement : %s", e.what());
	}
}

void	Content_Map::ExtractFromElement(	XMLElement		*	Element,	
											btVector3		& outPosition,
											btVector3		& outScale,
											btQuaternion	& outQuaternion)
{
	try
	{
		XMLElement * Refer = Element->FindElementZ("Position");
		outPosition = btVector3(Refer->FindVariableZ("x")->GetValueFloat(),
								Refer->FindVariableZ("y")->GetValueFloat(),
								Refer->FindVariableZ("z")->GetValueFloat());

		Refer = Element->FindElementZ("Scale");
		outScale	= btVector3(Refer->FindVariableZ("x")->GetValueFloat(),
								Refer->FindVariableZ("y")->GetValueFloat(),
								Refer->FindVariableZ("z")->GetValueFloat());

		Refer = Element->FindElementZ("Rotation");
		outQuaternion = btQuaternion(	Refer->FindVariableZ("x")->GetValueFloat(),
										Refer->FindVariableZ("y")->GetValueFloat(),
										Refer->FindVariableZ("z")->GetValueFloat());
	}
	catch(std::exception	& e)
	{
		e;
		WriteCommandLine("Error Reading XMLElement : %s", e.what());
	}
}

void Content_Map :: ExtractWalls(XMLElement * WallRoot)
{
	ASSERT(WallRoot, "NO WALLS");
	XMLElement *	Wall;
	XMLElement **	WallGroups, ** WallList;

	WallGroups = WallRoot->GetChildren();
	size_t NumberOfGroups = WallRoot->GetChildrenNum();

	btVector3		Position,	Scale;
	btQuaternion	Quaternion;

	std::string		MeshName;
	std::string		CollisionMeshName;
	std::string		Id;
	std::string		KeyName;

	for(size_t i = 0; i < NumberOfGroups; i++)
	{
		std::string		Tag;
		Tag.reserve(256);
		WallGroups[i]->FindVariableZ("Tag")->GetValue(&Tag[0]);
		Tag = Tag.c_str();

		size_t GroupSize = WallGroups[i]->GetChildrenNum();
		WallList = WallGroups[i]->GetChildren();
		for(size_t j = 0; j < GroupSize; j++)
		{
			MeshName.clear();
			CollisionMeshName.clear();
			Id.clear();
			KeyName.clear();
			Wall = WallList[j];

			ExtractFromElement(Wall, 
				Id, MeshName, CollisionMeshName, Position,	Scale, Quaternion);

			WriteCommandLine("\n<Defining Wall> ID:%s D:%s C:%s\nP: %f, %f, %f\nS: %f, %f, %f\nQ: %f, %f, %f, %f",
				Id.c_str(), MeshName.c_str(), CollisionMeshName.c_str(), 
				Position.getX(), Position.getY(), Position.getZ(),
				Scale.getX(), Scale.getY(), Scale.getZ(),
				Quaternion.getX(), Quaternion.getY(), Quaternion.getZ(), Quaternion.getW());


			KeyName = Tag + "_" + Id;
			KeyName = KeyName.c_str();
			Ogre::SceneNode * Node = m_pMapRoot->createChildSceneNode(KeyName);
			Node->setInheritOrientation(true);
			Ogre::Entity	*	Display(NULL), * Collision(NULL);

			System_OgreHandler::BlockRender();
			if(MeshName.length() || CollisionMeshName.length())
			{
				
				if(MeshName.size() > 0)
				{
					size_t it = MeshName.find(".mesh");
					ASSERT(it > 0, "FileName Have no .mesh in the name")				
					Display = m_pSceneManager->createEntity(KeyName + "_D" + MeshName.substr(0, it), MeshName);
					Display->setMaterialName("TF2NPR");
				}
				if(CollisionMeshName.size() > 0)
				{
					size_t it = CollisionMeshName.find(".mesh");
					ASSERT(it > 0, "FileName Have no .mesh in the name")
					Collision = m_pSceneManager->createEntity(KeyName + "_C" + CollisionMeshName.substr(0, it), CollisionMeshName);
				}
			}
			Content_Wall *	Wall = new Content_Wall;
			Wall->AttachObject(Node);
			Wall->Create(Display, Collision, Position, Scale, Quaternion, 0);
			System_OgreHandler::UnblockRender();
			m_Walls.push_back(Wall);
		}
	}
}

//void	Content_Map :: ExtractObstacles(XMLElement * SpecialRoot)
//{
//	if(!SpecialRoot) return;
//	XMLElement *	Special;
//	XMLElement **	SpecialGroups, ** SpecialList;
//
//	SpecialGroups			= SpecialRoot->GetChildren();
//	size_t NumberOfGroups	= SpecialRoot->GetChildrenNum();
//
//	btVector3		Position,	Scale;
//	btQuaternion	Quaternion;
//
//	std::string		MeshName;
//	std::string		CollisionMeshName;
//	std::string		Id;
//	std::string		KeyName;
//
//	for(size_t i = 0; i < NumberOfGroups; i++)
//	{
//		std::string		Tag;
//		Tag.reserve(256);
//		SpecialGroups[i]->FindVariableZ("Tag")->GetValue(&Tag[0]);
//		Tag = Tag.c_str();
//
//		size_t GroupSize = SpecialGroups[i]->GetChildrenNum();
//		SpecialList = SpecialGroups[i]->GetChildren();
//		for(size_t j = 0; j < GroupSize; j++)
//		{
//			MeshName.clear();
//			CollisionMeshName.clear();
//			Id.clear();
//			KeyName.clear();
//			Special = SpecialList[j];
//
//			ExtractFromElement(Special, 
//				Id, MeshName, CollisionMeshName, Position,	Scale, Quaternion);
//
//			WriteCommandLine("\n<Defining Special> ID:%s D:%s C:%s\nP: %f, %f, %f\nS: %f, %f, %f\nQ: %f, %f, %f, %f",
//				Id.c_str(), MeshName.c_str(), CollisionMeshName.c_str(), 
//				Position.getX(), Position.getY(), Position.getZ(),
//				Scale.getX(), Scale.getY(), Scale.getZ(),
//				Quaternion.getX(), Quaternion.getY(), Quaternion.getZ(), Quaternion.getW());
//
//
//			KeyName = Tag + "_" + Id;
//			KeyName = KeyName.c_str();
//			Ogre::SceneNode * Node = m_pMapRoot->createChildSceneNode(KeyName);
//			Node->setInheritOrientation(true);
//			Ogre::Entity	*	Display(NULL), * Collision(NULL);
//
//			if(MeshName.length() || CollisionMeshName.length())
//			{
//				System_OgreHandler::BlockRender();
//				if(MeshName.size() > 0)
//				{
//					size_t it = MeshName.find(".mesh");
//					ASSERT(it > 0, "FileName Have no .mesh in the name")				
//					Display = m_pSceneManager->createEntity(KeyName + "_D" + MeshName.substr(0, it), MeshName);
//					Display->setMaterialName("TF2NPR");
//				}
//				if(CollisionMeshName.size() > 0)
//				{
//					size_t it = CollisionMeshName.find(".mesh");
//					ASSERT(it > 0, "FileName Have no .mesh in the name")
//					Collision = m_pSceneManager->createEntity(KeyName + "_C" + CollisionMeshName.substr(0, it), CollisionMeshName);
//				}
//				System_OgreHandler::UnblockRender();
//			}
//			// At this Point you would have extrated the following :
//			// Position, scale, Quaterntion, display mesh, collision mesh
//			// Display and collision can be NULL, do take note
//
//			Content_Obstacle *	Obstacle = new Content_Obstacle;
//			Obstacle->AttachObject(Node);
//			Obstacle->Create(Display, Collision, Position, Scale, Quaternion);
//			m_Obstacles.push_back(Obstacle);
//			//m_Obstacles.push_back(NULL);	// Add to this list
//
//			/*Content_Wall *	Wall = new Content_Wall;
//			Wall->AttachObject(Node);
//			Wall->CreateWall(Display, Collision, Position, Scale, Quaternion);
//			m_Walls.push_back(Wall);*/
//		}
//	}
//}


void	Content_Map :: ExtractObstacles(XMLElement * SpecialRoot)
{
	if(!SpecialRoot) return;
	XMLElement *	Special;
	XMLElement **	SpecialGroups, ** SpecialList;

	SpecialGroups			= SpecialRoot->GetChildren();
	size_t NumberOfGroups	= SpecialRoot->GetChildrenNum();

	btVector3		Position,	Scale;
	btQuaternion	Quaternion;

	std::string		MeshName;
	std::string		CollisionMeshName;
	std::string		Id;
	std::string		KeyName;
	int				ObstacleType = 0;

	for(size_t i = 0; i < NumberOfGroups; i++)
	{
		std::string		Tag;
		Tag.reserve(256);
		SpecialGroups[i]->FindVariableZ("Tag")->GetValue(&Tag[0]);
		Tag = Tag.c_str();

		size_t GroupSize = SpecialGroups[i]->GetChildrenNum();
		SpecialList = SpecialGroups[i]->GetChildren();
		for(size_t j = 0; j < GroupSize; j++)
		{
			MeshName.clear();
			CollisionMeshName.clear();
			Id.clear();
			KeyName.clear();
			Special = SpecialList[j];

			ExtractFromElement(Special, 
				Id, MeshName, CollisionMeshName, Position,	Scale, Quaternion);

			WriteCommandLine("\n<Defining Special> ID:%s D:%s C:%s\nP: %f, %f, %f\nS: %f, %f, %f\nQ: %f, %f, %f, %f",
				Id.c_str(), MeshName.c_str(), CollisionMeshName.c_str(), 
				Position.getX(), Position.getY(), Position.getZ(),
				Scale.getX(), Scale.getY(), Scale.getZ(),
				Quaternion.getX(), Quaternion.getY(), Quaternion.getZ(), Quaternion.getW());

			if(Tag == "Needle")
			{
				ObstacleType = 1;
			}
			else if(Tag == "HotPad")
			{
				ObstacleType = 2;
			}
			else if(Tag == "ColdPad")
			{
				ObstacleType = 3;
			}

			KeyName = Tag + "_" + Id;
			KeyName = KeyName.c_str();
			Ogre::SceneNode * Node = m_pMapRoot->createChildSceneNode(KeyName);
			Node->setInheritOrientation(true);
			Ogre::Entity	*	Display(NULL), * Collision(NULL);

			if(MeshName.length() || CollisionMeshName.length())
			{
				System_OgreHandler::BlockRender();
				if(MeshName.size() > 0)
				{
					size_t it = MeshName.find(".mesh");
					ASSERT(it > 0, "FileName Have no .mesh in the name")				
					Display = m_pSceneManager->createEntity(KeyName + "_D" + MeshName.substr(0, it), MeshName);
					switch(ObstacleType)
					{
					case 1:Display->setMaterialName("TF2NPR");
						break;
					case 2:Display->setMaterialName("HotPad");
						break;
					case 3:Display->setMaterialName("ColdPad");
						break;
					}
				}
				if(CollisionMeshName.size() > 0)
				{
					size_t it = CollisionMeshName.find(".mesh");
					ASSERT(it > 0, "FileName Have no .mesh in the name")
					Collision = m_pSceneManager->createEntity(KeyName + "_C" + CollisionMeshName.substr(0, it), CollisionMeshName);
				}
				System_OgreHandler::UnblockRender();
			}
			// At this Point you would have extrated the following :
			// Position, scale, Quaterntion, display mesh, collision mesh
			// Display and collision can be NULL, do take note


			//m_Obstacles.push_back(NULL);	// Add to this list

			Content_Obstacle *	Obstacles = new Content_Obstacle;
			Obstacles->AttachObject(Node);
			Obstacles->Create(Display, Collision, Position, Scale, Quaternion,ObstacleType);

			m_Obstacles.push_back(Obstacles);
		}
	}
}