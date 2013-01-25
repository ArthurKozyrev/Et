
#include "_headers.hxx"

#include <Et\COM\ComPtr.hpp>

#import <msxml6.dll> rename_namespace("MSXML6"), no_smart_pointers, raw_interfaces_only

///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4800)

///////////////////////////////////////////////////////////////////////////////////////////////////

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MSXML6;

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Test {
	
TEST_CLASS(ComPtrTest)
{
public:
	TEST_METHOD(ComPtr)
	{
		using Et::COM::ComPtr;

		CoInitialize(nullptr);
		{
			ComPtr<IUnknown> cp1;
			ComPtr<IUnknown> cp2 = 0;
			ComPtr<IUnknown> cp3 = cp2;
			ComPtr<IUnknown> cp4(std::move(ComPtr<IUnknown>(nullptr)));
			ComPtr<IXMLDOMDocument3> cp5((IUnknown*)0);
			ComPtr<IXMLDOMDocument3> cp6((IXMLDOMDocument3*)0);
			ComPtr<IXMLDOMDocument3> cp7 = cp6;
		
			IXMLDOMDocument3* xmlDomDocumentPtr = nullptr;
			auto CoCreateInstanceResult = CoCreateInstance(__uuidof(DOMDocument60), nullptr, CLSCTX_INPROC_SERVER,
				__uuidof(IXMLDOMDocument3), reinterpret_cast<void**>(&xmlDomDocumentPtr));
			Assert::IsTrue(SUCCEEDED(CoCreateInstanceResult));

			cp1.Attach(xmlDomDocumentPtr);
			cp2 = xmlDomDocumentPtr;
			cp3 = cp2;
			cp4 = std::move(cp3);
			Assert::IsTrue(cp1 != cp2);
			Assert::IsTrue(!cp3);
			Assert::IsTrue(cp4);
			Assert::IsTrue(cp4.IsEqualObject(cp1));
			Assert::IsTrue(cp4.IsEqual(cp2));
			Assert::IsTrue(cp4.IsEqual(static_cast<IUnknown*>(cp2)));
			LOG(cp2 > cp1 ? "cp2 > cp1" : "cp2 <= cp1"), LOG_NL();

			cp5 = cp1;
			cp6 = cp2;
			(*cp5).QueryInterface(&cp7);
			cp7.Detach()->Release();
			Assert::IsTrue(cp5 && cp6 && !cp7);
		}
		CoUninitialize();
	}
};

} //namespace Test
