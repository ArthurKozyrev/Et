
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlDef.hpp>
#include <Et\XML\XmlInc.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

class ET_XMLAPI XmlNode;
class ET_XMLAPI XmlNodeList;
class ET_XMLAPI XmlElement;
class ET_XMLAPI XmlAttributeList;
class ET_XMLAPI XmlDocument;
class ET_XMLAPI XmlParseError;
class ET_XMLAPI XmlSerializer;
class ET_XMLAPI XmlException;

/*************************************************************************************************/

typedef Et::COM::ComPtr<MSXML6::IXMLDOMNode> _DOMNodePtr_t;
typedef Et::COM::ComPtr<MSXML6::IXMLDOMNodeList> _DOMNodeListPtr_t;
typedef Et::COM::ComPtr<MSXML6::IXMLDOMElement> _DOMElementPtr_t;
typedef Et::COM::ComPtr<MSXML6::IXMLDOMNamedNodeMap> _DOMAttributeListPtr_t;
typedef Et::COM::ComPtr<MSXML6::IXMLDOMDocument3> _DOMDocumentPtr_t;
typedef Et::COM::ComPtr<MSXML6::IXMLDOMParseError2> _DOMParseErrorPtr_t;
typedef Et::COM::ComPtr<MSXML6::ISAXXMLReader> _SAXReaderPtr_t;
typedef Et::COM::ComPtr<MSXML6::IMXWriter> _MXWriterPtr_t;

namespace Detail {

typedef std::unique_ptr<BSTR, Et::COM::BSTRDeleter> bstr_ptr_t;

}

/*************************************************************************************************/

template class ET_XMLAPI Et::COM::ComPtr<MSXML6::IXMLDOMNode>;
template class ET_XMLAPI Et::COM::ComPtr<MSXML6::IXMLDOMNodeList>;
template class ET_XMLAPI Et::COM::ComPtr<MSXML6::IXMLDOMElement>;
template class ET_XMLAPI Et::COM::ComPtr<MSXML6::IXMLDOMNamedNodeMap>;
template class ET_XMLAPI Et::COM::ComPtr<MSXML6::IXMLDOMDocument3>;
template class ET_XMLAPI Et::COM::ComPtr<MSXML6::IXMLDOMParseError2>;
template class ET_XMLAPI Et::COM::ComPtr<MSXML6::ISAXXMLReader>;
template class ET_XMLAPI Et::COM::ComPtr<MSXML6::IMXWriter>;
template class ET_XMLAPI Et::COM::ComPtr<Et::IExceptionInfo>;

template class ET_XMLAPI Et::Detail::ExceptionInfo<XmlException, Et::ExceptionInfoType::Message>;
template class ET_XMLAPI Et::Detail::ExceptionInfo<XmlException, Et::ExceptionInfoType::ErrorCode>;
template class ET_XMLAPI Et::Detail::ExceptionInfo<XmlException, Et::ExceptionInfoType::Location>;
template class ET_XMLAPI Et::Detail::ExceptionInfo<XmlException, Et::ExceptionInfoType::File>;
template class ET_XMLAPI Et::Detail::ExceptionInfo<XmlException, Et::ExceptionInfoType::Line>;

///////////////////////////////////////////////////////////////////////////////////////////////////

enum class XmlNodeType : unsigned int
{
	None,
	Element               = 0x0001,
	Attribute             = 0x0002,
	Text                  = 0x0004,
	CDATA                 = 0x0008,
	EntityReference       = 0x0010,
	Entity                = 0x0020,
	ProcessingInstruction = 0x0040,
	Comment               = 0x0080,
	Document              = 0x0100,
	DocumentType          = 0x0200,
	DocumentFragment      = 0x0400,
	Notation              = 0x0800,
};

enum class XmlDocumentProperty : unsigned int
{
	AllowDocumentFunction,
	AllowXsltScript,
	ForcedResync,
	MaxElementDepth,
	MaxXmlSize,
	MultipleErrorMessages,
	NewParser,
	NormalizeAttributeValues,
	PopulateElementDefaultValues,
	ProhibitDTD,
	ResolveExternals,
	SelectionLanguage,
	SelectionNamespaces,
	ServerHttpRequest,
	UseInlineSchema,
	ValidateOnParse,
	
	AsyncLoading = 100,
	PreserveWhitespace,
};

enum class XmlDocumentState : unsigned int
{
	None,
	Loading,
	Parsing,
	Building,
	Ready,
};

enum class XmlSerializerProperty : unsigned int
{
	BOM,
	Declaration,
	Version,
	Encoding,
	Standalone,
	Indentation,
	Escaping,
};

/*************************************************************************************************/

ET_XMLAPI inline XmlNodeType operator~(const XmlNodeType& type)
{
	return XmlNodeType(static_cast<XmlNodeType>(~(unsigned int)type));
}

ET_XMLAPI inline XmlNodeType operator&(const XmlNodeType& left, const XmlNodeType& right)
{
	return XmlNodeType(static_cast<XmlNodeType>((unsigned int)left & (unsigned int)right));
}

ET_XMLAPI inline XmlNodeType operator|(const XmlNodeType& left, const XmlNodeType& right)
{
	return XmlNodeType(static_cast<XmlNodeType>((unsigned int)left | (unsigned int)right));
}

ET_XMLAPI inline XmlNodeType operator^(const XmlNodeType& left, const XmlNodeType& right)
{
	return XmlNodeType(static_cast<XmlNodeType>((unsigned int)left ^ (unsigned int)right));
}

ET_XMLAPI inline XmlNodeType& operator&=(XmlNodeType& left, const XmlNodeType& right)
{
	return reinterpret_cast<XmlNodeType&>((unsigned int&)left &= (unsigned int)right);
}

ET_XMLAPI inline XmlNodeType& operator|=(XmlNodeType& left, const XmlNodeType& right)
{
	return reinterpret_cast<XmlNodeType&>((unsigned int&)left |= (unsigned int)right);
}

ET_XMLAPI inline XmlNodeType& operator^=(XmlNodeType& left, const XmlNodeType& right)
{
	return reinterpret_cast<XmlNodeType&>((unsigned int&)left ^= (unsigned int)right);
}

} //namespace XML
} //namespace Et
