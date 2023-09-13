#pragma once

#ifdef ST_PLATFORM_WINDOWS
	#if ST_BUILD_DLL
		#define SATURNAPI __declspec(dllexport)
	#else
		#define SATURNAPI __declspec(dllimport)
	#endif
#else
	#error Saturn only supports windows.
#endif