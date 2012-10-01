
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlTypes.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
namespace Detail {

_DOMDocumentPtr_t CreateDOMDocumentInstance();
XmlParseError GetDocumentParseError(const _DOMDocumentPtr_t& document);

XmlDocumentState EncodeDocumentState(unsigned int value);

void LoadDOMDocument(const _DOMDocumentPtr_t& document, const VARIANT& source);
void SaveDOMDocument(const _DOMDocumentPtr_t& document, const VARIANT& destination);
void TransformDOMDocument(const _DOMDocumentPtr_t& document, const _DOMNodePtr_t& xsl, const VARIANT& destination);

std::wstring GetDOMDocumentPropertyValue(const _DOMDocumentPtr_t& document, const wchar_t* property_name);
void SetDOMDocumentPropertyValue(const _DOMDocumentPtr_t& document, const wchar_t* property_name, const _variant_t& property_value);

} //namespace Detail
} //namespace XML
} //namespace Et
