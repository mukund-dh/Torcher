// Mukund Dhananjay - 2024

#pragma once

#include "Windows/WindowsPlatformCompilerPreSetup.h"


#define LOCTEXT_NAMESPACE "TorcherPreProcMacros"

#ifndef TORCH_INCLUDES_START
// Macro for disabling warnings before libtorch headers
#define TORCH_INCLUDES_START \
__pragma(warning(push)) \
\
/* Unexpected tokens following a preprocessor directive - expected a new line */ \
__pragma(warning(disable: 4067)) \
\
/* 'identifier' - unreferenced formal parameter */ \
__pragma(warning(disable: 4100)) \
\
/*
* conditional expression is constant
*/ \
__pragma(warning(disable: 4127)) \
\
/*
* 'type' : class 'type1' needs to have dll-interface to be used by clients of class 'type2'
*/ \
__pragma(warning(disable: 4251)) \
\
/*
* 'var' : conversion from 'size_t' to 'type', possible loss of data
*/ \
__pragma(warning(disable: 4267)) \
\
/*
* non - DLL-interface class 'class_1' used as base for DLL-interface class 'class_2'
*/ \
__pragma(warning(disable: 4275)) \
\
/*
* 'struct_name' : structure was padded due to __declspec(align())
*/ \
__pragma(warning(disable: 4324)) \
\
/*
* 'derived class' : destructor was implicitly defined as deleted
* because a base class destructor is inaccessible or deleted
*/ \
__pragma(warning(disable: 4624)) \
\
/*
* 'symbol' is not defined as a preprocessor macro, replacing with '0' for 'directives'
*/ \
__pragma(warning(disable: 4668)) \
\
/*
* 'user-defined type' : possible change in behavior, change in UDT return calling convention
*/ \
__pragma(warning(disable: 4686)) \
\
/*
* unreachable code
*/ \
__pragma(warning(disable: 4702)) \
\
/*
* 'operation' : unsafe mix of type 'type' and type 'type' in operation
*/ \
__pragma(warning(disable: 4805)) \
\
THIRD_PARTY_INCLUDES_START
#endif

#ifndef TORCH_INCLUDES_END
/**
 * Macro for enabling warnings after including LibTorch headers
 */
#define TORCH_INCLUDES_END \
THIRD_PARTY_INCLUDES_END \
__pragma(warning(pop))
#endif



#undef LOCTEXT_NAMESPACE