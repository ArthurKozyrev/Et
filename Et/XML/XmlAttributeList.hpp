
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlTypes.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
	
class XmlAttributeList sealed
{
public:
	explicit XmlAttributeList(const _DOMAttributeListPtr_t& ptr);
	XmlAttributeList(const XmlAttributeList& other);
	XmlAttributeList(_DOMAttributeListPtr_t&& ptr);
	XmlAttributeList(XmlAttributeList&& other);
	virtual ~XmlAttributeList();
	
public:
	size_t GetCount() const;
	XmlNode GetAttribute(size_t index) const;
	XmlNode GetAttribute(const std::wstring& name) const;
	XmlNode GetAttribute(const std::wstring& local_name, const std::wstring& namespace_uri) const;
	std::wstring GetAttributeValue(size_t index) const;
	std::wstring GetAttributeValue(const std::wstring& name) const;
	
	XmlNode InsertAttribute(const XmlNode& new_attribute) throw(...);
	
	bool SetAttributeValue(size_t index, const std::wstring& value);
	bool SetAttributeValue(const std::wstring& name, const std::wstring& value);

	XmlNode RemoveAttribute(size_t index);
	XmlNode RemoveAttribute(const std::wstring& name);
	XmlNode RemoveAttribute(const std::wstring& local_name, const std::wstring& namespace_uri);

public:
	XmlAttributeList& operator=(const XmlAttributeList& other);
	XmlAttributeList& operator=(XmlAttributeList&& other);
	operator bool() const;
	bool operator!() const;
	XmlNode operator[](size_t index) const;
	bool operator==(const XmlAttributeList& other) const;
	bool operator!=(const XmlAttributeList& other) const;
	
protected:
	XmlAttributeList();

protected:
	_DOMAttributeListPtr_t _implPtr;
};

} //namespace XML
} //namespace Et
