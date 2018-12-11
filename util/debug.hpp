#pragma once

#include "../prelude.hpp"

#ifdef PA_DEBUG
#define PD if (true)
#else
#define PD if (false)
#endif

#ifdef PA_DEBUG_LIB
#define PD_LIB if (true)
#else
#define PD_LIB if (false)
#endif
