#pragma once

#define KeyDown(value) (GetAsyncKeyState(value)&0x8000)? true : false
#define PI 3.14159265f
#define DEGTORAD(a) (a * PI / 180)
#define RADTODEG(a) (a * 180 / PI)

#define SmartPtr std::auto_ptr


#define APP_TITLE "OgreRojak"
#define APP_NOMOUSE

union FLOAT_BYTE
{
	float Value;
	unsigned char byte[4];
};

union INT_BYTE
{
	int Value;
	unsigned char byte[4];
};

union VECTOR3
{
	FMOD_VECTOR		fv;
	unsigned char byte[12];
};
#ifdef _DEBUG
#define WriteCommandLine System_Utility::CompilerCommandLine
#else
#define WriteCommandLine(a, ...)	{}
#endif

