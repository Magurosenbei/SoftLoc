#pragma once

/* Use GetCollisionShape during creation of bodies, Collisionshapes can be shared safely, therefore reusing to save memory */


class System_Physics : public Abstract_Single <System_Physics> , public System_Thread
{	
	friend class Abstract_Single <System_Physics>;
	friend int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int);
	/* Configurations */
	btDefaultCollisionConfiguration	*	m_pbtCol_Config;
	btCollisionDispatcher			*	m_pbtCol_Dispatch;
	btBroadphaseInterface			*	m_pBtBroad_Interface;
	btGhostPairCallback				*	m_pbtGhost_Callback;
	btConstraintSolver				*	m_pbtConstraint_Solver;

protected:
	/* Thread */
	virtual bool	ThreadProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void	Work(const float & Interval);
	/* Mainly */
	btDiscreteDynamicsWorld			*	m_pbtDyn_World;
	btSoftBodyWorldInfo				*	m_pSoftWorldInfo;

	typedef std::map	<std::string, btCollisionShape *>	ShapeList;
	ShapeList												m_Shapes;

	System_Physics();
public:
	inline btSoftBodyWorldInfo		* World_Soft_Info() const { return m_pSoftWorldInfo; }
	inline btDiscreteDynamicsWorld	* World()			const { return m_pbtDyn_World; }
	inline btSoftRigidDynamicsWorld	* World_Soft()		const { return static_cast<btSoftRigidDynamicsWorld *>(m_pbtDyn_World); }

	bool	Initialize();
	void	UpdatePhysics(const float & Interval);
	static bool	Shutdown();

	// Check the list if the shape already exist, if not add to the list. If added to list, param Shape is NULLED and returned.
	btCollisionShape	*	GetCollisionShape(const std::string & Key, btCollisionShape * Shape);
	// Clear the list;
	void					ClearShapes();
	void					ClearBodies();

	enum THREAD_MSG {	STEP = THREAD_LASTSTATE + 1		};
};

/* List of Keys */
/* W, H, D, R, meshname are param values */
// box W_H_D	e.g box 5_20_10
// sphere R		e.g sphere 14.0f
// tri meshname e.g tri boxshape.mesh
