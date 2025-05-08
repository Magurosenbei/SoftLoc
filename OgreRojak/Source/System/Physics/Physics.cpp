#include "stdafx.h"
#include "Physics.h"

#define USE_PARALLEL_DISPATCHER 1

SmartPtr <System_Physics> Abstract_Single<System_Physics>::m_pInstance(NULL);

System_Physics :: System_Physics()
:	System_Thread(),
	m_pbtCol_Config(NULL), m_pbtCol_Dispatch(NULL), 
	m_pBtBroad_Interface(NULL), m_pbtConstraint_Solver(NULL),
	m_pbtDyn_World(NULL), m_pSoftWorldInfo(NULL)
{
	Label = "System_Physics";
	mPriority = REALTIME_PRIORITY_CLASS;
	mLastState = System_Physics::STEP;
}

bool System_Physics :: Initialize()
{
	m_pbtCol_Config = new btSoftBodyRigidBodyCollisionConfiguration;
	m_pbtCol_Dispatch = new btCollisionDispatcher(m_pbtCol_Config);

	btVector3 min(-1000, -1000, -100), max(1000, 1000, 1000);
	m_pBtBroad_Interface = new btAxisSweep3(min, max, 2048);

	m_pbtGhost_Callback = new btGhostPairCallback;
	m_pBtBroad_Interface->getOverlappingPairCache()->setInternalGhostPairCallback(m_pbtGhost_Callback);

	m_pbtConstraint_Solver = new btSequentialImpulseConstraintSolver;

	m_pbtDyn_World = new btSoftRigidDynamicsWorld(	m_pbtCol_Dispatch, m_pBtBroad_Interface,
													m_pbtConstraint_Solver, m_pbtCol_Config);
	if(!m_pbtDyn_World)
		return false;
	m_pbtDyn_World->setGravity(btVector3(0, -9.8f, 0));
	
	m_pSoftWorldInfo = new btSoftBodyWorldInfo;
	m_pSoftWorldInfo->air_density = 0.4f;
	m_pSoftWorldInfo->water_density = 0.3f;
	m_pSoftWorldInfo->water_offset = 0.3f;								// setting these to 0 first;
	m_pSoftWorldInfo->water_normal = btVector3(0,0,0);	
	m_pSoftWorldInfo->m_gravity = m_pbtDyn_World->getGravity();
	m_pSoftWorldInfo->m_broadphase = m_pBtBroad_Interface;
	m_pSoftWorldInfo->m_dispatcher = m_pbtCol_Dispatch;
	m_pSoftWorldInfo->m_sparsesdf.Initialize();
	
	System_Utility::CompilerCommandLine("Initialized");
	return true;
}

const float local_SubStep = 1.0f / 30.0f;

void System_Physics :: UpdatePhysics(const float & Interval)
{
	m_pSoftWorldInfo->m_sparsesdf.GarbageCollect();
	m_pbtDyn_World->applyGravity();
	m_pbtDyn_World->stepSimulation(Interval, 1, local_SubStep);
	m_pSoftWorldInfo->m_gravity = m_pbtDyn_World->getGravity();
}

bool System_Physics :: Shutdown()
{
	/* Do some removal check before deleting Dynamics world */
	PostThreadMessage(m_pInstance->ThreadId(), THREAD_STOP, NULL, NULL);
	Sleep(500);	// Give time for thread terminate

	m_pInstance->ClearBodies();
	m_pInstance->ClearShapes();
	/* Clean up */
	try
	{
		m_pInstance->m_pSoftWorldInfo->m_sparsesdf.Reset();

		delete m_pInstance->m_pbtDyn_World;			m_pInstance->m_pbtDyn_World = NULL;
		delete m_pInstance->m_pbtConstraint_Solver;	m_pInstance->m_pbtConstraint_Solver = NULL;
		delete m_pInstance->m_pbtCol_Dispatch;		m_pInstance->m_pbtCol_Dispatch = NULL;
		delete m_pInstance->m_pBtBroad_Interface;	m_pInstance->m_pBtBroad_Interface = NULL;
		delete m_pInstance->m_pbtGhost_Callback;	m_pInstance->m_pbtGhost_Callback = NULL;
		delete m_pInstance->m_pbtCol_Config;		m_pInstance->m_pbtCol_Config = NULL;
		
		delete m_pInstance->m_pSoftWorldInfo;		m_pInstance->m_pSoftWorldInfo = NULL;
	}
	catch(std::exception & e)
	{
		UNREFERENCED_PARAMETER(e);
		WriteCommandLine("Problem -SysPhysics Shutdown : \n%s", e.what());
		return false;
	}
	return true;
}

bool System_Physics :: ThreadProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case THREAD_MSG::STEP:
		World_Soft()->stepSimulation(float(wParam));
		break;
	default:
		return System_Thread::ThreadProc(uMsg, wParam, lParam);
	}
	return true;
}

void System_Physics :: Work(const float & Interval)
{
	m_pbtDyn_World->stepSimulation(Interval);
}

btCollisionShape * System_Physics :: GetCollisionShape(const std::string & Key, btCollisionShape * Shape)
{
	// Query only
	ShapeList::iterator search = m_Shapes.find(Key);
	if(!Shape)
	{
		if(search == m_Shapes.end())
			return NULL;
		else
			return search->second;
	}
	// Don't Exist, add it in
	if(search == m_Shapes.end())
	{
		std::pair <std::string, btCollisionShape *> p(Key, Shape);
		m_Shapes.insert(p);
		return Shape;
	}
	else	// if the shape already existed
	{
		// Clean up automatically
		delete Shape;
		Shape = NULL;

		return search->second;
	}
}

void System_Physics :: ClearShapes()
{
	for(ShapeList::iterator it = m_Shapes.begin();
		it != m_Shapes.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}
	m_Shapes.clear();
}

void System_Physics :: ClearBodies()
{
	btCollisionObjectArray & List = m_pbtDyn_World->getCollisionObjectArray();
	btRigidBody	*	B;
	for (int i = List.size() - 1; i >= 0 ; i--)
	{
		B = btRigidBody::upcast(List[i]);
		if(B && B->getMotionState())
			delete B->getMotionState();

		m_pbtDyn_World->removeCollisionObject(List[i]);
		List[i] = NULL;
		delete B;
	}
	List.clear();
}