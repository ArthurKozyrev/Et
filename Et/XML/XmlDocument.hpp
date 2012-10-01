
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlTypes.hpp>
#include <Et\XML\XmlNode.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

class XmlDocument sealed : public XmlNode
{
private:
	using XmlNode::CloneNode;
	using XmlNode::GetAttributeList;
	using XmlNode::GetValue;
	using XmlNode::SetValue;
	using XmlNode::operator bool;
	using XmlNode::operator!;
	
public:
	XmlDocument() throw(...);
	explicit XmlDocument(const _DOMDocumentPtr_t& ptr) throw(...);
	XmlDocument(const XmlDocument& other);
	XmlDocument(XmlDocument&& other);
	~XmlDocument();

public:
	void AbortLoading();

	XmlDocument Clone() const throw(...);
	
	XmlNode CreateNode(XmlNodeType type, const std::wstring& name, const std::wstring& namespace_uri = L"") const throw(...);
	XmlElement CreateElement(const std::wstring& name, const std::wstring& namespace_uri = L"") const;
	XmlNode CreateAttribute(const std::wstring& name, const std::wstring& value, const std::wstring& namespace_uri = L"") const;
	XmlNode CreateTextNode(const std::wstring& text) const;
	XmlNode CreateComment(const std::wstring& text) const;

	std::wstring GetDocumentProperty(XmlDocumentProperty property) const;
	XmlDocumentState GetDocumentState() const;
	std::wstring GetDocumentURL() const;
	XmlNode GetDocumentTypeDefinition() const;
	XmlAttributeList GetDocumentTypeEntities() const;
	std::wstring GetDocumentEncoding() const;
	XmlElement GetDocumentElement() const;
	XmlNodeList GetElementsByTagName(const std::wstring& name) const;
	XmlParseError GetParseError() const;
	
	bool IsHasFeature(const std::wstring& feature, const std::wstring& version) const;
	bool IsReady() const;
	
	void Load(const void* buffer, size_t size) throw(...);
	void Load(const std::wstring& filename) throw(...);
	void Load(IStream* stream) throw(...);
	
	void Save(const std::wstring& filename) const throw(...);
	void Save(IStream* stream) const throw(...);
	
	void SetDocumentProperty(XmlDocumentProperty property, const std::wstring& value);
	bool SetDocumentEncoding(const std::wstring& encoding);
	bool SetDocumentElement(const XmlElement& new_root);
	
	XmlDocument Transform(const XmlNode& xsl) const throw(...);
	
	XmlParseError Validate() const throw(...);
	XmlParseError ValidateNode(const XmlNode& node) const throw(...);
	
public:
	XmlDocument& operator=(const XmlDocument& other);
	XmlDocument& operator=(XmlDocument&& other);
	
	friend XmlSerializer;
};

} //namespace XML
} //namespace Et
