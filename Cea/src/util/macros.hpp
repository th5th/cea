// Debug macro
#ifndef CEA_MACROS_H
#define CEA_MACROS_H

#ifdef CEA_DEBUG
#define DEBUG_OUT(s) do{ std::cout << (s) << std::endl; }while(false)
#else
#define DEBUG_OUT(s) do{ }while(false)
#endif // CEA_DEBUG

#endif // CEA_MACROS_H
