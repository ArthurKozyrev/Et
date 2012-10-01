
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlTypes.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
namespace Detail {

bool CheckNodeType(XmlNodeType type);
XmlNodeType EncodeNodeType(unsigned int value);
unsigned int DecodeNodeType(XmlNodeType type);

void GetNodeText(const XmlNode& node, std::wstring& output);
void RemoveNodeText(XmlNode& node);

} //namespace Detail
} //namespace XML
} //namespace Et
