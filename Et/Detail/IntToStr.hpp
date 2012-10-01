
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>

#include <string>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace Detail {

template <typename T>
size_t CalculateIntToStrBufferSize(T value);

template <typename Type>
struct _IntToStrResultTypeAdapter;

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
size_t CalculateIntToStrBufferSize(T value)
{
	size_t result = 1;

	if (value < 0)
		++result;

	do {
		value /= 10;
		++result;
	}
	while (value);

	return result;
}

/*************************************************************************************************/

template <>
struct _IntToStrResultTypeAdapter<char>
{
	typedef char _Type_t;
	typedef char* Result_t;
	
	template <typename T>
	static Result_t Convert(T value)
	{
		const size_t bufferSize = CalculateIntToStrBufferSize(value);
		Result_t result = static_cast<Result_t>(calloc(bufferSize, sizeof(_Type_t)));

		if (value < 0)
			_i64toa_s(value, result, bufferSize, 10); else
			_ui64toa_s(value, result, bufferSize, 10);
		
		return result;
	}
};

template <>
struct _IntToStrResultTypeAdapter<wchar_t>
{
	typedef wchar_t _Type_t;
	typedef wchar_t* Result_t;
	
	template <typename T>
	static Result_t Convert(T value)
	{
		const size_t bufferSize = CalculateIntToStrBufferSize(value);
		Result_t result = static_cast<Result_t>(calloc(bufferSize, sizeof(_Type_t)));

		if (value < 0)
			_i64tow_s(value, result, bufferSize, 10); else
			_ui64tow_s(value, result, bufferSize, 10);
		
		return result;
	}
};

template <>
struct _IntToStrResultTypeAdapter<std::string>
{
	typedef std::string _Type_t;
	typedef std::string Result_t;
	
	template <typename T>
	static Result_t Convert(T value)
	{
		const size_t bufferSize = CalculateIntToStrBufferSize(value);
		Result_t result(bufferSize - 1, '\0');

		if (value < 0)
			_i64toa_s(value, const_cast<_Type_t::pointer>(result.data()), bufferSize, 10); else
			_ui64toa_s(value, const_cast<_Type_t::pointer>(result.data()), bufferSize, 10);

		return result;
	}
};

template <>
struct _IntToStrResultTypeAdapter<std::wstring>
{
	typedef std::wstring _Type_t;
	typedef std::wstring Result_t;
	
	template <typename T>
	static Result_t Convert(T value)
	{
		const size_t bufferSize = CalculateIntToStrBufferSize(value);
		Result_t result(bufferSize - 1, L'\0');

		if (value < 0)
			_i64tow_s(value, const_cast<_Type_t::pointer>(result.data()), bufferSize, 10); else
			_ui64tow_s(value, const_cast<_Type_t::pointer>(result.data()), bufferSize, 10);

		return result;
	}
};

} //namespace Detail
} //namespace Et
