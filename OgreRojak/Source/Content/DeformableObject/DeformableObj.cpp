#include "stdafx.h"
#include "DeformableObj.h"
#include "Lib/Bullet/BulletSoftBody/btSoftBodyHelpers.h"

#include "System/Physics/Physics.h"

Content_Deformable_Object :: Content_Deformable_Object(System_Camera * Sys_Cam)
: Content_DisplayPhysicsObj(), m_pSoftBody(NULL),  Registered_Camera(Sys_Cam), m_Position(0.0f, 0.0f, 0.0f)
{
}

Content_Deformable_Object :: ~Content_Deformable_Object()
{

	System_Physics::Instance()->World_Soft()->removeCollisionObject(m_pGhost);
	delete m_pGhost;
	Registered_Camera.release();
	if(m_pSoftBody)
	{
		delete m_pSoftBody;
		m_pSoftBody = NULL;
	}

}

void Content_Deformable_Object :: AttachObject(Ogre::SceneNode * node)
{
	ASSERT(node != NULL, "Invalid Node");
	m_pCurrentNode = SmartPtr<Ogre::SceneNode>(node);
}

bool Content_Deformable_Object :: Initialize(Ogre::Entity * Entity)
{
	if(!Entity) return false;
	m_pEntity = SmartPtr<Ogre::Entity>(Entity);
	m_pCurrentNode->attachObject(m_pEntity.get());
	
	/* Extra Mesh Data */
	size_t VertexCount(0), IndexCount(0);
	std::vector<float>	Vertices;
	std::vector<int>	Indices;

	System_OgreHandler::BlockRender();
	if(!System_Utility::RetrieveMeshInformation(m_pEntity->getMesh().get(), VertexCount, Vertices, IndexCount, Indices))
		return false;
	m_pEntity->setMaterialName("SoftBody_Material");	// **Warning Using Shader without matWorld Transform for softbody
	System_OgreHandler::UnblockRender();
	
	//btSoftBodyWorldInfo * WorldInfo = new btSoftBodyWorldInfo;
	//WorldInfo->air_density = 1.0f;
	//WorldInfo->water_density = 0.3f;
	//WorldInfo->water_offset = 0.3f; // setting these to 0 first;
	//WorldInfo->water_normal = btVector3(0,0,0);	
	//WorldInfo->m_gravity = System_Physics::Instance()->World_Soft()->getGravity();
	//WorldInfo->m_broadphase = System_Physics::Instance()->World_Soft()->getBroadphase();
	//WorldInfo->m_dispatcher = System_Physics::Instance()->World_Soft()->getDispatcher();
	//WorldInfo->m_sparsesdf.Initialize();

	std::string Key = System_Utility::FormatText("BALL R:%f", 9.0f);
	
	m_pGhost = new btPairCachingGhostObject;
	m_pGhost->setCollisionShape(System_Physics::Instance()->GetCollisionShape(Key, new btSphereShape(9.0f)));
	m_pGhost->setCollisionFlags(btCollisionObject::CO_GHOST_OBJECT);
	m_pGhost->setActivationState(DISABLE_DEACTIVATION);
	System_Physics::Instance()->World_Soft()->addCollisionObject(m_pGhost, btBroadphaseProxy::SensorTrigger, btBroadphaseProxy::AllFilter);
	
	
	m_pSoftBody  =	btSoftBodyHelpers::CreateFromTriMesh(	*System_Physics::Instance()->World_Soft_Info(), &Vertices[0], 
															&Indices[0], static_cast<int>(IndexCount) / 3);
	
	m_pSoftBody->setActivationState(DISABLE_DEACTIVATION);
	m_pSoftBody->getVolume();

	m_PreviousVertex.resize(m_pSoftBody->m_nodes.size());
	m_PreviousNormal.resize(m_pSoftBody->m_nodes.size());

	__m128 Divide = _mm_set1_ps(1.0f / m_pSoftBody->m_nodes.size());
	memcpy(&m_kDivider, &Divide, 16);
	
	// READ m_cfg of softbody , "Find Definition"

	m_pSoftBody->m_materials[0]->m_kAST = 0.1f;
	m_pSoftBody->m_materials[0]->m_kLST = 0.3f;
	m_pSoftBody->m_materials[0]->m_kVST = 0.4f;
	m_pSoftBody->m_cfg.kDF = 0.3f;
	m_pSoftBody->m_cfg.kDP = 0.01f;
	m_pSoftBody->m_cfg.kPR = 20000;

	m_pSoftBody->setTotalMass(100.0f);
	m_pSoftBody->setRestitution(0.0f);
	m_pSoftBody->m_cfg.piterations = 4;
	m_pSoftBody->generateClusters(32);
	m_pSoftBody->m_cfg.collisions = 0;
	m_pSoftBody->m_cfg.collisions	+=  btSoftBody::fCollision::CL_RS + btSoftBody::fCollision::VF_SS;

	m_pSoftBody->getCollisionShape()->setMargin(0.35f);	
#ifdef _DEBUG
	m_pCurrentNode->showBoundingBox(true);
	m_pCurrentNode->setInheritOrientation(false);
#endif
	
	return true;
}

