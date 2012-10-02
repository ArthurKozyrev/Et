
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlTypes.hpp>
#include <Et\XML\XmlException.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
	
class XmlNode
{
public:
	explicit XmlNode(const _DOMNodePtr_t& ptr);
	XmlNode(const XmlNode& other);
	XmlNode(_DOMNodePtr_t&& ptr);
	XmlNode(XmlNode&& other);
	virtual ~XmlNode();
	
public:
	void AppendChildNode(const XmlNode& new_child) throw(...);
	
	XmlNode CloneNode(bool child_nodes) const;
	
	static XmlNode EmptyNode();
	
	XmlNodeType GetNodeType() const;
	std::wstring GetNamespaceURI() const;
	std::wstring GetPrefix() const;
	std::wstring GetLocalName() const;
	virtual std::wstring GetName() const;
	virtual std::wstring GetValue() const;
	virtual std::wstring GetText() const;
	virtual std::wstring GetXML() const;

	XmlDocument GetOwnerDocument() const throw(...);
	XmlNode GetParentNode() const;
	XmlNode GetPreviousSiblingNode() const;
	XmlNode GetPreviousSiblingNode(XmlNodeType type) const;
	XmlNode GetNextSiblingNode() const;
	XmlNode GetNextSiblingNode(XmlNodeType type) const;
	
	size_t GetChildNodeCount() const;
	size_t GetChildNodeCount(XmlNodeType type) const;
	XmlNode GetFirstChildNode() const;
	XmlNode GetFirstChildNode(XmlNodeType type) const;
	XmlNode GetLastChildNode() const;
	XmlNode GetLastChildNode(XmlNodeType type) const;
	XmlNode GetChildNode(size_t index) const;
	XmlNode GetChildNode(const std::wstring& name, size_t index = 0) const;
	XmlNode GetChildNode(XmlNodeType type, size_t index = 0) const;
	XmlNode GetChildNode(XmlNodeType type, const std::wstring& name, size_t index = 0) const;
	XmlNodeList GetChildNodeList() const;
	XmlAttributeList GetAttributeList() const;
	
	bool InsertChildNode(const XmlNode& new_child, size_t index) throw(...);
	bool InsertChildNode(const XmlNode& new_child, const XmlNode& ref_child) throw(...);
	
	bool IsRoot() const;
	bool IsHasChildNodes() const;
	bool IsParsed() const;
	
	XmlNode ReplaceChildNode(const XmlNode& new_child, const XmlNode& old_child) throw(...);

	XmlNode RemoveChildNode(size_t index);
	XmlNode RemoveChildNode(const std::wstring& name, size_t index);
	XmlNode RemoveChildNode(XmlNodeType type, size_t index);
	XmlNode RemoveChildNode(XmlNodeType type, const std::wstring& name, size_t index);
	XmlNode RemoveChildNode(const XmlNode& child);
	virtual void RemoveAll();
	
	virtual bool SetValue(const std::wstring& value);
	virtual bool SetText(const std::wstring& text);
	
	XmlNode SelectNode(const std::wstring& xpath) const;
	XmlNodeList SelectNodes(const std::wstring& xpath) const;
	
	std::wstring TransformNode(const XmlNode& xsl) const throw(...);
	void TransformNode(const XmlNode& xsl, const std::wstring& filename) const throw(...);
	void TransformNode(const XmlNode& xsl, IStream* stream) const throw(...);

public:
	XmlNode& operator=(const XmlNode& other);
	XmlNode& operator=(XmlNode&& other);
	operator bool() const;
	bool operator!() const;
	bool operator==(const XmlNode& other) const;
	bool operator!=(const XmlNode& other) const;
	
protected:
	XmlNode();

protected:
	_DOMNodePtr_t _implPtr;

	friend XmlAttributeList;
	friend XmlDocument;
};

} //namespace XML
} //namespace Et
