
#include "_headers.hxx"

#include <Et\String.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4245)

///////////////////////////////////////////////////////////////////////////////////////////////////

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Test {

TEST_CLASS(StringTest)
{
public:
	TEST_METHOD(NormalizeString)
	{
		using Et::IsNormalizedString;
		using Et::NormalizationType;

		const auto kTestValue = L"Tèst string ｔｏ nørmälize";

		Assert::IsTrue(IsNormalizedString(kTestValue, -1, NormalizationType::Composition), nullptr, LINE_INFO());
		Assert::IsFalse(IsNormalizedString(kTestValue, -1, NormalizationType::Decomposition), nullptr, LINE_INFO());
		Assert::IsFalse(IsNormalizedString(kTestValue, -1, NormalizationType::ObsoleteComposition), nullptr, LINE_INFO());
		Assert::IsFalse(IsNormalizedString(kTestValue, -1, NormalizationType::ObsoleteDecomposition), nullptr, LINE_INFO());
	}

	

	TEST_METHOD(AnsiToWide)
	{
		using Et::AnsiToWide;

		const auto russianLocaleId = MAKELCID(MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA), SORT_DEFAULT);
		auto currentThreadLocaleId = GetThreadLocale();
		SetThreadLocale(russianLocaleId);
		
		const std::string kTestValue = "Привет, Мир!";
		const std::wstring kResultValue = L"Привет, Мир!";

		auto result1 = AnsiToWide(kTestValue, CP_THREAD_ACP);
		auto result2 = AnsiToWide(kTestValue.c_str(), CP_OEMCP);

		Assert::AreEqual(result1.c_str(), kResultValue.c_str(), false, nullptr, LINE_INFO());
		Assert::AreNotEqual(result2.c_str(), kResultValue.c_str(), false, nullptr, LINE_INFO());

		SetThreadLocale(currentThreadLocaleId);
	}

	TEST_METHOD(UTF8ToWide)
	{
		using Et::UTF8ToWide;
		
		const std::string kTestValue = "РџСЂРёРІРµС‚, РњРёСЂ!";
		const std::wstring kResultValue = L"Привет, Мир!";

		auto result1 = UTF8ToWide(kTestValue);
		auto result2 = UTF8ToWide(kTestValue.c_str());

		Assert::AreEqual(result1.c_str(), kResultValue.c_str(), false, nullptr, LINE_INFO());
		Assert::AreEqual(result2.c_str(), kResultValue.c_str(), false, nullptr, LINE_INFO());
	}

	TEST_METHOD(WideToAnsi)
	{
		using Et::WideToAnsi;

		const auto russianLocaleId = MAKELCID(MAKELANGID(LANG_RUSSIAN, SUBLANG_RUSSIAN_RUSSIA), SORT_DEFAULT);
		auto currentThreadLocaleId = GetThreadLocale();

		SetThreadLocale(russianLocaleId);
		const std::wstring kTestValue = L"Привет, Мир!";
		const std::string kResultValue = "Привет, Мир!";

		auto result1 = WideToAnsi(kTestValue, CP_THREAD_ACP);
		auto result2 = WideToAnsi(kTestValue.c_str(), CP_OEMCP);

		Assert::AreEqual(result1.c_str(), kResultValue.c_str(), false, nullptr, LINE_INFO());
		Assert::AreNotEqual(result2.c_str(), kResultValue.c_str(), false, nullptr, LINE_INFO());

		SetThreadLocale(currentThreadLocaleId);
	}

	TEST_METHOD(WideToUTF8)
	{
		using Et::WideToUTF8;
		
		const std::wstring kTestValue = L"Привет, Мир!";
		const std::string kResultValue = "РџСЂРёРІРµС‚, РњРёСЂ!";

		auto result1 = WideToUTF8(kTestValue);
		auto result2 = WideToUTF8(kTestValue.c_str());

		Assert::AreEqual(result1.c_str(), kResultValue.c_str(), false, nullptr, LINE_INFO());
		Assert::AreEqual(result2.c_str(), kResultValue.c_str(), false, nullptr, LINE_INFO());
	}

	TEST_METHOD(AnsiToUTF8)
	{
		using Et::AnsiToUTF8;
		
		const std::string kTestValue = "Привет, Мир!";
		const std::string kResultValue = "РџСЂРёРІРµС‚, РњРёСЂ!";

		auto result1 = AnsiToUTF8(kTestValue);
		auto result2 = AnsiToUTF8(kTestValue.c_str());

		Assert::AreEqual(result1.c_str(), kResultValue.c_str(), false, nullptr, LINE_INFO());
		Assert::AreEqual(result2.c_str(), kResultValue.c_str(), false, nullptr, LINE_INFO());
	}



	TEST_METHOD(TrimString)
	{
		using Et::TrimString;

		std::wstring controlChars10 = L"\x01\x02\x03\x04\x05\x06"L"value"L"\x07\x08";
		std::wstring controlChars11 = L"\x01\x02\x03\x04\x05\x06"L"value"L"\x07\x08";
		std::wstring controlChars12 = L"\x01\x02\x03\x04\x05\x06"L"value"L"\x07\x08";
		std::wstring controlChars20 = L"\x0E\x0F\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F";
		std::wstring controlChars30 = L"\x7F\x00"L"value";
		std::wstring controlChars31 = L"\x7F"L"value";
		std::string whitespaceChars = "\x09\x0A\x0B\x0C\x0D\x20";
		std::string blankChars = "\x09\x20";

		Assert::AreEqual(TrimString(controlChars10, true, true).c_str(), L"value", false, nullptr, LINE_INFO());
		Assert::AreEqual(TrimString(controlChars11, true, false).c_str(), L"value\x07\x08", false, nullptr, LINE_INFO());
		Assert::AreEqual(TrimString(controlChars12, false, true).c_str(), L"\x01\x02\x03\x04\x05\x06value", false, nullptr, LINE_INFO());
		Assert::AreEqual(TrimString(controlChars20, true, true, std::locale("is")).c_str(), L"", false, nullptr, LINE_INFO());
		Assert::AreEqual(TrimString(controlChars30, false, false).c_str(), controlChars30.c_str(), false, nullptr, LINE_INFO());
		Assert::AreEqual(TrimString(controlChars31, true).c_str(), L"value", false, nullptr, LINE_INFO());
		Assert::AreEqual(TrimString(whitespaceChars).c_str(), "", false, nullptr, LINE_INFO());
		Assert::AreEqual(TrimString(blankChars).c_str(), "", false, nullptr, LINE_INFO());
	}

	TEST_METHOD(TrimAllString)
	{
		using Et::TrimAllString;

		std::wstring chars1 = L"\x02\x08\x09\x0C\x20"L"val\tue: \x0C 1 \b -  \t1"L"\x7F\x17\x1E";
		std::string chars2 = "\x02\x08\x09\x0C\x20""value\r: 1 -  2  ""\x7F\x17\x1E";

		Assert::AreEqual(TrimAllString(chars1).c_str(), L"value: 1 - 1", false, nullptr, LINE_INFO()); 
		Assert::AreEqual(TrimAllString(chars2).c_str(), "value: 1 - 2", false, nullptr, LINE_INFO());
	}

};

} //namespace Test
