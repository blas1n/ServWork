#pragma once

#if PLATFORM_LINUX
#	include "Linux_TCP.h"
#elif PLATFORM_WINDOWS
#	include "Windows_TCP.h"
#endif