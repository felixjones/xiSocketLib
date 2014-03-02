#ifndef __OS_H__
#define __OS_H__

#if defined( _WIN32 ) || defined( _WIN64 )
	#define __WINDOWS__

	#ifdef _WIN64
		#define __X64__
	#else
		#define __X32__
	#endif

	#pragma warning( disable: 4996 )
#endif

#ifdef __APPLE__
	#include <TargetConditionals.h>

	#ifdef TARGET_OS_MAC
		#define __OS_X__
		#define __X64__
	#endif
#endif

#ifdef __linux__
	#define __LINUX__

#if defined( __LP64__ ) || defined( _LP64 )
	#define __X64__
#else
	#define __X32__
#endif
#endif

#if defined( __LINUX__ ) || defined( __OS_X__ )
	#define __POSIX__
#else
	#define	__WIN_API__
#endif

#if !defined( __POSIX__ ) && !defined( __WIN_API__ )
	#error	"Unknown platform"
#endif

#endif