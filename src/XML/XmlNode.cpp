
#include <Et\XML\XmlNode.hpp>
#include <Et\XML\XmlNodeList.hpp>
#include <Et\XML\XmlAttributeList.hpp>
#include <Et\XML\XmlDocument.hpp>
#include <Et\XML\XmlException.hpp>
#include "Detail\DOMNode.hpp"
#include "Detail\Errors.hpp"
#include "Detail\Common.hpp"

#include <shlwapi.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

using Et::COM::ComPtr;
using Et::XML::Detail::bstr_ptr_t;

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

XmlNode::XmlNode(const _DOMNodePtr_t& ptr) : _implPtr(ptr)
{
}

XmlNode::XmlNode(const XmlNode& other) : _implPtr(other._implPtr)
{
}

XmlNode::XmlNode(_DOMNodePtr_t&& ptr) : _implPtr(std::forward<_DOMNodePtr_t>(ptr))
{
}

XmlNode::XmlNode(XmlNode&& other) : _implPtr(std::move(other._implPtr))
{
}

XmlNode::~XmlNode()
{
}

/*************************************************************************************************/

void XmlNode::AppendChildNode(const XmlNode& new_child)
{
	InsertChildNode(new_child, EmptyNode());
}



XmlNode XmlNode::CloneNode(bool child_nodes) const
{
	const VARIANT_BOOL deep = (child_nodes) ? VARIANT_TRUE : VARIANT_FALSE;
	_DOMNodePtr_t clonedNodePtr;

	_implPtr->cloneNode(deep, &clonedNodePtr);
	_ET_XML_ASSERT(clonedNodePtr != nullptr);

	if (!clonedNodePtr)
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotCloneNode);
	
	return XmlNode(std::move(clonedNodePtr));
}



XmlNode XmlNode::EmptyNode()
{
	return XmlNode();
}



XmlNodeType XmlNode::GetNodeType() const
{
	MSXML6::DOMNodeType nodeType = MSXML6::NODE_INVALID;

	_implPtr->get_nodeType(&nodeType);
	_ET_XML_ASSERT(nodeType != MSXML6::NODE_INVALID);

	if (nodeType == MSXML6::NODE_INVALID)
		_ET_XML_THROW(XmlException::InternalError(), Detail::kInvalidNodeType);

	return Detail::EncodeNodeType(nodeType);
}

std::wstring XmlNode::GetNamespaceURI() const
{
	BSTR namespaceURI = nullptr;
	const bstr_ptr_t namespaceURIPtr(&namespaceURI);
	std::wstring result;

	if (_implPtr->get_namespaceURI(&namespaceURI) == S_OK)
		result = namespaceURI;

	return result;
}

std::wstring XmlNode::GetPrefix() const
{
	BSTR namePrefix = nullptr;
	const bstr_ptr_t namePrefixPtr(&namePrefix);
	std::wstring result;

	if (_implPtr->get_prefix(&namePrefix) == S_OK)
		result = namePrefix;

	return result;
}

std::wstring XmlNode::GetLocalName() const
{
	BSTR localName = nullptr;
	const bstr_ptr_t localNamePtr(&localName);
	std::wstring result;

	if (_implPtr->get_baseName(&localName) == S_OK)
		result = localName;

	return result;
}

std::wstring XmlNode::GetName() const
{
	BSTR nodeName = nullptr;
	const bstr_ptr_t nodeNamePtr(&nodeName);
	
	_implPtr->get_nodeName(&nodeName);
	
	return std::wstring(nodeName);
}

std::wstring XmlNode::GetValue() const
{
	_variant_t nodeValue;
	std::wstring result;

	auto nodeValueResult = _implPtr->get_nodeValue(&nodeValue);
	_ET_XML_ASSERT(nodeValueResult != E_FAIL);

	if (FAILED(nodeValueResult))
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotGetNodeValue);

	switch (nodeValue.vt)
	{
		case VT_BSTR:
			result = nodeValue.bstrVal;
			break;
	}
	
	return result;
}

std::wstring XmlNode::GetText() const
{
	BSTR nodeText = nullptr;
	const bstr_ptr_t nodeTextPtr(&nodeText);
	std::wstring result;

	if (_implPtr->get_text(&nodeText) == S_OK)
		result = nodeText;

	return result;
}

