
#include <Et\XML\XmlAttributeList.hpp>
#include <Et\XML\XmlNode.hpp>
#include "Detail\Errors.hpp"

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

XmlAttributeList::XmlAttributeList(const _DOMAttributeListPtr_t& ptr) : _implPtr(ptr)
{
}

XmlAttributeList::XmlAttributeList(const XmlAttributeList& other) : _implPtr(other._implPtr)
{
}

XmlAttributeList::XmlAttributeList(_DOMAttributeListPtr_t&& ptr) : _implPtr(std::forward<_DOMAttributeListPtr_t>(ptr))
{
}

XmlAttributeList::XmlAttributeList(XmlAttributeList&& other) : _implPtr(std::move(other._implPtr))
{
}

XmlAttributeList::~XmlAttributeList()
{
}

/*************************************************************************************************/

size_t XmlAttributeList::GetCount() const
{
	long itemCount = 0;

	_implPtr->get_length(&itemCount);

	return static_cast<size_t>(itemCount);
}

XmlNode XmlAttributeList::GetAttribute(size_t index) const
{
	_DOMNodePtr_t attributePtr;
	
	_implPtr->get_item(static_cast<long>(index), &attributePtr);

	return XmlNode(std::move(attributePtr));
}

XmlNode XmlAttributeList::GetAttribute(const std::wstring& name) const
{
	const _bstr_t attributenName(name.c_str());
	_DOMNodePtr_t attributePtr;
	
	_implPtr->getNamedItem(attributenName, &attributePtr);

	return XmlNode(std::move(attributePtr));
}

XmlNode XmlAttributeList::GetAttribute(const std::wstring& local_name, const std::wstring& namespace_uri) const
{
	const _bstr_t localName(local_name.c_str());
	const _bstr_t namespaceURI(namespace_uri.c_str());
	_DOMNodePtr_t attributePtr;
	
	_implPtr->getQualifiedItem(localName, namespaceURI, &attributePtr);

	return XmlNode(std::move(attributePtr));
}

std::wstring XmlAttributeList::GetAttributeValue(size_t index) const
{
	const XmlNode attribute = GetAttribute(index);
	std::wstring result;

	if (attribute)
		result = attribute.GetValue();

	return result;
}

std::wstring XmlAttributeList::GetAttributeValue(const std::wstring& name) const
{
	const XmlNode attribute = GetAttribute(name);
	std::wstring result;

	if (attribute)
		result = attribute.GetValue();

	return result;
}



XmlNode XmlAttributeList::InsertAttribute(const XmlNode& new_attribute) throw(...)
{
	_DOMNodePtr_t insertedAttributePtr;

	auto setNamedItemResult = _implPtr->setNamedItem(new_attribute._implPtr, &insertedAttributePtr);
	_ET_XML_ASSERT(setNamedItemResult != E_FAIL);

	if (FAILED(setNamedItemResult))
		_ET_XML_THROW(XmlException::InvalidOperation(), Detail::kCannotInsertAttribute);

	return XmlNode(std::move(insertedAttributePtr));
}



bool XmlAttributeList::SetAttributeValue(size_t index, const std::wstring& value)
{
	XmlNode attribute = GetAttribute(index);
	bool result = false;

	if (attribute)
		result = attribute.SetValue(value);

	return result;
}

bool XmlAttributeList::SetAttributeValue(const std::wstring& name, const std::wstring& value)
{
	XmlNode attribute = GetAttribute(name);
	bool result = false;

	if (attribute)
		result = attribute.SetValue(value);

	return result;
}



XmlNode XmlAttributeList::RemoveAttribute(size_t index)
{
	XmlNode attribute = GetAttribute(index);
	XmlNode result;

	if (attribute)
		result = RemoveAttribute(attribute.GetName());
	
	return result;
}

XmlNode XmlAttributeList::RemoveAttribute(const std::wstring& name)
{
	const _bstr_t attributeName(name.c_str());
	_DOMNodePtr_t removedAttributePtr;

	auto removeNamedItemResult = _implPtr->removeNamedItem(attributeName, &removedAttributePtr);
	_ET_XML_ASSERT(removeNamedItemResult != E_FAIL);

	if (FAILED(removeNamedItemResult))
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotRemoveAttribute);

	return XmlNode(std::move(removedAttributePtr));
}

XmlNode XmlAttributeList::RemoveAttribute(const std::wstring& local_name, const std::wstring& namespace_uri)
{
	const _bstr_t localName(local_name.c_str()), namespaceURI(namespace_uri.c_str());
	_DOMNodePtr_t removedAttributePtr;

	auto removeNamedItemResult = _implPtr->removeQualifiedItem(localName, namespaceURI, &removedAttributePtr);
	_ET_XML_ASSERT(removeNamedItemResult != E_FAIL);

	if (FAILED(removeNamedItemResult))
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotRemoveAttribute);

	return XmlNode(std::move(removedAttributePtr));
}

/*************************************************************************************************/

XmlAttributeList& XmlAttributeList::operator=(const XmlAttributeList& other)
{
	if (this != &other)
	{
		_implPtr = other._implPtr;
	}

	return *this;
}

XmlAttributeList& XmlAttributeList::operator=(XmlAttributeList&& other)
{
	if (this != &other)
	{
		_implPtr = std::move(other._implPtr);
	}

	return *this;
}

XmlAttributeList::operator bool() const
{
	return (_implPtr != nullptr);
}

bool XmlAttributeList::operator!() const
{
	return (_implPtr == nullptr);
}

XmlNode XmlAttributeList::operator[](size_t index) const
{
	return GetAttribute(index);
}

bool XmlAttributeList::operator==(const XmlAttributeList& other) const
{
	return _implPtr.IsEqualObject(other._implPtr);
}

bool XmlAttributeList::operator!=(const XmlAttributeList& other) const
{
	return !(operator==(other));
}

/*************************************************************************************************/

XmlAttributeList::XmlAttributeList()
{
}

} //namespace XML
} //namespace Et
