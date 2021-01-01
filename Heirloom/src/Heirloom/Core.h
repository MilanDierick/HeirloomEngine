#pragma once

#ifdef HL_PLATFORM_WINDOWS
	#ifdef HL_DYNAMIC_LINK
		#ifdef HL_BUILD_DLL
			#define HL_API __declspec(dllexport)
		#else
			#define HL_API __declspec(dllimport)
		#endif
	#else
		#define HL_API
	#endif
#elif HL_PLATFORM_LINUX
	#error Linux support is currently not implemented!
#else
	#error Heirloom currently only supports Windows!
#endif

#ifdef HL_DEBUG
    #define HL_ENABLE_ASSERTS
#endif

#ifdef HL_ENABLE_ASSERTS
	#define HL_ASSERT(x, ...) { if(!(x)) { HL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define	HL_CORE_ASSERT(x, ...) { if(!(x)) { HL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HL_ASSERT(x, ...)
	#define HL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)