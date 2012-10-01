
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlTypes.hpp>
#include <Et\XML\XmlParseError.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

class XmlException : public Exception<XmlException>
{
public:
	struct ET_XMLAPI InternalError;
	struct ET_XMLAPI InvalidArgument;
	struct ET_XMLAPI InvalidOperation;
	struct ET_XMLAPI CannotAccessFile;
	struct ET_XMLAPI DocumentNotLoaded;
	struct ET_XMLAPI DocumentNotSaved;
	
public:
	XmlException();
	XmlException(const char* message);
	XmlException(const XmlException& other);
	XmlException(XmlException&& other);
	~XmlException();

public:
	auto GetDefaultMessage() const -> const char* const override;

public:
	mutable XmlParseError parseError;

	friend const XmlException& operator<<(const XmlException& e, const XmlParseError& pe);
	friend const XmlException& operator<<(const XmlException& e, XmlParseError&& pe);
};

/*************************************************************************************************/

struct XmlException::InternalError : public XmlException { };
struct XmlException::InvalidArgument : public XmlException { };
struct XmlException::InvalidOperation : public XmlException { };
struct XmlException::CannotAccessFile : public XmlException { };
struct XmlException::DocumentNotLoaded : public XmlException { };
struct XmlException::DocumentNotSaved : public XmlException { };

///////////////////////////////////////////////////////////////////////////////////////////////////

inline const XmlException& operator<<(const XmlException& e, const XmlParseError& pe)
{
	e.parseError = pe;

	return e;
}

inline const XmlException& operator<<(const XmlException& e, XmlParseError&& pe)
{
	e.parseError = std::forward<XmlParseError>(pe);

	return e;
}

} //namespace XML
} //namespace Et
