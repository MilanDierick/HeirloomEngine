#pragma once

#ifdef HL_PLATFORM_WINDOWS
	#ifdef HL_BUILD_DLL
		#define HL_API __declspec(dllexport)
	#else
		#define HL_API __declspec(dllimport)
	#endif
#else
	#error Heirloom currently only supports Windows!
#endif

#define BIT(x) (1 << x)