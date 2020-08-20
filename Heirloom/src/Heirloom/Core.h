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

#ifdef HL_ENABLE_ASSERTS
	#define HL_ASSERT(x, ...) { if(!(x)) { HL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define	HL_CORE_ASSERT(, ...) { if(!(x)) { HL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HL_ASSERT(x, ...)
	#define HL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)