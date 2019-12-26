#pragma once

#if PLATFORM_LINUX
#	include "TCP_Linux.h"
#elif PLATFORM_WINDOWS
#	include "TCP_Windows.h"
#endif