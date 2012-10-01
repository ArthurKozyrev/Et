
#include "Common.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
namespace Detail {

std::wstring VariantBoolToStr(VARIANT_BOOL value)
{
	return std::wstring((value == VARIANT_TRUE) ? L"true" : L"false");
}

VARIANT_BOOL StrToVariantBool(const std::wstring& value)
{
	return (_wcsicmp(value.c_str(), L"true") == 0) ? VARIANT_TRUE : VARIANT_FALSE;
}

} //namespace Detail
} //namespace XML
} //namespace Et
