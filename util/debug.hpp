#ifndef DEBUG_HPP_OB5Y82L9
#define DEBUG_HPP_OB5Y82L9

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

#endif /* end of include guard: DEBUG_HPP_OB5Y82L9 */
