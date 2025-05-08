#pragma once

#include <Ogre.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>
#include <OgreCEGUIRenderer.h>	// inside samples >< don't know why they put there
#include <CEGUI/CEGUI.h>
#include <OIS/OIS.h>


#include "Lib/FMod/fmod.hpp"

#pragma comment (lib, "ode.lib")
#pragma comment (lib, "Lib/FMod/Fmodex_vc.lib")

#include "Lib/TurboircXml/XML.h"
#include "Lib/TurboircXML/mime.h"

//#pragma comment(lib, "Lib/TurboircXml/XMLms.lib")

#include <comutil.h>
#ifdef _DEBUG
#pragma comment(lib, "comsuppd.lib")
#pragma comment(lib, "comsuppwd.lib")
#else
#pragma comment(lib, "comsupp.lib")
#pragma comment(lib, "comsuppw.lib")
#endif

#define MULTI_TEXT _bstr_t

#include "Lib/Bullet/btBulletDynamicsCommon.h"
/* Soft Body */
#include "Lib/Bullet/BulletSoftBody/btSoftBody.h"
#include "Lib/Bullet/BulletSoftBody/btSoftRigidDynamicsWorld.h"
#include "Lib/Bullet/BulletSoftBody/btSoftBodyRigidBodyCollisionConfiguration.h"

#include "lib/Bullet/LinearMath/btScalar.h"
#include "lib/Bullet/BulletCollision/CollisionDispatch/btGhostObject.h"


/* Bt Ogre*/
#include "Lib/BtOgre/BtOgreExtras.h"
#include "Lib/BtOgre/BtOgreGP.h"
#include "Lib/BtOgre/BtOgrePG.h"

#ifdef _DEBUG
#pragma comment (lib, "OgreMain_d.lib")
#pragma comment (lib, "OIS_d.lib")
#pragma comment (lib, "CEGUIBase_d.lib")
#pragma comment (lib, "OgreGUIRenderer_d.lib")
/* Bullet */
#pragma comment (lib, "Lib/Bullet/libbulletdynamics_d.lib")
#pragma comment (lib, "Lib/Bullet/libbulletcollision_d.lib")
#pragma comment (lib, "Lib/Bullet/libbulletmath_d.lib")
#pragma comment (lib, "Lib/Bullet/libbulletsoftbody_d.lib")
#pragma comment (lib, "Lib/Bullet/libbulletmultithreaded_d.lib")
#else
#pragma comment (lib, "OgreMain.lib")
#pragma comment (lib, "OIS.lib")
#pragma comment (lib, "CEGUIBase.lib")
#pragma comment (lib, "OgreGUIRenderer.lib")
/* Bullet */
#pragma comment (lib, "Lib/Bullet/libbulletdynamics.lib")
#pragma comment (lib, "Lib/Bullet/libbulletcollision.lib")
#pragma comment (lib, "Lib/Bullet/libbulletmath.lib")
#pragma comment (lib, "Lib/Bullet/libbulletsoftbody.lib")
#pragma comment (lib, "Lib/Bullet/libbulletmultithreaded.lib")
#endif