std::wstring XmlNode::GetXML() const
{
	BSTR nodeXML = nullptr;
	const bstr_ptr_t nodeXMLPtr(&nodeXML);
	std::wstring result;

	if (_implPtr->get_xml(&nodeXML) == S_OK)
		result = nodeXML;

	return result;
}



XmlDocument XmlNode::GetOwnerDocument() const throw(...)
{
	 ComPtr<MSXML6::IXMLDOMDocument> ownerDocumentPtr;

	_implPtr->get_ownerDocument(&ownerDocumentPtr);
	_ET_XML_ASSERT(ownerDocumentPtr != nullptr);

	if (!ownerDocumentPtr)
		_ET_XML_THROW(XmlException::InvalidOperation(), Detail::kCannotGetOwnerDocument);
	
	return XmlDocument(ownerDocumentPtr);
}

XmlNode XmlNode::GetParentNode() const
{
	_DOMNodePtr_t parentNodePtr;
	
	_implPtr->get_parentNode(&parentNodePtr);

	return XmlNode(std::move(parentNodePtr));
}

XmlNode XmlNode::GetPreviousSiblingNode() const
{
	_DOMNodePtr_t siblingNodePtr;

	_implPtr->get_previousSibling(&siblingNodePtr);

	return XmlNode(std::move(siblingNodePtr));
}

XmlNode XmlNode::GetPreviousSiblingNode(XmlNodeType type) const
{
	XmlNode siblingNode = GetPreviousSiblingNode();
	XmlNode result;
	
	while (siblingNode)
	{
		if ((siblingNode.GetNodeType() & type) != XmlNodeType::None)
		{
			result = std::move(siblingNode);
			break;
		}
		siblingNode = siblingNode.GetPreviousSiblingNode();
	}

	return result;
}

XmlNode XmlNode::GetNextSiblingNode() const
{
	_DOMNodePtr_t siblingNodePtr;

	_implPtr->get_nextSibling(&siblingNodePtr);

	return XmlNode(std::move(siblingNodePtr));
}

XmlNode XmlNode::GetNextSiblingNode(XmlNodeType type) const
{
	XmlNode siblingNode = GetNextSiblingNode();
	XmlNode result;

	while (siblingNode)
	{
		if ((siblingNode.GetNodeType() & type) != XmlNodeType::None)
		{
			result = std::move(siblingNode);
			break;
		}
		siblingNode = siblingNode.GetNextSiblingNode();
	}
	
	return result;
}



size_t XmlNode::GetChildNodeCount() const
{
	return GetChildNodeList().GetCount();
}

size_t XmlNode::GetChildNodeCount(XmlNodeType type) const
{
	const XmlNodeList childNodeList = GetChildNodeList();
	const size_t childCount = childNodeList.GetCount();
	size_t result = 0;

	for (size_t n = 0; n < childCount; ++n)
	{
		if ((childNodeList[n].GetNodeType() & type) != XmlNodeType::None)
			++result;
	}

	return result;
}

XmlNode XmlNode::GetFirstChildNode() const
{
	_DOMNodePtr_t childNodePtr;

	_implPtr->get_firstChild(&childNodePtr);

	return XmlNode(std::move(childNodePtr));
}

XmlNode XmlNode::GetFirstChildNode(XmlNodeType type) const
{
	const XmlNodeList childNodeList = GetChildNodeList();
	const size_t childCount = childNodeList.GetCount();
	XmlNode result;

	for (size_t n = 0; n < childCount; ++n)
	{
		XmlNode childNode = childNodeList[n];

		if ((childNode.GetNodeType() & type) != XmlNodeType::None)
		{
			result = std::move(childNode);
			break;
		}
	}

	return result;
}

XmlNode XmlNode::GetLastChildNode() const
{
	_DOMNodePtr_t childNodePtr;
	
	_implPtr->get_lastChild(&childNodePtr);

	return XmlNode(std::move(childNodePtr));
}

XmlNode XmlNode::GetLastChildNode(XmlNodeType type) const
{
	const XmlNodeList childNodeList = GetChildNodeList();
	const size_t childCount = childNodeList.GetCount();
	size_t n = childCount;
	XmlNode result;
	
	while (n--)
	{
		XmlNode childNode = childNodeList[n];

		if ((childNode.GetNodeType() & type) != XmlNodeType::None)
		{
			result = std::move(childNode);
			break;
		}
	}

	return result;
}

