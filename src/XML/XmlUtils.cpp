
#include <Et\XML\XmlUtils.hpp>
#include <Et\XML\XmlDocument.hpp>
#include <Et\XML\XmlSerializer.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

void CloneXmlDocumentProperties(const XmlDocument& source, XmlDocument& destination)
{
	destination.SetDocumentProperty(XmlDocumentProperty::AllowDocumentFunction, source.GetDocumentProperty(XmlDocumentProperty::AllowDocumentFunction));
	destination.SetDocumentProperty(XmlDocumentProperty::AllowXsltScript, source.GetDocumentProperty(XmlDocumentProperty::AllowXsltScript));
	destination.SetDocumentProperty(XmlDocumentProperty::ForcedResync, source.GetDocumentProperty(XmlDocumentProperty::ForcedResync));
	destination.SetDocumentProperty(XmlDocumentProperty::MaxElementDepth, source.GetDocumentProperty(XmlDocumentProperty::MaxElementDepth));
	destination.SetDocumentProperty(XmlDocumentProperty::MaxXmlSize, source.GetDocumentProperty(XmlDocumentProperty::MaxXmlSize));
	destination.SetDocumentProperty(XmlDocumentProperty::MultipleErrorMessages, source.GetDocumentProperty(XmlDocumentProperty::MultipleErrorMessages));
	destination.SetDocumentProperty(XmlDocumentProperty::NewParser, source.GetDocumentProperty(XmlDocumentProperty::NewParser));
	destination.SetDocumentProperty(XmlDocumentProperty::NormalizeAttributeValues, source.GetDocumentProperty(XmlDocumentProperty::NormalizeAttributeValues));
	destination.SetDocumentProperty(XmlDocumentProperty::PopulateElementDefaultValues, source.GetDocumentProperty(XmlDocumentProperty::PopulateElementDefaultValues));
	destination.SetDocumentProperty(XmlDocumentProperty::ProhibitDTD, source.GetDocumentProperty(XmlDocumentProperty::ProhibitDTD));
	destination.SetDocumentProperty(XmlDocumentProperty::ResolveExternals, source.GetDocumentProperty(XmlDocumentProperty::ResolveExternals));
	destination.SetDocumentProperty(XmlDocumentProperty::SelectionLanguage, source.GetDocumentProperty(XmlDocumentProperty::SelectionLanguage));
	destination.SetDocumentProperty(XmlDocumentProperty::SelectionNamespaces, source.GetDocumentProperty(XmlDocumentProperty::SelectionNamespaces));
	destination.SetDocumentProperty(XmlDocumentProperty::ServerHttpRequest, source.GetDocumentProperty(XmlDocumentProperty::ServerHttpRequest));
	destination.SetDocumentProperty(XmlDocumentProperty::UseInlineSchema, source.GetDocumentProperty(XmlDocumentProperty::UseInlineSchema));
	destination.SetDocumentProperty(XmlDocumentProperty::ValidateOnParse, source.GetDocumentProperty(XmlDocumentProperty::ValidateOnParse));

	destination.SetDocumentProperty(XmlDocumentProperty::AsyncLoading, source.GetDocumentProperty(XmlDocumentProperty::AsyncLoading));
	destination.SetDocumentProperty(XmlDocumentProperty::PreserveWhitespace, source.GetDocumentProperty(XmlDocumentProperty::PreserveWhitespace));
}



XmlDocument LoadXmlDocument(const void* buffer, size_t size) throw(...)
{
	XmlDocument document;

	document.Load(buffer, size);

	return document;
}

XmlDocument LoadXmlDocument(const std::wstring& filename) throw(...)
{
	XmlDocument document;

	document.Load(filename);

	return document;
}

XmlDocument LoadXmlDocument(IStream* stream) throw(...)
{
	XmlDocument document;

	document.Load(stream);

	return document;
}

} //namespace XML
} //namespace Et
