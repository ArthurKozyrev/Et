
#include <Et\XML\XmlElement.hpp>
#include <Et\XML\XmlNodeList.hpp>
#include <Et\XML\XmlAttributeList.hpp>
#include <Et\XML\XmlDocument.hpp>
#include "Detail\DOMNode.hpp"
#include "Detail\Errors.hpp"
#include "Detail\Common.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

using Et::COM::ComPtr;
using Et::XML::Detail::bstr_ptr_t;

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

XmlElement::XmlElement(const _DOMElementPtr_t& ptr) : XmlNode(ptr)
{
}

XmlElement::XmlElement(const XmlNode& node) throw(...) : XmlNode(node)
{
	if (!_implPtr.QueryInterface<_DOMElementPtr_t::Element_t>())
		_ET_XML_THROW(XmlException::InvalidOperation(), Detail::kNodeIsNotAnElement);
}

XmlElement::XmlElement(const XmlElement& element) : XmlNode(element._implPtr)
{
}

XmlElement::XmlElement(XmlNode&& node) throw(...) : XmlNode(std::forward<XmlNode>(node))
{
	if (!_implPtr.QueryInterface<_DOMElementPtr_t::Element_t>())
		_ET_XML_THROW(XmlException::InvalidOperation(), Detail::kNodeIsNotAnElement);
}

XmlElement::XmlElement(XmlElement&& element) : XmlNode(std::move(element._implPtr))
{
}

XmlElement::~XmlElement()
{
}

/*************************************************************************************************/

bool XmlElement::AddAttribute(const std::wstring& name, const std::wstring& value, const std::wstring& namespace_uri) throw(...)
{
	XmlNode attribute = GetOwnerDocument().CreateAttribute(name, namespace_uri);

	if (attribute)
		attribute.SetValue(value);

	return GetAttributeList().InsertAttribute(attribute);
}



std::wstring XmlElement::GetName() const
{
	const _DOMElementPtr_t elementPtr(_implPtr);
	BSTR elementName = nullptr;
	const bstr_ptr_t elementNamePtr(&elementName);
	std::wstring result;
	
	if (elementPtr->get_tagName(&elementName) == S_OK)
		result = elementName;

	return result;
}

std::wstring XmlElement::GetText() const
{
	std::wstring result;

	Detail::GetNodeText(*this, result);

	return result;
}

std::wstring XmlElement::GetText(size_t index) const
{
	const XmlNode childNode = GetChildNode(XmlNodeType::Text, index);
	std::wstring result;

	if (childNode)
		result = childNode.GetValue();

	return result;
}



XmlElement XmlElement::GetPreviousSiblingElement() const
{	
	return GetPreviousSiblingNode(XmlNodeType::Element);
}

XmlElement XmlElement::GetNextSiblingElement() const
{
	return GetNextSiblingNode(XmlNodeType::Element);
}



size_t XmlElement::GetChildElementCount() const
{
	return GetChildNodeCount(XmlNodeType::Element);
}

XmlElement XmlElement::GetFirstChildElement() const
{
	return GetFirstChildNode(XmlNodeType::Element);
}

XmlElement XmlElement::GetLastChildElement() const
{
	return GetLastChildNode(XmlNodeType::Element);
}

XmlElement XmlElement::GetChildElement(size_t index) const
{
	return GetChildNode(XmlNodeType::Element, index);
}

XmlElement XmlElement::GetChildElement(const std::wstring& name, size_t index) const
{
	return GetChildNode(XmlNodeType::Element, name, index);
}

XmlNodeList XmlElement::GetElementsByName(const std::wstring& name) const
{
	const _DOMElementPtr_t elementPtr(_implPtr);
	const _bstr_t elementName(name.c_str());
	_DOMNodeListPtr_t elementListPtr;

	elementPtr->getElementsByTagName(elementName, &elementListPtr);
	
	return XmlNodeList(std::move(elementListPtr));
}



size_t XmlElement::GetAttributeCount() const
{
	return GetAttributeList().GetCount();
}

XmlNode XmlElement::GetAttribute(size_t index) const
{
	return GetAttributeList().GetAttribute(index);
}

XmlNode XmlElement::GetAttribute(const std::wstring& name) const
{
	return GetAttributeList().GetAttribute(name);
}

XmlNode XmlElement::GetAttribute(const std::wstring& local_name, const std::wstring& namespace_uri) const
{
	return GetAttributeList().GetAttribute(local_name, namespace_uri);
}

std::wstring XmlElement::GetAttributeValue(const std::wstring& name) const
{
	return GetAttributeList().GetAttributeValue(name);
}



bool XmlElement::IsHasAttributes() const
{
	return (GetAttributeCount() != 0);
}



void XmlElement::NormalizeText()
{
	const _DOMElementPtr_t elementPtr(_implPtr);

	auto normalizeResult = elementPtr->normalize();
	_ET_XML_ASSERT(normalizeResult == S_OK);

	if (FAILED(normalizeResult))
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotNormalizeText);
}



XmlNode XmlElement::RemoveAttribute(size_t index)
{
	return GetAttributeList().RemoveAttribute(index);
}

XmlNode XmlElement::RemoveAttribute(const std::wstring& name)
{
	return GetAttributeList().RemoveAttribute(name);
}

XmlNode XmlElement::RemoveAttribute(const std::wstring& local_name, const std::wstring& namespace_uri)
{
	return GetAttributeList().RemoveAttribute(local_name, namespace_uri);
}

void XmlElement::RemoveAllAttributes()
{
	XmlAttributeList attributeList = GetAttributeList();
	size_t n = attributeList.GetCount();

	while (n--)
		attributeList.RemoveAttribute(n);
}

void XmlElement::RemoveAll()
{
	XmlNode::RemoveAll();
	RemoveAllAttributes();
}



bool XmlElement::SetText(const std::wstring& text) throw(...)
{
	bool result = false;

	Detail::RemoveNodeText(*this);
	result = SetText(text, 0);

	return result;
}

bool XmlElement::SetText(const std::wstring& text, size_t index) throw(...)
{
	XmlNode childNode = GetChildNode(XmlNodeType::Text, index);
	bool result = false;

	if (!childNode)
	{
		if (index == 0)
		{
			childNode = GetOwnerDocument().CreateTextNode(text);
			result = InsertChildNode(childNode, 0);
		}
	}
	else
		result = childNode.SetValue(text);
				
	return result;
}

/*************************************************************************************************/

XmlElement& XmlElement::operator=(const XmlElement& other)
{
	if (this != &other)
	{
		XmlNode::operator=(other);
	}

	return *this;
}

XmlElement& XmlElement::operator=(XmlElement&& other)
{
	if (this != &other)
	{
		XmlNode::operator=(std::move(other));
	}

	return *this;
}

/*************************************************************************************************/

XmlElement::XmlElement()
{
}

} //namespace XML
} //namespace Et
