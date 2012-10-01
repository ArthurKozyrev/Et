
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <cctype>
#include <locale>
#include <algorithm>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace Detail {

template <typename Char>
bool _IsWhiteSpace(Char ch, const std::locale& locale)
{
	return (std::isspace(ch, locale) || std::isblank(ch, locale) || std::iscntrl(ch, locale));
}

template <typename T>
void _TrimStringFront(T& str, const std::locale& locale)
{
	auto it = std::begin(str);

	while (str.length())
	{
		auto ch = *it;
	
		if (_IsWhiteSpace(ch, locale))
			it = str.erase(it); else
			break;
	}
}

template <typename T>
void _TrimStringBack(T& str, const std::locale& locale)
{
	while (str.length())
	{
		auto ch = str.back();
	
		if (_IsWhiteSpace(ch, locale))
			str.pop_back(); else
			break;
	}
}

template <typename T>
void _TrimAllString(T& str, const std::locale& locale)
{
	for (auto it = std::begin(str); it != std::end(str); )
	{
		auto ch = *it;

		if (Et::Detail::_IsWhiteSpace(ch, locale))
		{
			if (ch == ' ')
			{
				auto it2 = ++it;

				while (it2 != std::end(str) && Et::Detail::_IsWhiteSpace(*it2, locale))
					it2 = str.erase(it2);
			}
			else
				it = str.erase(it);
		}
		else
			++it;
	}
}

} //namespace Detail
} //namespace Et
