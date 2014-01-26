
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Elenian Toolkit: STL deleters for COM
//  Version 1.0.0
//  Copyright © 2011-2014, Arthur Kozyrev
//  Web: https://github.com/ArthurKozyrev/Et
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <oleauto.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace COM {
	
struct BSTRDeleter
{
	void operator()(BSTR* ptr) const
	{
		if (ptr)
			SysFreeString(*ptr);
	}
};

} //namespace COM
} //namespace Et
