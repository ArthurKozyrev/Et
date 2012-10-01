
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
namespace Detail {

static const char* kCannotCreateInstanceOfDOMDocument = "XML: cannot create instance of MSXML6::DOMDocument60";
static const char* kCannotCreateInstanceOfSAXReader = "XML: cannot create instance of MSXML6::SAXXMLReader60";
static const char* kCannotCreateInstanceOfMXWriter = "XML: cannot create instance of MSXML6::MXXMLWriter60";

static const char* kInvalidArgument = "XML: one or more arguments are invalid";
static const char* kCannotAccessFile = "XML: cannot access file";

//XmlNode
static const char* kInvalidNodeType = "XML: invalid node type";
static const char* kCannotCloneNode = "XML: cannot clone node";
static const char* kCannotGetNodeValue = "XML: cannot get node value";
static const char* kCannotGetOwnerDocument = "XML: cannot get node owner document";
static const char* kCannotInsertNode = "XML: cannot insert node";
static const char* kCannotReplaceNode = "XML: cannot replace node";
static const char* kCannotRemoveNode = "XML: cannot remove node";
static const char* kCannotTransformNode = "XML: cannot transform node";
static const char* kCannotValidateNode = "XML: cannot validate node";

//XmlElement
static const char* kNodeIsNotAnElement = "XML: node is not an element";
static const char* kCannotNormalizeText = "XML: cannot normalize text";
static const char* kCannotInsertAttribute = "XML: cannot insert attribute";
static const char* kCannotRemoveAttribute = "XML: cannot remove attribute";

//XmlDocument
static const char* kInvalidDocumentState = "XML: invalid document state";
static const char* kCannotCloneDocument = "XML: cannot clone document";
static const char* kCannotLoadDocument = "XML: cannot load document";
static const char* kCannotSaveDocument = "XML: cannot save document";
static const char* kCannotTransformDocument = "XML: cannot transform document";
static const char* kCannotValidateDocument = "XML: cannot validate document";

//XmlSerializer
static const char* kCannotGetSerializerProperty = "XML: сannot get serializer property";
static const char* kCannotSetSerializerProperty = "XML: сannot set serializer property";
static const char* kCannotGetSerializerOutput = "XML: сannot get serializer output";
static const char* kCannotSetSerializerOutput = "XML: сannot set serializer output";
static const char* kCannotSerializeDocument = "XML: сannot serialize document";

} //namespace Detail
} //namespace XML
} //namespace Et