XmlNode XmlNode::GetChildNode(size_t index) const
{
	return GetChildNodeList().GetNode(index);
}

XmlNode XmlNode::GetChildNode(const std::wstring& name, size_t index) const
{
	return GetChildNodeList().GetNode(name, index);
}

XmlNode XmlNode::GetChildNode(XmlNodeType type, size_t index) const
{
	return GetChildNodeList().GetNode(type, index);
}

XmlNode XmlNode::GetChildNode(XmlNodeType type, const std::wstring& name, size_t index) const
{
	return GetChildNodeList().GetNode(type, name, index);
}

XmlNodeList XmlNode::GetChildNodeList() const
{
	_DOMNodeListPtr_t childNodeListPtr;

	_implPtr->get_childNodes(&childNodeListPtr);

	return XmlNodeList(std::move(childNodeListPtr));
}

XmlAttributeList XmlNode::GetAttributeList() const
{
	_DOMAttributeListPtr_t attributeListPtr;

	_implPtr->get_attributes(&attributeListPtr);
	_ET_XML_ASSERT(attributeListPtr != nullptr);
	
	return XmlAttributeList(std::move(attributeListPtr));
}



bool XmlNode::InsertChildNode(const XmlNode& new_child, size_t index)
{
	return InsertChildNode(new_child, GetChildNode(index));
}

bool XmlNode::InsertChildNode(const XmlNode& new_child, const XmlNode& ref_child)
{
	const _variant_t referenceChild(ref_child._implPtr);
	_DOMNodePtr_t insertedNodePtr;

	auto insertBeforeResult = _implPtr->insertBefore(new_child._implPtr, referenceChild, &insertedNodePtr);
	_ET_XML_ASSERT(insertBeforeResult != E_FAIL);

	if (insertBeforeResult == E_FAIL)
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotInsertNode);

	return (insertBeforeResult != E_FAIL);
}



bool XmlNode::IsRoot() const
{
	return (GetParentNode() == EmptyNode());
}

bool XmlNode::IsHasChildNodes() const
{
	VARIANT_BOOL hasChildNodes = VARIANT_FALSE;
	
	_implPtr->hasChildNodes(&hasChildNodes);
	
	return (hasChildNodes == VARIANT_TRUE);
}

bool XmlNode::IsParsed() const
{
	VARIANT_BOOL parsed = VARIANT_FALSE;

	_implPtr->get_parsed(&parsed);

	return (parsed == VARIANT_TRUE);
}



XmlNode XmlNode::ReplaceChildNode(const XmlNode& new_child, const XmlNode& old_child) throw(...)
{
	_DOMNodePtr_t replacedNodePtr;
	
	auto replaceChildResult = _implPtr->replaceChild(new_child._implPtr, old_child._implPtr, &replacedNodePtr);
	_ET_XML_ASSERT(replaceChildResult == S_OK);

	if (replaceChildResult == E_INVALIDARG)
		_ET_XML_THROW(XmlException::InvalidArgument(), Detail::kInvalidArgument);
	else if (FAILED(replaceChildResult))
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotReplaceNode);

	return XmlNode(std::move(replacedNodePtr));
}



XmlNode XmlNode::RemoveChildNode(size_t index)
{
	return RemoveChildNode(GetChildNode(index));
}

XmlNode XmlNode::RemoveChildNode(const std::wstring& name, size_t index)
{
	return RemoveChildNode(GetChildNode(name, index));
}

XmlNode XmlNode::RemoveChildNode(XmlNodeType type, size_t index)
{
	return RemoveChildNode(GetChildNode(type, index));
}

XmlNode XmlNode::RemoveChildNode(XmlNodeType type, const std::wstring& name, size_t index)
{
	return RemoveChildNode(GetChildNode(type, name, index));
}

XmlNode XmlNode::RemoveChildNode(const XmlNode& child)
{
	_DOMNodePtr_t removedNodePtr;
	
	auto removeChildResult = _implPtr->removeChild(child._implPtr, &removedNodePtr);
	_ET_XML_ASSERT(removeChildResult != E_FAIL);

	if (removeChildResult == E_FAIL)
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotRemoveNode);

	return XmlNode(std::move(removedNodePtr));
}

