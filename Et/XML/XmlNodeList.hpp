
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlTypes.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
	
class XmlNodeList sealed
{
public:
	explicit XmlNodeList(const _DOMNodeListPtr_t& ptr);
	XmlNodeList(const XmlNodeList& other);
	XmlNodeList(_DOMNodeListPtr_t&& ptr);
	XmlNodeList(XmlNodeList&& other);
	virtual ~XmlNodeList();

public:
	size_t GetCount() const;
	XmlNode GetNode(size_t index) const;
	XmlNode GetNode(const std::wstring& name, size_t index) const;
	XmlNode GetNode(XmlNodeType type, size_t index) const;
	XmlNode GetNode(XmlNodeType type, const std::wstring& name, size_t index) const;
	
public:
	XmlNodeList& operator=(const XmlNodeList& other);
	XmlNodeList& operator=(XmlNodeList&& other);
	operator bool() const;
	bool operator!() const;
	XmlNode operator[](size_t index) const;
	bool operator==(const XmlNodeList& other) const;
	bool operator!=(const XmlNodeList& other) const;

protected:
	XmlNodeList();

protected:
	_DOMNodeListPtr_t _implPtr;
};

} //namespace XML
} //namespace Et
