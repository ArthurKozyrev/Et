
#include <Et\XML\XmlSerializer.hpp>
#include <Et\XML\XmlDocument.hpp>
#include <Et\XML\XmlException.hpp>
#include "Detail\MXWriter.hpp"
#include "Detail\Errors.hpp"
#include "Detail\Common.hpp"

#include <shlwapi.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

using Et::COM::ComPtr;
using Et::XML::Detail::bstr_ptr_t;

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

XmlSerializer::XmlSerializer() throw(...) : _implPtr(Detail::CreateMXWriterInstance())
{
	SetSerializerProperty(XmlSerializerProperty::Indentation, L"true");
}

XmlSerializer::XmlSerializer(const XmlSerializer& other) : _implPtr(other._implPtr)
{
}

XmlSerializer::XmlSerializer(XmlSerializer&& other) : _implPtr(std::move(other._implPtr))
{
}

XmlSerializer::~XmlSerializer()
{
}

/*************************************************************************************************/

std::wstring XmlSerializer::GetSerializerProperty(XmlSerializerProperty property) const throw(...)
{
	std::wstring result;

	switch (property)
	{
		case XmlSerializerProperty::BOM:
			{
				VARIANT_BOOL byteOrderMark = VARIANT_FALSE;

				if (FAILED(_implPtr->get_byteOrderMark(&byteOrderMark)))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotGetSerializerProperty);

				result = Detail::VariantBoolToStr(byteOrderMark);
			}
			break;

		case XmlSerializerProperty::Declaration:
			{
				VARIANT_BOOL omitXmlDeclaration = VARIANT_FALSE;

				if (FAILED(_implPtr->get_omitXMLDeclaration(&omitXmlDeclaration)))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotGetSerializerProperty);

				omitXmlDeclaration = ~omitXmlDeclaration;

				result = Detail::VariantBoolToStr(omitXmlDeclaration);
			}
			break;

		case XmlSerializerProperty::Version:
			{
				BSTR version = nullptr;
				const bstr_ptr_t versionPtr(&version);

				if (FAILED(_implPtr->get_version(&version)))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotGetSerializerProperty);

				result = version;
			}
			break;

		case XmlSerializerProperty::Encoding:
			{
				BSTR encoding = nullptr;
				const bstr_ptr_t encodingPtr(&encoding);

				if (FAILED(_implPtr->get_encoding(&encoding)))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotGetSerializerProperty);
				
				result = encoding;
			}
			break;

		case XmlSerializerProperty::Standalone:
			{
				VARIANT_BOOL standalone = VARIANT_FALSE;

				if (FAILED(_implPtr->get_standalone(&standalone)))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotGetSerializerProperty);

				result = Detail::VariantBoolToStr(standalone);
			}
			break;

		case XmlSerializerProperty::Indentation:
			{
				VARIANT_BOOL indentation = VARIANT_FALSE;

				if (FAILED(_implPtr->get_indent(&indentation)))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotGetSerializerProperty);

				result = Detail::VariantBoolToStr(indentation);
			}
			break;

		case XmlSerializerProperty::Escaping:
			{
				VARIANT_BOOL disableOutputEscaping = VARIANT_FALSE;

				if (FAILED(_implPtr->get_disableOutputEscaping(&disableOutputEscaping)))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotGetSerializerProperty);

				disableOutputEscaping = ~disableOutputEscaping;

				result = Detail::VariantBoolToStr(disableOutputEscaping);
			}
			break;
	}

	return result;
}



void XmlSerializer::SetSerializerProperty(XmlSerializerProperty property, const std::wstring& value)
{
	switch (property)
	{
		case XmlSerializerProperty::BOM:
			{
				if (FAILED(_implPtr->put_byteOrderMark(Detail::StrToVariantBool(value))))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotSetSerializerProperty);
			}
			break;

		case XmlSerializerProperty::Declaration:
			{
				if (FAILED(_implPtr->put_omitXMLDeclaration(~Detail::StrToVariantBool(value))))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotSetSerializerProperty);
			}
			break;

		case XmlSerializerProperty::Version:
			{
				const _bstr_t version(value.c_str());

				if (FAILED(_implPtr->put_version(version)))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotSetSerializerProperty);
			}
			break;

		case XmlSerializerProperty::Encoding:
			{
				// There is a bug in MXXMLWriter
				const _bstr_t encoding = (_wcsicmp(value.c_str(), L"UTF-16") != 0) ? value.c_str() : L"";

				if (FAILED(_implPtr->put_encoding(encoding)))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotSetSerializerProperty);
			}
			break;

		case XmlSerializerProperty::Standalone:
			{
				if (FAILED(_implPtr->put_standalone(Detail::StrToVariantBool(value))))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotSetSerializerProperty);
			}
			break;

		case XmlSerializerProperty::Indentation:
			{
				if (FAILED(_implPtr->put_indent(Detail::StrToVariantBool(value))))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotSetSerializerProperty);
			}
			break;

		case XmlSerializerProperty::Escaping:
			{
				if (FAILED(_implPtr->put_disableOutputEscaping(~Detail::StrToVariantBool(value))))
					_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotSetSerializerProperty);
			}
			break;
	}
}



void XmlSerializer::SerializeToString(const XmlDocument& document, std::wstring& str) throw(...)
{
	Detail::SerializeDOMDocument(_implPtr, _variant_t(document._implPtr), _variant_t());

	_variant_t output;

	if (FAILED(_implPtr->get_output(&output)))
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotGetSerializerOutput);

	switch (output.vt)
	{
		case VT_BSTR:
			str = output.bstrVal;
			break;
	}

	if (FAILED(_implPtr->put_output(_variant_t())))
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotSetSerializerOutput);
}

void XmlSerializer::SerializeToFile(const XmlDocument& document, const std::wstring& filename) throw(...)
{
	const DWORD fileMode = STGM_CREATE | STGM_WRITE | STGM_SHARE_EXCLUSIVE;
	ComPtr<IStream> fileStreamPtr;

	SHCreateStreamOnFileEx(filename.c_str(), fileMode, 0, TRUE, nullptr, &fileStreamPtr);

	if (!fileStreamPtr)
		_ET_XML_THROW(XmlException::CannotAccessFile(), Detail::kCannotAccessFile);

	SerializeToStream(document, fileStreamPtr);
}

void XmlSerializer::SerializeToStream(const XmlDocument& document, IStream* stream) throw(...)
{
	_ET_XML_ASSERT(stream != nullptr);

	Detail::SerializeDOMDocument(_implPtr, _variant_t(document._implPtr), _variant_t(stream));
	
	if (FAILED(_implPtr->put_output(_variant_t())))
		_ET_XML_THROW(XmlException::InternalError(), Detail::kCannotSetSerializerOutput);
}

/*************************************************************************************************/

XmlSerializer& XmlSerializer::operator=(const XmlSerializer& other)
{
	if (this != &other)
	{
		_implPtr = other._implPtr;
	}

	return *this;
}

XmlSerializer& XmlSerializer::operator=(XmlSerializer&& other)
{
	if (this != &other)
	{
		_implPtr = std::move(other._implPtr);
	}

	return *this;
}

bool XmlSerializer::operator==(const XmlSerializer& other) const
{
	return _implPtr.IsEqualObject(other._implPtr);
}

bool XmlSerializer::operator!=(const XmlSerializer& other) const
{
	return !(operator==(other));
}

} //namespace XML
} //namespace Et
