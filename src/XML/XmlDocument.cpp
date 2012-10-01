
#include <Et\XML\XmlDocument.hpp>
#include <Et\XML\XmlNode.hpp>
#include <Et\XML\XmlNodeList.hpp>
#include <Et\XML\XmlElement.hpp>
#include <Et\XML\XmlAttributeList.hpp>
#include <Et\XML\XmlParseError.hpp>
#include <Et\XML\XmlException.hpp>
#include <Et\XML\XmlUtils.hpp>
#include "Detail\DOMDocument.hpp"
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
	
XmlDocument::XmlDocument() throw(...) : XmlNode(Detail::CreateDOMDocumentInstance())
{
	SetDocumentProperty(XmlDocumentProperty::AsyncLoading, L"false");
	SetDocumentProperty(XmlDocumentProperty::MultipleErrorMessages, L"true");
}

XmlDocument::XmlDocument(const _DOMDocumentPtr_t& ptr) throw(...) : XmlNode(ptr)
{
	if (!_implPtr)
		_ET_XML_THROW(XmlException::InvalidOperation(), Detail::kInvalidArgument);
}

XmlDocument::XmlDocument(const XmlDocument& other) : XmlNode(other._implPtr)
{
}

XmlDocument::XmlDocument(XmlDocument&& other) : XmlNode(std::move(other._implPtr))
{
}

XmlDocument::~XmlDocument()
{
}

/*************************************************************************************************/

void XmlDocument::AbortLoading()
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);

	documentPtr->abort();
}



XmlDocument XmlDocument::Clone() const throw(...)
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	XmlDocument clonedDocument;
	
	CloneXmlDocumentProperties(*this, clonedDocument);
	try
	{
		Detail::SaveDOMDocument(documentPtr, _variant_t(clonedDocument._implPtr));
	}
	catch(XmlException& xe)
	{
		_ET_XML_THROW2(XmlException::InternalError(), Detail::kCannotCloneDocument, xe.parseError);
	}

	return clonedDocument;
}



XmlNode XmlDocument::CreateNode(XmlNodeType type, const std::wstring& name, const std::wstring& namespace_uri) const throw(...)
{
	if (!Detail::CheckNodeType(type))
		_ET_XML_THROW(XmlException::InvalidArgument(), Detail::kInvalidArgument);

	const _DOMDocumentPtr_t documentPtr(_implPtr);
	const _variant_t nodeType(Detail::DecodeNodeType(type));
	const _bstr_t nodeName(name.c_str()), nodeNamespace(namespace_uri.c_str());
	_DOMNodePtr_t nodePtr;

	auto createNodeResult = documentPtr->createNode(nodeType, nodeName, nodeNamespace, &nodePtr);
	_ET_XML_ASSERT(createNodeResult != E_FAIL);

	return XmlNode(std::move(nodePtr));
}

XmlElement XmlDocument::CreateElement(const std::wstring& name, const std::wstring& namespace_uri) const
{
	return CreateNode(XmlNodeType::Element, name, namespace_uri);
}

XmlNode XmlDocument::CreateAttribute(const std::wstring& name, const std::wstring& value, const std::wstring& namespace_uri) const
{
	XmlNode attributeNode = CreateNode(XmlNodeType::Attribute, name, namespace_uri);

	if (attributeNode)
		attributeNode.SetValue(value);

	return attributeNode;
}

XmlNode XmlDocument::CreateTextNode(const std::wstring& text) const
{
	XmlNode textNode = CreateNode(XmlNodeType::Text, L"", L"");

	if (textNode)
		textNode.SetValue(text);

	return textNode;
}

XmlNode XmlDocument::CreateComment(const std::wstring& text) const
{
	XmlNode commentNode = CreateNode(XmlNodeType::Comment, L"", L"");

	if (commentNode)
		commentNode.SetValue(text);

	return commentNode;
}



