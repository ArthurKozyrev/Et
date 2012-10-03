
#include "_headers.hxx"

#include <Et\Conversion.hpp>

#include <limits>
#include <memory>

///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma warning(disable: 4146)

///////////////////////////////////////////////////////////////////////////////////////////////////

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Test {

TEST_CLASS(ConversionTest)
{
public:
	TEST_METHOD(IntToStr)
	{
		using namespace std;
		using Et::IntToStr;

		auto result1 = IntToStr<char>(INT32_MAX);
		auto result2 = IntToStr<char>(INT64_MAX);
		auto result3 = IntToStr<wchar_t>(INT32_MAX);
		auto result4 = IntToStr<wchar_t>(INT64_MAX);
		auto result10 = to_string(INT32_MAX);
		auto result20 = to_string(INT64_MAX);
		auto result30 = to_wstring(INT32_MAX);
		auto result40 = to_wstring(INT64_MAX);
		Assert::IsTrue(result1 == result10, nullptr, LINE_INFO());
		Assert::IsTrue(result2 == result20, nullptr, LINE_INFO());
		Assert::IsTrue(result3 == result30, nullptr, LINE_INFO());
		Assert::IsTrue(result4 == result40, nullptr, LINE_INFO());
		free(result1);
		free(result2);
		free(result3);
		free(result4);

		Assert::IsTrue(IntToStr<string>(0) == to_string(0), nullptr, LINE_INFO());
		Assert::IsTrue(IntToStr<string>(-1L) == to_string(-1L), nullptr, LINE_INFO());
		Assert::IsTrue(IntToStr<string>(-1UL) == to_string(-1UL), nullptr, LINE_INFO());
		Assert::IsTrue(IntToStr<string>(-1LL) == to_string(-1LL), nullptr, LINE_INFO());
		Assert::IsTrue(IntToStr<string>(-1ULL) == to_string(-1ULL), nullptr, LINE_INFO());
		Assert::IsTrue(IntToStr<wstring>(0) == to_wstring(0), nullptr, LINE_INFO());
		Assert::IsTrue(IntToStr<wstring>(-1L) == to_wstring(-1L), nullptr, LINE_INFO());
		Assert::IsTrue(IntToStr<wstring>(-1UL) == to_wstring(-1UL), nullptr, LINE_INFO());
		Assert::IsTrue(IntToStr<wstring>(-1LL) == to_wstring(-1LL), nullptr, LINE_INFO());
		Assert::IsTrue(IntToStr<wstring>(-1ULL) == to_wstring(-1ULL), nullptr, LINE_INFO());
	}
};

} //namespace Test
