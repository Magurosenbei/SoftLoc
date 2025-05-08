#pragma once

/* Warnings */
// Ogre
#pragma warning (disable : 4100)	
#pragma warning (disable : 4127)
#pragma warning (disable : 4512)	// Assignment operator of CEGUI
#pragma warning (disable : 4482)	// use of enum conversion
#pragma warning (disable : 4189)	// Unreference Variable
#pragma warning (disable : 4244)
#pragma warning (disable : 4245)

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
// C RunTime Header Files
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <tchar.h>
#include <stdexcept>
#include <memory>
#include <xmmintrin.h>  // intel simd header
#include <mmintrin.h>

#include <map>
// OMP
#include <omp.h>

#ifdef _MSC_VER
 #ifdef NDEBUG
	#define ASSERT(exp, msg)	{}
	#define VERIFY(exp, msg)	(exp);
 #else // NDEBUG
	#define ASSERT(exp, msg)	if( !(exp) ) std::_Debug_message(L#msg, _CRT_WIDE(__FILE__), __LINE__);
	#define VERIFY(exp, msg)	if( !(exp) ) std::_Debug_message(L#msg, _CRT_WIDE(__FILE__), __LINE__);
 #endif // end NDEBUG
#else // _MSC_VER
 #ifdef NDEBUG
	#define ASSERT(exp, msg)	{}
	#define VERIFY(exp, msg)	(exp);
 #else // NDEBUG
	#include <cassert>
	#define ASSERT(exp, msg)		assert( (exp) );
	#define VERIFY(exp, msg)		assert( (exp) );
 #endif // end NDEBUG
#endif // end _MSC_VER

#include "Definition/targetver.h"
#include "AppResource/Resource.h"
#include "Definition/LibaryInclude.h"
#include "Definition/Terms.h"
#include "Definition/AbstractTemplate.h"

#include "Definition/AppInclude.h"