std::wstring XmlDocument::GetDocumentProperty(XmlDocumentProperty property) const
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	std::wstring result;

	switch (property)
	{
		case XmlDocumentProperty::AllowDocumentFunction:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"AllowDocumentFunction");
			break;

		case XmlDocumentProperty::AllowXsltScript:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"AllowXsltScript");
			break;

		case XmlDocumentProperty::ForcedResync:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"ForcedResync");
			break;

		case XmlDocumentProperty::MaxElementDepth:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"MaxElementDepth");
			break;

		case XmlDocumentProperty::MaxXmlSize:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"MaxXMLSize");
			break;

		case XmlDocumentProperty::MultipleErrorMessages:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"MultipleErrorMessages");
			break;

		case XmlDocumentProperty::NewParser:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"NewParser");
			break;

		case XmlDocumentProperty::NormalizeAttributeValues:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"NormalizeAttributeValues");
			break;

		case XmlDocumentProperty::PopulateElementDefaultValues:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"PopulateElementDefaultValues");
			break;

		case XmlDocumentProperty::ProhibitDTD:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"ProhibitDTD");
			break;

		case XmlDocumentProperty::ResolveExternals:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"ResolveExternals");
			break;

		case XmlDocumentProperty::SelectionLanguage:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"SelectionLanguage");
			break;

		case XmlDocumentProperty::SelectionNamespaces:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"SelectionNamespaces");
			break;

		case XmlDocumentProperty::ServerHttpRequest:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"ServerHTTPRequest");
			break;

		case XmlDocumentProperty::UseInlineSchema:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"UseInlineSchema");
			break;

		case XmlDocumentProperty::ValidateOnParse:
			result = Detail::GetDOMDocumentPropertyValue(documentPtr, L"ValidateOnParse");
			break;

		case XmlDocumentProperty::AsyncLoading:
			{
				VARIANT_BOOL async = VARIANT_FALSE;

				documentPtr->get_async(&async);
				result = Detail::VariantBoolToStr(async);
			}
			break;

		case XmlDocumentProperty::PreserveWhitespace:
			{
				VARIANT_BOOL preserveWhiteSpace = VARIANT_FALSE;

				documentPtr->get_preserveWhiteSpace(&preserveWhiteSpace);
				result = Detail::VariantBoolToStr(preserveWhiteSpace);
			}
			break;
	}

	return result;
}

XmlDocumentState XmlDocument::GetDocumentState() const
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	long state = static_cast<long>(XmlDocumentState::None);

	documentPtr->get_readyState(&state);
	if (state == 0)
		_ET_XML_THROW(XmlException::InternalError(), Detail::kInvalidDocumentState);

	return Detail::EncodeDocumentState(state);
}

std::wstring XmlDocument::GetDocumentURL() const
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	BSTR documentURL = nullptr;
	const bstr_ptr_t documentURLPtr(&documentURL);
	std::wstring result;

	if (documentPtr->get_url(&documentURL) == S_OK)
		result = documentURL;

	return result;
}

XmlNode XmlDocument::GetDocumentTypeDefinition() const
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	ComPtr<MSXML6::IXMLDOMDocumentType> documentTypePtr;

	documentPtr->get_doctype(&documentTypePtr);

	return XmlNode(documentTypePtr);
}

XmlAttributeList XmlDocument::GetDocumentTypeEntities() const
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	ComPtr<MSXML6::IXMLDOMDocumentType> documentTypePtr;
	_DOMAttributeListPtr_t entitiesListPtr;

	documentPtr->get_doctype(&documentTypePtr);

	if (documentTypePtr)
		documentTypePtr->get_entities(&entitiesListPtr);
	
	return XmlAttributeList(std::move(entitiesListPtr));
}

std::wstring XmlDocument::GetDocumentEncoding() const
{
	const XmlNode processingInstruction = GetChildNode(XmlNodeType::ProcessingInstruction, L"xml");
	std::wstring result;

	if (processingInstruction)
	{
		const std::wstring& encodingAttributeName = L"encoding";
		const XmlAttributeList attributeList = processingInstruction.GetAttributeList();

		result = attributeList.GetAttributeValue(encodingAttributeName);
	}

	return result;
}

