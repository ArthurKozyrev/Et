
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlTypes.hpp>
#include <Et\XML\XmlNode.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
	
class XmlElement sealed : public XmlNode
{
private:
	using XmlNode::GetValue;
	using XmlNode::SetValue;
	
public:
	explicit XmlElement(const _DOMElementPtr_t& ptr);
	XmlElement(const XmlNode& node) throw(...);
	XmlElement(const XmlElement& element);
	XmlElement(XmlNode&& node) throw(...);
	XmlElement(XmlElement&& element);
	~XmlElement();
	
public:
	bool AddAttribute(const std::wstring& name, const std::wstring& value, const std::wstring& namespace_uri = L"") throw(...);

	std::wstring GetName() const override;
	std::wstring GetText() const override;
	std::wstring GetText(size_t index) const;
	
	XmlElement GetPreviousSiblingElement() const;
	XmlElement GetNextSiblingElement() const;
	
	size_t GetChildElementCount() const;
	XmlElement GetFirstChildElement() const;
	XmlElement GetLastChildElement() const;
	XmlElement GetChildElement(size_t index) const;
	XmlElement GetChildElement(const std::wstring& name, size_t index = 0) const;
	XmlNodeList GetElementsByName(const std::wstring& name) const;

	size_t GetAttributeCount() const;
	XmlNode GetAttribute(size_t index) const;
	XmlNode GetAttribute(const std::wstring& name) const;
	XmlNode GetAttribute(const std::wstring& local_name, const std::wstring& namespace_uri) const;
	std::wstring GetAttributeValue(const std::wstring& name) const;
	
	bool IsHasAttributes() const;

	void NormalizeText();

	XmlNode RemoveAttribute(size_t index);
	XmlNode RemoveAttribute(const std::wstring& name);
	XmlNode RemoveAttribute(const std::wstring& local_name, const std::wstring& namespace_uri);
	void RemoveAllAttributes();
	void RemoveAll() override;

	bool SetText(const std::wstring& text) throw(...) override;
	bool SetText(const std::wstring& text, size_t index) throw(...);
	
public:
	XmlElement& operator=(const XmlElement& other);
	XmlElement& operator=(XmlElement&& other);
	
protected:
	XmlElement();
};

} //namespace XML
} //namespace Et
