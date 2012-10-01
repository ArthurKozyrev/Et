
#include "DOMDocument.hpp"
#include "SAXReader.hpp"
#include "Errors.hpp"
#include "Common.hpp"

#include <Et\XML\XmlException.hpp>
#include <Et\XML\XmlParseError.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

using Et::COM::ComPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
namespace Detail {
	
_DOMDocumentPtr_t CreateDOMDocumentInstance()
{
	_DOMDocumentPtr_t result;
	
	auto CoCreateInstanceResult = CoCreateInstance(__uuidof(MSXML6::DOMDocument60), nullptr, CLSCTX_INPROC_SERVER,
		__uuidof(_DOMDocumentPtr_t::Element_t), reinterpret_cast<void**>(&result));
	_ET_XML_ASSERT(CoCreateInstanceResult == S_OK);
	
	if (!result)
		_ET_XML_THROW(XmlException::InternalError(), kCannotCreateInstanceOfDOMDocument);

	return result;
}

XmlParseError GetDocumentParseError(const _DOMDocumentPtr_t& document)
{
	ComPtr<MSXML6::IXMLDOMParseError> parseErrorPtr;
	
	document->get_parseError(&parseErrorPtr);
	
	return XmlParseError(std::move(parseErrorPtr));
}

/*************************************************************************************************/

XmlDocumentState EncodeDocumentState(unsigned int value)
{
	return static_cast<XmlDocumentState>(value);
}

/*************************************************************************************************/

void LoadDOMDocument(const _DOMDocumentPtr_t& document, const VARIANT& source)
{
	VARIANT_BOOL loadSuccess = VARIANT_FALSE;

	auto loadResult = document->load(source, &loadSuccess);
	_ET_XML_ASSERT(loadResult == S_OK);

	if (loadResult == E_INVALIDARG)
		_ET_XML_THROW(XmlException::InvalidArgument(), kInvalidArgument);

	if (!loadSuccess)
		_ET_XML_THROW2(XmlException::DocumentNotLoaded(), kCannotLoadDocument, GetDocumentParseError(document));
}

void SaveDOMDocument(const _DOMDocumentPtr_t& document, const VARIANT& destination)
{
	auto saveResult = document->save(destination);
	_ET_XML_ASSERT(saveResult == S_OK);

	if (saveResult == 0x80070020)
		_ET_XML_THROW(XmlException::CannotAccessFile(), kCannotAccessFile);
	else if(saveResult == E_INVALIDARG)
		_ET_XML_THROW(XmlException::InvalidArgument(), kInvalidArgument);
	else if (FAILED(saveResult))
		_ET_XML_THROW2(XmlException::DocumentNotSaved(), kCannotSaveDocument, GetDocumentParseError(document));
}

void TransformDOMDocument(const _DOMDocumentPtr_t& document, const _DOMNodePtr_t& xsl, const VARIANT& destination)
{
	auto transformNodeToObjectResult = document->transformNodeToObject(xsl, destination);
	_ET_XML_ASSERT(transformNodeToObjectResult == S_OK);

	if (transformNodeToObjectResult == E_INVALIDARG)
		_ET_XML_THROW(XmlException::InvalidArgument(), Detail::kInvalidArgument);
	else if (FAILED(transformNodeToObjectResult))
		_ET_XML_THROW2(XmlException::InternalError(), Detail::kCannotTransformDocument, GetDocumentParseError(document));
}

/*************************************************************************************************/

std::wstring GetDOMDocumentPropertyValue(const _DOMDocumentPtr_t& document, const wchar_t* property_name)
{
	const _bstr_t propertyName(property_name);
	_variant_t propertyValue;
	std::wstring result;

	auto getPropertyResult = document->getProperty(propertyName, &propertyValue);
	_ET_XML_ASSERT(getPropertyResult == S_OK);

	if (FAILED(getPropertyResult))
		_ET_XML_THROW(XmlException::InvalidArgument(), Detail::kInvalidArgument);

	switch (propertyValue.vt)
	{
		case VT_BOOL:
			result = VariantBoolToStr(propertyValue.boolVal);
			break;

		case VT_I4:
			{
				WCHAR buf[16] = {0};

				_itow_s(propertyValue.lVal, buf, 10);
				result = buf;
			}
			break;

		case VT_BSTR:
			result = propertyValue.bstrVal;
			break;

		default:
			_ET_XML_ASSERT(false);
	}

	return result;
}

void SetDOMDocumentPropertyValue(const _DOMDocumentPtr_t& document, const wchar_t* property_name, const _variant_t& property_value)
{
	const _bstr_t propertyName(property_name);

	auto setPropertyResult = document->setProperty(propertyName, property_value);
	_ET_XML_ASSERT(setPropertyResult == S_OK);

	if (FAILED(setPropertyResult))
		_ET_XML_THROW(XmlException::InvalidArgument(), Detail::kInvalidArgument);
}

} //namespace Detail
} //namespace XML
} //namespace Et