void XmlNode::RemoveAll()
{
	XmlNode childNode = GetLastChildNode();

	while (childNode)
	{
		XmlNode siblingNode = GetPreviousSiblingNode();

		RemoveChildNode(childNode);
		childNode = siblingNode;
	}
}



bool XmlNode::SetValue(const std::wstring& value)
{
	const _variant_t nodeValue(value.c_str());
	bool result = false;

	if (_implPtr->put_nodeValue(nodeValue) == S_OK)
		result = true;

	return result;
}

bool XmlNode::SetText(const std::wstring& text)
{
	const _bstr_t nodeText(text.c_str());
	bool result = false;

	if (_implPtr->put_text(nodeText) == S_OK)
		result = true;
	
	return result;
}



XmlNode XmlNode::SelectNode(const std::wstring& xpath) const
{
	const _bstr_t query(xpath.c_str());
	_DOMNodePtr_t selectedNodePtr;

	_implPtr->selectSingleNode(query, &selectedNodePtr);

	return XmlNode(std::move(selectedNodePtr));
}

XmlNodeList XmlNode::SelectNodes(const std::wstring& xpath) const
{
	const _bstr_t query(xpath.c_str());
	_DOMNodeListPtr_t selectedNodeListPtr;

	_implPtr->selectNodes(query, &selectedNodeListPtr);
	
	return XmlNodeList(std::move(selectedNodeListPtr));
}



std::wstring XmlNode::TransformNode(const XmlNode& xsl) const throw(...)
{
	BSTR transformed = nullptr;
	const bstr_ptr_t transformedPtr(&transformed);
	std::wstring result;
	
	auto transformNodeResult = _implPtr->transformNode(xsl._implPtr, &transformed);
	_ET_XML_ASSERT(transformNodeResult == S_OK);

	if (transformNodeResult == E_INVALIDARG)
		_ET_XML_THROW(XmlException::InvalidArgument(), Detail::kInvalidArgument);
	else if (FAILED(transformNodeResult))
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotTransformNode);

	if (transformed)
		result = transformed;
	
	return result;
}

void XmlNode::TransformNode(const XmlNode& xsl, const std::wstring& filename) const throw(...)
{
	const DWORD fileMode = STGM_CREATE | STGM_WRITE | STGM_SHARE_EXCLUSIVE;
	ComPtr<IStream> fileStreamPtr;

	SHCreateStreamOnFileEx(filename.c_str(), fileMode, 0, TRUE, nullptr, &fileStreamPtr);
	
	if (!fileStreamPtr)
		_ET_XML_THROW(XmlException::CannotAccessFile(), Detail::kCannotAccessFile);

	TransformNode(xsl, fileStreamPtr);
}

void XmlNode::TransformNode(const XmlNode& xsl, IStream* stream) const throw(...)
{
	_ET_XML_ASSERT(stream != nullptr);

	auto transformNodeToObjectResult = _implPtr->transformNodeToObject(xsl._implPtr, _variant_t(stream));
	_ET_XML_ASSERT(transformNodeToObjectResult == S_OK);

	if (transformNodeToObjectResult == E_INVALIDARG)
		_ET_XML_THROW(XmlException::InvalidArgument(), Detail::kInvalidArgument);
	else if (FAILED(transformNodeToObjectResult))
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotTransformNode);
}

/*************************************************************************************************/

XmlNode& XmlNode::operator=(const XmlNode& other)
{
	if (this != &other)
	{
		_implPtr = other._implPtr;
	}

	return *this;
}

XmlNode& XmlNode::operator=(XmlNode&& other)
{
	if (this != &other)
	{
		_implPtr = std::move(other._implPtr);
	}

	return *this;
}

XmlNode::operator bool() const
{
	return (_implPtr != nullptr);
}

bool XmlNode::operator!() const
{
	return (_implPtr == nullptr);
}

bool XmlNode::operator==(const XmlNode& other) const
{
	return _implPtr.IsEqualObject(other._implPtr);
}

bool XmlNode::operator!=(const XmlNode& other) const
{
	return !(operator==(other));
}

/*************************************************************************************************/

XmlNode::XmlNode()
{
}

} //namespace XML
} //namespace Et
