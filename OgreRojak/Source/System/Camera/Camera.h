#pragma once

/* Default No clip camera , Hold Space to move	*/
/* Need to register a camera from a Viewport	*/

class System_Camera
{	
	float				mfSpeedFactor;
	float				mfRollAngle;

	SmartPtr<System_OISHandler>	Registered_Input;	// Reference only
public:
	SmartPtr<Ogre::Camera>		Registered_Camera;	// Reference only, outsiders may use this to change position etc

	System_Camera(Ogre::Camera * Camera);
	~System_Camera();	// Release all reference
	
	inline void			ResetAngle()		{ mfRollAngle = 0.0f; }	
	inline const float	RollAngle() const	{ return mfRollAngle; }
	virtual void Step(const float & Interval);
};