XmlElement XmlDocument::GetDocumentElement() const
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	_DOMElementPtr_t documentElementPtr;

	documentPtr->get_documentElement(&documentElementPtr);
	
	return XmlElement(documentElementPtr);
}

XmlNodeList XmlDocument::GetElementsByTagName(const std::wstring& name) const
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	const _bstr_t elementName(name.c_str());
	_DOMNodeListPtr_t elementListPtr;

	documentPtr->getElementsByTagName(elementName, &elementListPtr);
	
	return XmlNodeList(std::move(elementListPtr));
}

XmlParseError XmlDocument::GetParseError() const
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);

	return Detail::GetDocumentParseError(documentPtr);
}



bool XmlDocument::IsHasFeature(const std::wstring& feature, const std::wstring& version) const
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	ComPtr<MSXML6::IXMLDOMImplementation> xmlDomImplementationPtr;
	VARIANT_BOOL hasFeature = VARIANT_FALSE;

	if (documentPtr->get_implementation(&xmlDomImplementationPtr) == S_OK)
	{
		const _bstr_t featureName(feature.c_str()), featureVersion(version.c_str());

		xmlDomImplementationPtr->hasFeature(featureName, featureVersion, &hasFeature);
	}
	
	return (hasFeature == VARIANT_TRUE);
}

bool XmlDocument::IsReady() const
{
	return (GetDocumentState() == XmlDocumentState::Ready);
}



void XmlDocument::Load(const void* buffer, size_t size) throw(...)
{
	_ET_XML_ASSERT(buffer && size);
	if (!buffer || !size)
		_ET_XML_THROW(XmlException::InvalidArgument(), Detail::kInvalidArgument);

	SAFEARRAY sa = {0};
	VARIANT v = {0};
	
	sa.cDims = 1;
	sa.fFeatures = FADF_STATIC;
	sa.cbElements = sizeof(BYTE);
	sa.pvData = const_cast<PVOID>(buffer);
	sa.rgsabound->cElements = static_cast<ULONG>(size);

	v.vt = VT_ARRAY | VT_UI1;
	v.parray = &sa;

	Detail::LoadDOMDocument(_implPtr, v);
}

void XmlDocument::Load(const std::wstring& filename) throw(...)
{
	const DWORD fileMode = STGM_READ | STGM_SHARE_DENY_WRITE;
	ComPtr<IStream> fileStreamPtr;

	SHCreateStreamOnFileEx(filename.c_str(), fileMode, 0, FALSE, nullptr, &fileStreamPtr);

	if (!fileStreamPtr)
		_ET_XML_THROW(XmlException::CannotAccessFile(), Detail::kCannotAccessFile);

	Load(fileStreamPtr);
}

void XmlDocument::Load(IStream* stream) throw(...)
{
	_ET_XML_ASSERT(stream != nullptr);

	Detail::LoadDOMDocument(_implPtr, _variant_t(stream));
}



void XmlDocument::Save(const std::wstring& filename) const throw(...)
{
	Detail::SaveDOMDocument(_implPtr, _variant_t(filename.c_str()));
}

void XmlDocument::Save(IStream* stream) const throw(...)
{
	_ET_XML_ASSERT(stream != nullptr);

	Detail::SaveDOMDocument(_implPtr, _variant_t(stream));
}



void XmlDocument::SetDocumentProperty(XmlDocumentProperty property, const std::wstring& value)
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);

	switch (property)
	{
		case XmlDocumentProperty::AllowDocumentFunction:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"AllowDocumentFunction", Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::AllowXsltScript:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"AllowXsltScript", Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::ForcedResync:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"ForcedResync", Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::MaxElementDepth:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"MaxElementDepth", _wtoi(value.c_str()));
			break;

		case XmlDocumentProperty::MaxXmlSize:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"MaxXMLSize", _wtoi(value.c_str()));
			break;

		case XmlDocumentProperty::MultipleErrorMessages:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"MultipleErrorMessages", Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::NewParser:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"NewParser", Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::NormalizeAttributeValues:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"NormalizeAttributeValues", Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::PopulateElementDefaultValues:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"PopulateElementDefaultValues", Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::ProhibitDTD:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"ProhibitDTD", Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::ResolveExternals:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"ResolveExternals", Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::SelectionLanguage:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"SelectionLanguage", value.c_str());
			break;

		case XmlDocumentProperty::SelectionNamespaces:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"SelectionNamespaces", value.c_str());
			break;

		case XmlDocumentProperty::ServerHttpRequest:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"ServerHTTPRequest", Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::UseInlineSchema:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"UseInlineSchema", Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::ValidateOnParse:
			Detail::SetDOMDocumentPropertyValue(documentPtr, L"ValidateOnParse", Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::AsyncLoading:
			documentPtr->put_async(Detail::StrToVariantBool(value));
			break;

		case XmlDocumentProperty::PreserveWhitespace:
			documentPtr->put_preserveWhiteSpace(Detail::StrToVariantBool(value));
			break;
	}
}

