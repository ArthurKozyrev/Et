
#include "MXWriter.hpp"
#include "SAXReader.hpp"
#include "Errors.hpp"

#include <Et\XML\XmlException.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

using Et::COM::ComPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
namespace Detail {

_MXWriterPtr_t CreateMXWriterInstance()
{
	_MXWriterPtr_t result;

	auto CoCreateInstanceResult = CoCreateInstance(__uuidof(MSXML6::MXXMLWriter60), nullptr, CLSCTX_INPROC_SERVER,
		__uuidof(_MXWriterPtr_t::Element_t), reinterpret_cast<void**>(&result));
	_ET_XML_ASSERT(CoCreateInstanceResult == S_OK);

	if (!result)
		_ET_XML_THROW(XmlException::InternalError(), kCannotCreateInstanceOfMXWriter);

	return result;
}

/*************************************************************************************************/

void SerializeDOMDocument(const _MXWriterPtr_t& writer, const VARIANT& source, const VARIANT& destination)
{
	_SAXReaderPtr_t readerPtr = CreateSAXReaderInstance();

	readerPtr->putContentHandler(ComPtr<MSXML6::ISAXContentHandler>(writer));
	readerPtr->putDTDHandler(ComPtr<MSXML6::ISAXDTDHandler>(writer));
	readerPtr->putErrorHandler(ComPtr<MSXML6::ISAXErrorHandler>(writer));
	readerPtr->putProperty(reinterpret_cast<USHORT*>(L"http://xml.org/sax/properties/declaration-handler"), _variant_t(writer));
	readerPtr->putProperty(reinterpret_cast<USHORT*>(L"http://xml.org/sax/properties/lexical-handler"), _variant_t(writer));

	if (FAILED(writer->put_output(destination)))
		_ET_XML_THROW(XmlException::InternalError(), kCannotSetSerializerOutput);

	auto parseResult = readerPtr->parse(source);
	_ET_XML_ASSERT(parseResult == S_OK);
	
	if (parseResult == E_INVALIDARG)
		_ET_XML_THROW(XmlException::InvalidArgument(), kInvalidArgument);
	else if (FAILED(parseResult))
		_ET_XML_THROW(XmlException::InternalError(), kCannotSerializeDocument);
}

} //namespace Detail
} //namespace XML
} //namespace Et
