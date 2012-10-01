
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Elenian Toolkit: data conversion
//  Version 1.0.0
//  Copyright © 2011-2012, Arthur Kozyrev
//  Web: https://github.com/ArthurKozyrev/Et
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstddef>

#include <windows.h>

#include <Et\Detail\IntToStr.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {

template <typename R, typename T>
auto IntToStr(T value) -> typename Detail::_IntToStrResultTypeAdapter<R>::Result_t;

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename R, typename T>
auto IntToStr(T value) -> typename Detail::_IntToStrResultTypeAdapter<R>::Result_t
{
	return Detail::_IntToStrResultTypeAdapter<R>::Convert(value);
}

} //namespace Et
