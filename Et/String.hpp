
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Elenian Toolkit: string manipulation
//  Version 1.0.0
//  Copyright © 2011-2014, Arthur Kozyrev
//  Web: https://github.com/ArthurKozyrev/Et
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <locale>

#include <windows.h>

#include <Et\Detail\TrimString.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {

enum class NormalizationType
{
	None                  = 0x00,
	Composition           = 0x01,
	Decomposition         = 0x02,
	ObsoleteComposition   = 0x05,
	ObsoleteDecomposition = 0x06,
};

bool IsNormalizedString(const wchar_t* str, size_t length = std::wstring::npos, NormalizationType type = NormalizationType::Composition);
bool IsNormalizedString(const std::wstring& str, size_t length = std::wstring::npos, NormalizationType type = NormalizationType::Composition);
std::wstring NormalizeString(const wchar_t* str, size_t length = std::wstring::npos, NormalizationType type = NormalizationType::Composition);
std::wstring NormalizeString(const std::wstring& str, size_t length = std::wstring::npos, NormalizationType type = NormalizationType::Composition);

std::wstring AnsiToWide(const char* str, DWORD codepage = CP_ACP);
std::wstring AnsiToWide(const std::string& str, DWORD codepage = CP_ACP);
std::wstring UTF8ToWide(const char* str);
std::wstring UTF8ToWide(const std::string& str);
std::string WideToAnsi(const wchar_t* str, DWORD codepage = CP_ACP);
std::string WideToAnsi(const std::wstring& str, DWORD codepage = CP_ACP);
std::string WideToUTF8(const wchar_t* str);
std::string WideToUTF8(const std::wstring& str);
std::string AnsiToUTF8(const char* str, DWORD codepage = CP_ACP);
std::string AnsiToUTF8(const std::string& str, DWORD codepage = CP_ACP);

template <typename T>
T& TrimString(T& str, bool front = true, bool back = true, const std::locale& locale = std::locale());
template <typename T>
T& TrimAllString(T& str, const std::locale& locale = std::locale());

///////////////////////////////////////////////////////////////////////////////////////////////////

inline bool IsNormalizedString(const wchar_t* str, size_t length, NormalizationType type)
{
	const int stringLength = static_cast<int>((length == std::wstring::npos) ? -1 : length);

	return (::IsNormalizedString(static_cast<NORM_FORM>(type), str, stringLength) == TRUE);
}

inline bool IsNormalizedString(const std::wstring& str, size_t length, NormalizationType type)
{
	const int stringLength = static_cast<int>((length == std::wstring::npos) ? -1 : length);

	return (::IsNormalizedString(static_cast<NORM_FORM>(type), str.c_str(), stringLength) == TRUE);
}

inline std::wstring NormalizeString(const wchar_t* str, size_t length, NormalizationType type)
{
	const int stringLength = static_cast<int>((length == std::wstring::npos) ? -1 : length);
	std::wstring result;

	const int normalizedStringLength = ::NormalizeString(static_cast<NORM_FORM>(type), str, -1, nullptr, 0);

	if (normalizedStringLength > 0)
	{
		result.resize(normalizedStringLength, '\0');
		::NormalizeString(static_cast<NORM_FORM>(type), str, stringLength, const_cast<wchar_t*>(result.data()), normalizedStringLength);
	}

	return result;
}

inline std::wstring NormalizeString(const std::wstring& str, size_t length, NormalizationType type)
{
	return NormalizeString(str.c_str(), length, type);
}

/*************************************************************************************************/

inline std::wstring AnsiToWide(const char* str, DWORD codepage)
{
	std::wstring result;

	const int convertedLength = MultiByteToWideChar(codepage, 0, str, -1, nullptr, 0);

	if (convertedLength > 0)
	{
		result.resize(convertedLength, '\0');
		if (!MultiByteToWideChar(codepage, 0, str, -1, const_cast<wchar_t*>(result.data()), convertedLength))
			result.clear();
	}

	return result;
}

inline std::wstring AnsiToWide(const std::string& str, DWORD codepage)
{
	return Et::AnsiToWide(str.c_str(), codepage);
}

inline std::wstring UTF8ToWide(const char* str)
{
	return AnsiToWide(str, CP_UTF8);
}

inline std::wstring UTF8ToWide(const std::string& str)
{
	return AnsiToWide(str, CP_UTF8);
}

inline std::string WideToAnsi(const wchar_t* str, DWORD codepage)
{
	std::string result;

	const int convertedLength = WideCharToMultiByte(codepage, 0, str, -1, nullptr, 0, nullptr, nullptr);

	if (convertedLength > 0)
	{
		result.resize(convertedLength, '\0');
		if (!WideCharToMultiByte(codepage, 0, str, -1, const_cast<char*>(result.data()), convertedLength, nullptr, nullptr))
			result.clear();
	}

	return result;
}

inline std::string WideToAnsi(const std::wstring& str, DWORD codepage)
{
	return WideToAnsi(str.c_str(), codepage);
}

inline std::string WideToUTF8(const wchar_t* str)
{
	return WideToAnsi(str, CP_UTF8);
}

inline std::string WideToUTF8(const std::wstring& str)
{
	return WideToAnsi(str, CP_UTF8);
}

inline std::string AnsiToUTF8(const char* str, DWORD codepage)
{
	auto temp = AnsiToWide(str, codepage);
	return WideToUTF8(temp);
}

inline std::string AnsiToUTF8(const std::string& str, DWORD codepage)
{
	auto temp = AnsiToWide(str, codepage);
	return WideToUTF8(temp);
}

/*************************************************************************************************/

template <typename T>
T& TrimString(T& str, bool front, bool back, const std::locale& locale)
{
	if (back)
		Et::Detail::_TrimStringBack(str, locale);

	if (front)
		Et::Detail::_TrimStringFront(str, locale);
	
	return str;
}

template <typename T>
T& TrimAllString(T& str, const std::locale& locale)
{
	Et::Detail::_TrimStringBack(str, locale);
	Et::Detail::_TrimStringFront(str, locale);
	Et::Detail::_TrimAllString(str, locale);

	return str;
}

} //namespace Et
