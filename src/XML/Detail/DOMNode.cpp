
#include "DOMNode.hpp"

#include <Et\XML\XmlNode.hpp>

#include <bitset>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {
namespace Detail {

bool CheckNodeType(XmlNodeType type)
{
	const unsigned int kBitCount = 8 * sizeof(unsigned int);
	std::bitset<kBitCount> nodeType(static_cast<unsigned int>(type));

	return (nodeType.count() == 1);
}

XmlNodeType EncodeNodeType(unsigned int value)
{
	return static_cast<XmlNodeType>(1U << (value - 1U));
}

unsigned int DecodeNodeType(XmlNodeType type)
{
	unsigned int value = static_cast<unsigned int>(type);
	unsigned int result = 0;

	while (value)
	{
		value >>= 1U;
		++result;
	}

	return result;
}

/*************************************************************************************************/

void GetNodeText(const XmlNode& node, std::wstring& output)
{
	const XmlNodeType nodeType = XmlNodeType::Text | XmlNodeType::EntityReference;
	XmlNode childNode = node.GetFirstChildNode(nodeType);

	while (childNode)
	{
		switch (childNode.GetNodeType())
		{
			case XmlNodeType::Text:
				output += childNode.GetValue();
				break;

			case XmlNodeType::EntityReference:
				GetNodeText(childNode, output);
				break;
		}

		childNode = childNode.GetNextSiblingNode(nodeType);
	}
}

void RemoveNodeText(XmlNode& node)
{
	const XmlNodeType nodeType = XmlNodeType::Text | XmlNodeType::EntityReference;
	XmlNode childNode = node.GetLastChildNode(nodeType);

	while (childNode)
	{
		XmlNode siblingNode = childNode.GetPreviousSiblingNode(nodeType);

		switch (childNode.GetNodeType())
		{
			case XmlNodeType::Text:
			case XmlNodeType::EntityReference:
				node.RemoveChildNode(childNode);
				break;
		}

		childNode = siblingNode;
	}
}

} //namespace Detail
} //namespace XML
} //namespace Et
