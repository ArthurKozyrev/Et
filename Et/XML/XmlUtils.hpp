
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlDef.hpp>
#include <Et\XML\XmlTypes.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

ET_XMLAPI void CloneXmlDocumentProperties(const XmlDocument& source, XmlDocument& destination);

ET_XMLAPI XmlDocument LoadXmlDocument(const void* buffer, size_t size) throw(...);
ET_XMLAPI XmlDocument LoadXmlDocument(const std::wstring& filename) throw(...);
ET_XMLAPI XmlDocument LoadXmlDocument(IStream* stream) throw(...);

} //namespace XML
} //namespace Et
