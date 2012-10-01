
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <Et\XML\XmlTypes.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

class XmlSerializer sealed
{
public:
	XmlSerializer() throw(...);
	XmlSerializer(const XmlSerializer& other);
	XmlSerializer(XmlSerializer&& other);
	virtual ~XmlSerializer();
	
public:
	std::wstring GetSerializerProperty(XmlSerializerProperty property) const;
	
	void SetSerializerProperty(XmlSerializerProperty property, const std::wstring& value);
	
	void SerializeToString(const XmlDocument& document, std::wstring& str) throw(...);
	void SerializeToFile(const XmlDocument& document, const std::wstring& filename) throw(...);
	void SerializeToStream(const XmlDocument& document, IStream* stream) throw(...);
	
public:
	XmlSerializer& operator=(const XmlSerializer& other);
	XmlSerializer& operator=(XmlSerializer&& other);
	bool operator==(const XmlSerializer& other) const;
	bool operator!=(const XmlSerializer& other) const;
	
protected:
	_MXWriterPtr_t _implPtr;
};

} //namespace XML
} //namespace Et
