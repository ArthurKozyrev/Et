
#include <Et\XML\XmlNodeList.hpp>
#include <Et\XML\XmlNode.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace XML {

XmlNodeList::XmlNodeList(const _DOMNodeListPtr_t& ptr) : _implPtr(ptr)
{
}

XmlNodeList::XmlNodeList(const XmlNodeList& other) : _implPtr(other._implPtr)
{
}

XmlNodeList::XmlNodeList(_DOMNodeListPtr_t&& ptr) : _implPtr(std::forward<_DOMNodeListPtr_t>(ptr))
{
}

XmlNodeList::XmlNodeList(XmlNodeList&& other) : _implPtr(std::move(other._implPtr))
{
}

XmlNodeList::~XmlNodeList()
{
}

/*************************************************************************************************/

size_t XmlNodeList::GetCount() const
{
	long itemCount = 0;
	
	_implPtr->get_length(&itemCount);

	return static_cast<size_t>(itemCount);
}

XmlNode XmlNodeList::GetNode(size_t index) const
{
	_DOMNodePtr_t nodePtr;
	
	_implPtr->get_item(static_cast<long>(index), &nodePtr);
	
	return XmlNode(std::move(nodePtr));
}

XmlNode XmlNodeList::GetNode(const std::wstring& name, size_t index) const
{
	const size_t childCount = GetCount();
	size_t matchCount = 0;
	XmlNode result = XmlNode::EmptyNode();
	
	for (size_t n = 0; n < childCount; ++n)
	{
		XmlNode node = GetNode(n);

		if (node.GetName() == name)
			if (matchCount++ == index)
			{
				result = std::move(node);
				break;
			}
	}

	return result;
}

XmlNode XmlNodeList::GetNode(XmlNodeType type, size_t index) const
{
	const size_t childCount = GetCount();
	size_t matchCount = 0;
	XmlNode result = XmlNode::EmptyNode();
	
	for (size_t n = 0; n < childCount; ++n)
	{
		XmlNode node = GetNode(n);

		if ((node.GetNodeType() & type) != XmlNodeType::None)
			if (matchCount++ == index)
			{
				result = std::move(node);
				break;
			}
	}

	return result;
}

XmlNode XmlNodeList::GetNode(XmlNodeType type, const std::wstring& name, size_t index) const
{
	const size_t childCount = GetCount();
	size_t matchCount = 0;
	XmlNode result = XmlNode::EmptyNode();
	
	for (size_t n = 0; n < childCount; ++n)
	{
		XmlNode node = GetNode(n);

		if ((node.GetNodeType() & type) != XmlNodeType::None)
			if (node.GetName() == name)
				if (matchCount++ == index)
				{
					result = std::move(node);
					break;
				}
	}
	
	return result;
}

/*************************************************************************************************/

XmlNodeList& XmlNodeList::operator=(const XmlNodeList& other)
{
	if (this != &other)
	{
		_implPtr = other._implPtr;
	}

	return *this;
}

XmlNodeList& XmlNodeList::operator=(XmlNodeList&& other)
{
	if (this != &other)
	{
		_implPtr = std::move(other._implPtr);
	}

	return *this;
}

XmlNodeList::operator bool() const
{
	return (_implPtr != nullptr);
}

bool XmlNodeList::operator!() const
{
	return (_implPtr == nullptr);
}

XmlNode XmlNodeList::operator[](size_t index) const
{
	return GetNode(index);
}

bool XmlNodeList::operator==(const XmlNodeList& other) const
{
	return _implPtr.IsEqualObject(other._implPtr);
}

bool XmlNodeList::operator!=(const XmlNodeList& other) const
{
	return !(operator==(other));
}

/*************************************************************************************************/

XmlNodeList::XmlNodeList()
{
}

} //namespace XML
} //namespace Et