bool XmlDocument::SetDocumentEncoding(const std::wstring& encoding)
{
	const XmlNode processingInstruction = GetChildNode(XmlNodeType::ProcessingInstruction, L"xml");
	bool result = false;

	if (processingInstruction)
	{
		const std::wstring encodingAttributeName = L"encoding";
		XmlAttributeList attributeList = processingInstruction.GetAttributeList();
		XmlNode encodingAttribute = attributeList.GetAttribute(encodingAttributeName);

		if (encoding.empty())
		{
			const std::wstring standaloneAttributeName = L"standalone";
			XmlNode standaloneAttribute = attributeList.GetAttribute(standaloneAttributeName);

			if (encodingAttribute)
			{
				if (!standaloneAttribute)
					result = attributeList.RemoveAttribute(encodingAttributeName);
			}
			else
				result = true;
		}
		else
		{
			if (!encodingAttribute)
			{
				encodingAttribute = CreateAttribute(encodingAttributeName, encoding);

				if (encodingAttribute)
					result = attributeList.InsertAttribute(encodingAttribute);
			}
			else
				result = encodingAttribute.SetValue(encoding);
		}
	}
	
	return result;
}

bool XmlDocument::SetDocumentElement(const XmlElement& new_root)
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	const _DOMElementPtr_t elementPtr(new_root._implPtr);
	bool result = false;

	if (documentPtr->putref_documentElement(elementPtr) == S_OK)
		result = true;

	return result;
}



XmlDocument XmlDocument::Transform(const XmlNode& xsl) const throw(...)
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	XmlDocument transformedDocument;
	
	Detail::TransformDOMDocument(documentPtr, xsl._implPtr, _variant_t(transformedDocument._implPtr));

	return transformedDocument;
}



XmlParseError XmlDocument::Validate() const
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	ComPtr<MSXML6::IXMLDOMParseError> parseErrorPtr;

	auto validateResult = documentPtr->validate(&parseErrorPtr);
	_ET_XML_ASSERT(validateResult >= S_OK);

	if (FAILED(validateResult))
		_ET_XML_THROW(XmlException::InvalidOperation(), Detail::kCannotValidateDocument);

	return XmlParseError(parseErrorPtr);
}

XmlParseError XmlDocument::ValidateNode(const XmlNode& node) const
{
	const _DOMDocumentPtr_t documentPtr(_implPtr);
	ComPtr<MSXML6::IXMLDOMParseError> parseErrorPtr;

	auto validateNodeResult = documentPtr->validateNode(node._implPtr, &parseErrorPtr);
	_ET_XML_ASSERT(validateNodeResult >= S_OK);

	if (FAILED(validateNodeResult))
		_ET_XML_THROW(XmlException::InvalidOperation(), Detail::kCannotValidateNode);

	return XmlParseError(parseErrorPtr);
}

/*************************************************************************************************/

XmlDocument& XmlDocument::operator=(const XmlDocument& other)
{
	if (this != &other)
	{
		XmlNode::operator=(other);
	}

	return *this;
}

XmlDocument& XmlDocument::operator=(XmlDocument&& other)
{
	if (this != &other)
	{
		XmlNode::operator=(std::move(other));
	}

	return *this;
}

} //namespace XML
} //namespace Et