void Content_Deformable_Object :: MergeData()
{
	btAlignedObjectArray<btSoftBody::Node> & Nodes = m_pSoftBody->m_nodes;

	Ogre::SubMesh*  Sub = m_pEntity->getMesh()->getSubMesh(0);
	Ogre::VertexData * VertexData = (Sub->useSharedVertices)? m_pEntity->getMesh()->sharedVertexData : Sub->vertexData;
	const Ogre::VertexElement * PosElement = VertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
	Ogre::HardwareVertexBufferSharedPtr VBuffer = VertexData->vertexBufferBinding->getBuffer(PosElement->getSource());

	const Ogre::VertexElement * NormElement = VertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_NORMAL);
	Ogre::HardwareVertexBufferSharedPtr NBuffer = VertexData->vertexBufferBinding->getBuffer(NormElement->getSource());
	size_t NormalSize = NBuffer->getVertexSize();

	unsigned char * vertex = static_cast<unsigned char*>(VBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
	unsigned char * normal = vertex;
	float * localFloats(NULL), * localNormals(NULL);
	size_t VertexSize = VBuffer->getVertexSize();

	memset(&m_Position, 0, 16);
	for(int i = 0; i < Nodes.size(); i++, vertex += VertexSize, normal += NormalSize)
	{	
		PosElement->baseVertexPointerToElement(vertex, &localFloats);
		NormElement->baseVertexPointerToElement(normal, &localNormals);
		
		if(	_isnan(Nodes[i].m_x.m_floats[0]) || _isnan(Nodes[i].m_x.m_floats[1]) || _isnan(Nodes[i].m_x.m_floats[2])
			|| _isnan(Nodes[i].m_n.m_floats[0]) || _isnan(Nodes[i].m_n.m_floats[1]) || _isnan(Nodes[i].m_n.m_floats[2]))
		{
			Nodes[i].m_x = m_PreviousVertex[i];
			Nodes[i].m_n = m_PreviousNormal[i];
		}

		memcpy(localFloats, Nodes[i].m_x.m_floats, 12);
		memcpy(localNormals, Nodes[i].m_n.m_floats, 12);

		m_Position += Nodes[i].m_x;

		m_PreviousVertex[i] = Nodes[i].m_x;
		m_PreviousNormal[i] = Nodes[i].m_n;
	}
	VBuffer->unlock();
	m_Position *= m_kDivider;
	m_pCurrentNode->setPosition(m_Position.getX(), m_Position.getY(), m_Position.getZ());
	btTransform Trans;
	Trans.setIdentity();
	Trans.setOrigin(m_Position);
	m_pGhost->getWorldTransform().setOrigin(m_Position);//(Trans);

	if(m_pSoftBody->m_cfg.kPR < 20000)
		m_pSoftBody->m_cfg.kPR += 5.0f;
	else if(m_pSoftBody->m_cfg.kPR > 25000)
		m_pSoftBody->m_cfg.kPR -= 5.0f;

	if(m_pSoftBody->m_cfg.kPR < 15000)
	{
		// set blue
		m_pEntity->getSubEntity(0)->setCustomParameter(1, Ogre::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else if(m_pSoftBody->m_cfg.kPR > 25000)
	{
		m_pEntity->getSubEntity(0)->setCustomParameter(1, Ogre::Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	}
	else
		m_pEntity->getSubEntity(0)->setCustomParameter(1, Ogre::Vector4(0.0f, 1.0f, 0.0f, 1.0f));
}