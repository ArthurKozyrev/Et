
#include "SAXReader.hpp"
#include "Errors.hpp"

#include <Et\XML\XmlException.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
namespace Detail {

_SAXReaderPtr_t CreateSAXReaderInstance()
{
	_SAXReaderPtr_t result;

	auto CoCreateInstanceResult = CoCreateInstance(__uuidof(MSXML6::SAXXMLReader60), nullptr, CLSCTX_INPROC_SERVER,
		__uuidof(_SAXReaderPtr_t::Element_t), reinterpret_cast<void**>(&result));
	_ET_XML_ASSERT(CoCreateInstanceResult == S_OK);

	if (!result)
		_ET_XML_THROW(XmlException::InternalError(), kCannotCreateInstanceOfSAXReader);

	return result;
}

} //namespace Detail
} //namespace XML
} //namespace Et
