
#include "_headers.hxx"

#include <Et\XML.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Test {

const auto kXmlString = 
L"<?xml version='1.0' encoding='UTF-16'?>"
L"<recipe name='хлеб' preptime='5' cooktime='180'>"
  L"<title>Простой хлеб</title>"
  L"<composition>"
    L"<ingredient amount='3' unit='стакан'>Мука</ingredient>"
    L"<ingredient amount='0.25' unit='грамм'>Дрожжи</ingredient>"
    L"<ingredient amount='1.5' unit='стакан'>Тёплая вода</ingredient>"
    L"<ingredient amount='1' unit='чайная ложка'>Соль</ingredient>"
  L"</composition>"
  L"<instructions>"
    L"<step>Смешать все ингредиенты и тщательно замесить.</step>"
    L"<step>Закрыть тканью и оставить на один час в тёплом помещении.</step>"
    L"<!-- <step>Почитать вчерашнюю газету.</step> - это сомнительный шаг... -->"
    L"<step>Замесить ещё раз, положить на противень и поставить в духовку.</step>"
  L"</instructions>"
L"</recipe>";

///////////////////////////////////////////////////////////////////////////////////////////////////

TEST_CLASS(XmlTest)
{
public:
	TEST_METHOD(XML_1)
	{
		using namespace Et::XML;

		XmlNodeType nodeType1 = XmlNodeType::Element | XmlNodeType::Attribute | XmlNodeType::CDATA;
		XmlNodeType nodeType2 = nodeType1 & (XmlNodeType::Attribute | XmlNodeType::CDATA);
		XmlNodeType nodeType3 = nodeType1; nodeType3 &= ~XmlNodeType::CDATA;
		XmlNodeType nodeType4 = ~nodeType1; nodeType4 ^= ~XmlNodeType::Element;
		XmlNodeType nodeType5 = nodeType2; nodeType5 |= nodeType4 | XmlNodeType::Comment;
	}

	TEST_METHOD(XML_2)
	{
		using namespace Et::XML;

		CoInitialize(nullptr);
		try
		{
			XmlDocument document = LoadXmlDocument(kXmlString, wcslen(kXmlString) * 2);

			//XmlNode
			XmlNode node = document;
			XmlNode node2 = XmlNode::EmptyNode();
			XmlNode node3 = document.CreateNode(XmlNodeType::DocumentFragment, L"");

			Assert::IsTrue(node);
			Assert::IsTrue(!node2);
			Assert::IsTrue(node3);
			Assert::IsTrue(node == document);
			Assert::IsTrue(node2 != document);

			Assert::IsTrue(node3.AppendChildNode(document.CreateElement(L"root")));
			Assert::IsTrue(node3.GetXML() == L"<root/>");
			Assert::IsTrue(node3.CloneNode(true));
			Assert::IsTrue(node3.RemoveChildNode(L"root", 0));
			Assert::IsTrue(node3.GetXML().empty());

			node3 = document.CreateElement(L"root", L"uri");
			Assert::IsTrue(node3.SetText(L"text"));
			Assert::IsTrue(node3.GetNodeType() == XmlNodeType::Element);
			Assert::IsTrue(node3.GetNamespaceURI() == L"uri");
			Assert::IsTrue(node3.GetPrefix().empty());
			Assert::IsTrue(node3.GetLocalName() == node3.GetName());
			Assert::IsTrue(node3.GetText() == L"text");

			Assert::IsTrue(node3.GetParentNode() == XmlNode::EmptyNode());
			Assert::IsTrue(node3.IsRoot());
			Assert::IsTrue(node3.IsParsed());
			Assert::IsTrue(node3.IsHasChildNodes());
			Assert::IsTrue(node3.ReplaceChildNode(document.CreateTextNode(L"text2"), node3.GetChildNode(XmlNodeType::Text)));
			Assert::IsTrue(node3.GetText() == L"text2");

			//XmlElement
			XmlElement element = document.GetDocumentElement();

			Assert::IsTrue(element.GetChildElementCount() == 3);
			//Assert::Is
		}
		catch(const XmlException& xe)
		{
			LOG(xe.what()), LOG_NL();
			if (xe.parseError)
			{
				const auto description = xe.parseError.GetDescription();
				LOG(description.c_str()), LOG_NL();
			}
			Assert::Fail(nullptr);
		}
		catch(const std::exception& e)
		{
			LOG(e.what()), LOG_NL();
			Assert::Fail(nullptr);
		}
		CoUninitialize();
	}
};

} //namespace Test
