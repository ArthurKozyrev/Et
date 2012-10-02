
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlTypes.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

class XmlParseError sealed
{
public:
	typedef std::vector<XmlParseError> ValidationErrorList_t;

public:
	XmlParseError();
	explicit XmlParseError(const _DOMParseErrorPtr_t& ptr);
	XmlParseError(const XmlParseError& other);
	XmlParseError(_DOMParseErrorPtr_t&& ptr);
	XmlParseError(XmlParseError&& other);
	virtual ~XmlParseError();
	
public:
	long GetCode() const;
	std::wstring GetDescription() const;
	size_t GetLine() const;
	size_t GetLinePosition() const;
	std::wstring GetLineText() const;
	std::wstring GetURL() const;
	std::wstring GetXPath() const;
	auto GetValidationErrorList() const -> ValidationErrorList_t;
	
public:
	XmlParseError& operator=(const XmlParseError& other);
	XmlParseError& operator=(XmlParseError&& other);
	operator bool() const;
	bool operator!() const;
		
protected:
	mutable _DOMParseErrorPtr_t _implPtr;
};

} //namespace XML
} //namespace Et
