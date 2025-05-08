#include "stdafx.h"
#include "camera.h"

System_Camera :: System_Camera(Ogre::Camera * Camera)
:	Registered_Camera(Camera), mfSpeedFactor(0.2f), mfRollAngle(0)
{
}

System_Camera :: ~System_Camera()
{
	Registered_Camera.release();
	Registered_Input.release();
}

void System_Camera :: Step(const float &Interval)
{
	if(!Registered_Input.get())
		Registered_Input = SmartPtr<System_OISHandler>(System_OISHandler::Instance());

	float SpdInterval = mfSpeedFactor * Interval;
	Ogre::Radian Rad(SpdInterval * 0.01f);

	// Roll of camera, will auto reset to 0

	if(Registered_Input->Keyboard()->isKeyDown(OIS::KC_LEFT) && g_sGAME_STAT == GAME_PHASE::PLAY)
	{
		if(mfRollAngle + Rad.valueRadians() < 0.91094f)
			mfRollAngle += Rad.valueRadians();
	}
	else if(Registered_Input->Keyboard()->isKeyDown(OIS::KC_RIGHT)  && g_sGAME_STAT == GAME_PHASE::PLAY)
	{
		if(mfRollAngle - Rad.valueRadians() > -0.91094f)
			mfRollAngle -= Rad.valueRadians();
	}
	else if(!Registered_Input->Keyboard()->isKeyDown(OIS::KC_RIGHT) &&
			!Registered_Input->Keyboard()->isKeyDown(OIS::KC_LEFT))
	{
		Rad *= 2.0f;	// 2X speed when auto
		if(mfRollAngle + Rad.valueRadians() < 0)
		{
			//Registered_Camera->roll(Rad);
			mfRollAngle += Rad.valueRadians();
		}
		else if(mfRollAngle - Rad.valueRadians() > 0)
		{
			//Registered_Camera->roll(-Rad);
			mfRollAngle -= Rad.valueRadians();
		}
		else if(mfRollAngle != 0.0f)
		{
			//Registered_Camera->roll(Ogre::Radian(-mfRollAngle));
			mfRollAngle = 0.0f;
		}
	}
#ifdef _DEBUG
	/* FPS free CAM */
	if(!Registered_Input->Keyboard()->isKeyDown(OIS::KC_SPACE)) return;

	Ogre::Vector3	CurrentPosition = Registered_Camera->getPosition();
	Ogre::Vector3	FrontVector		= Registered_Camera->getDirection();
	Ogre::Vector3	RightVector		= Registered_Camera->getRight();

	if(Registered_Input->Keyboard()->isKeyDown(OIS::KC_W))
		CurrentPosition += FrontVector * SpdInterval;
	else if(Registered_Input->Keyboard()->isKeyDown(OIS::KC_S))
		CurrentPosition -= FrontVector * SpdInterval;
	if(Registered_Input->Keyboard()->isKeyDown(OIS::KC_D))
		CurrentPosition += RightVector * SpdInterval;
	else if(Registered_Input->Keyboard()->isKeyDown(OIS::KC_A))
		CurrentPosition -= RightVector * SpdInterval;

	Registered_Camera->setPosition(CurrentPosition);
	FrontVector += RightVector * 0.01f * Registered_Input->Mouse().X.rel;
	FrontVector -= Registered_Camera->getUp() * 0.01f * Registered_Input->Mouse().Y.rel;
	Registered_Camera->lookAt(FrontVector + CurrentPosition);
#endif
}