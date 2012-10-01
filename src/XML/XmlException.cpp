
#include <Et\XML\XmlException.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

static const auto kDefaultMessage = "XML: unknown exception";

///////////////////////////////////////////////////////////////////////////////////////////////////

XmlException::XmlException() : Exception(kDefaultMessage)
{
}

XmlException::XmlException(const char* message) : Exception(message)
{
}

XmlException::XmlException(const XmlException& other) : Exception(other), parseError(other.parseError)
{
}

XmlException::XmlException(XmlException&& other) : Exception(std::forward<Exception>(other)), parseError(std::move(other.parseError))
{
}

XmlException::~XmlException()
{
}

/*************************************************************************************************/

auto XmlException::GetDefaultMessage() const -> const char* const
{
	return kDefaultMessage;
}

} //namespace XML
} //namespace Et
