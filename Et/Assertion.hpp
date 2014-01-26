
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Elenian Toolkit: assertion
//  Version 1.0.0
//  Copyright © 2011-2014, Arthur Kozyrev
//  Web: https://github.com/ArthurKozyrev/Et
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Available defines:
//    ET_DISABLE_ASSERTS -- disable asserts everywhere
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <crtdbg.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ET_DISABLE_ASSERTS

#ifndef ET_ASSERT
#define ET_ASSERT(expr) ((void)0)
#endif

#else

#ifndef ET_ASSERT
#define ET_ASSERT(expr) _ASSERTE(expr)
#endif

#endif
