
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlTypes.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
namespace Detail {
	
_MXWriterPtr_t CreateMXWriterInstance();

void SerializeDOMDocument(const _MXWriterPtr_t& writer, const VARIANT& source, const VARIANT& destination);

} //namespace Detail
} //namespace XML
} //namespace Et
