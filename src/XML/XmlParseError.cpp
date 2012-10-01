
#include <Et\XML\XmlParseError.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

using Et::COM::ComPtr;
using Et::XML::Detail::bstr_ptr_t;

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

XmlParseError::XmlParseError()
{
}

XmlParseError::XmlParseError(const _DOMParseErrorPtr_t& ptr) : _implPtr(ptr)
{
}

XmlParseError::XmlParseError(const XmlParseError& other) : _implPtr(other._implPtr)
{
}

XmlParseError::XmlParseError(_DOMParseErrorPtr_t&& ptr) : _implPtr(std::forward<_DOMParseErrorPtr_t>(ptr))
{
}

XmlParseError::XmlParseError(XmlParseError&& other) : _implPtr(std::move(other._implPtr))
{
}

XmlParseError::~XmlParseError()
{
}

/*************************************************************************************************/

long XmlParseError::GetCode() const
{
	long errorCode = 0;
	
	_implPtr->get_errorCode(&errorCode);
	
	return errorCode;
}

std::wstring XmlParseError::GetMessage() const
{
	BSTR description = nullptr;
	const bstr_ptr_t descriptionPtr(&description);
	std::wstring result;

	if (_implPtr->get_reason(&description) == S_OK)
		result = description;

	return result;
}

size_t XmlParseError::GetLine() const
{
	long lineNumber = 0;

	_implPtr->get_line(&lineNumber);

	return static_cast<size_t>(lineNumber);
}

size_t XmlParseError::GetLinePosition() const
{
	long linePosition = 0;

	_implPtr->get_linepos(&linePosition);

	return static_cast<size_t>(linePosition);
}

std::wstring XmlParseError::GetLineText() const
{
	BSTR lineText = nullptr;
	const bstr_ptr_t lineTextPtr(&lineText);
	std::wstring result;

	if (_implPtr->get_srcText(&lineText) == S_OK)
		result = lineText;

	return result;
}

std::wstring XmlParseError::GetURL() const
{
	BSTR documentURL = NULL;
	const bstr_ptr_t documentURLPtr(&documentURL);
	std::wstring result;

	if (_implPtr->get_url(&documentURL) == S_OK)
		result = documentURL;

	return result;
}

std::wstring XmlParseError::GetXPath() const
{
	BSTR errorXPath = NULL;
	const bstr_ptr_t noderXPathPtr(&errorXPath);
	std::wstring result;
	
	if (_implPtr->get_errorXPath(&errorXPath) == S_OK)
		result = errorXPath;
	
	return result;
}

auto XmlParseError::GetValidationErrorList() const -> ValidationErrorList_t
{
	ComPtr<MSXML6::IXMLDOMParseErrorCollection> parseErrorListPtr;
	ValidationErrorList_t result;

	if (_implPtr->get_allErrors(&parseErrorListPtr) == S_OK)
	{
		long itemCount = 0;

		parseErrorListPtr->get_length(&itemCount);

		for (long i = 0; i < itemCount; ++i)
		{
			_DOMParseErrorPtr_t parseErrorPtr;

			if (parseErrorListPtr->get_item(i, &parseErrorPtr) == S_OK)
				result.insert(result.end(), std::move(parseErrorPtr));
		}
	}

	return result;
}

/*************************************************************************************************/

XmlParseError& XmlParseError::operator=(const XmlParseError& other)
{
	if (this != &other)
	{
		_implPtr = other._implPtr;
	}
	
	return *this;
}

XmlParseError& XmlParseError::operator=(XmlParseError&& other)
{
	if (this != &other)
	{
		_implPtr = std::move(other._implPtr);
	}
	
	return *this;
}

XmlParseError::operator bool() const
{
	return (_implPtr != nullptr);
}

bool XmlParseError::operator!() const
{
	return (_implPtr == nullptr);
}

} //namespace XML
} //nemspace Et
