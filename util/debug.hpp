#pragma once

#ifdef PA_DEBUG
#define PD(stmt) stmt
#else
#define PD(stmt)
#endif

#ifdef PA_DEBUG_LIB
#define PD_LIB(stmt) stmt
#else
#define PD_LIB(stmt)
#endif
