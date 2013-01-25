
#include "_headers.hxx"

#include <Et\Exception.hpp>

#include <boost\exception\all.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

template<> static std::wstring ToString<Et::COM::ComPtr<Et::IExceptionInfo>> (const Et::COM::ComPtr<Et::IExceptionInfo>& t) { RETURN_WIDE_STRING(t); }

}}}

/*************************************************************************************************/

namespace Test {

class Exception : public Et::Exception<Exception>
{
public:
	Exception();
	Exception(const char* message, int code = 0);
	Exception(Exception&& other);
};

class Exception2 : public Et::Exception<Exception2>, public boost::exception
{
public:
	Exception2(const char* message);
};

/*************************************************************************************************/

TEST_CLASS(ExceptionTest)
{
public:
	TEST_METHOD(Exception_1)
	{
		Exception e1;
		Exception e2("My Exception");
		Exception e3(nullptr, E_FAIL);
		Exception e4 = e2;
		Exception e5 = std::move(Exception(nullptr));

		Assert::IsNotNull(e1.what());
		Assert::IsNotNull(e2.what());
		Assert::IsNull(e3.what());
		Assert::IsNotNull(e4.what());
		Assert::IsNull(e5.what());
		Assert::AreNotEqual(e1.what(), e2.what());
		Assert::AreNotEqual(e2.what(), e3.what());
	}

	TEST_METHOD(Exception_2)
	{
		using Et::ExceptionInfoType;
		
		const auto kMessage = "My Exception";
		const auto kErrorCode = E_FAIL;
		const auto kErrorCodeStr = std::to_string(kErrorCode);

		Exception e1;
		Exception e2(kMessage, kErrorCode);
		Exception e3 = e2;

		Assert::IsNotNull(e1.GetExceptionInfo(ExceptionInfoType::Message));
		Assert::AreEqual(e2.GetExceptionInfo(ExceptionInfoType::ErrorCode), kErrorCodeStr.c_str());
		Assert::AreEqual(e3.GetExceptionInfo(ExceptionInfoType::Message), e2.GetExceptionInfo(ExceptionInfoType::Message));
		Assert::AreEqual(e3.GetExceptionInfoImpl(ExceptionInfoType::File), e2.GetExceptionInfoImpl(ExceptionInfoType::File));

		try
		{
			ET_THROW_EXCEPTION(e2);
		}
		catch(const Exception& e)
		{
			LOG("Message: "), LOG(e.GetExceptionInfo(ExceptionInfoType::Message)), LOG_NL();
			LOG("ErrorCode: "), LOG(e.GetExceptionInfo(ExceptionInfoType::ErrorCode)), LOG_NL();
			LOG("File: "), LOG(e.GetExceptionInfo(ExceptionInfoType::File)), LOG_NL();
			LOG("Line: "), LOG(e.GetExceptionInfo(ExceptionInfoType::Line)), LOG_NL();
			LOG("Location: "), LOG(e.GetExceptionInfo(ExceptionInfoType::Location)), LOG_NL();
		}
	}

	TEST_METHOD(Exception_3)
	{
		using Et::ExceptionInfoType;

		const auto kMessage = "My Exception";

		Exception2 e(kMessage);
		Exception2::LineInfo_t lineInfo;
		Exception2::FileInfo_t fileInfo(__FILE__);

		e << Exception2::ErrorCodeInfo_t("-1") << fileInfo << Exception2::LocationInfo_t(__FUNCSIG__);
		e >> lineInfo;
		auto lineInfoImpl = e.GetExceptionInfoImpl(ExceptionInfoType::Line);
		Assert::AreEqual(lineInfo.GetInfo(), lineInfoImpl->GetInfo());

		try
		{
			BOOST_THROW_EXCEPTION(e);
		}
		catch(const Exception2& e)
		{
			Assert::AreEqual(kMessage, e.what());	

			LOG(e.what()), LOG_NL();
		}
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////

Exception::Exception()
{
}

Exception::Exception(const char* message, int code) : Et::Exception<Exception>(message, code)
{
}

Exception::Exception(Exception&& other) : Et::Exception<Exception>(std::forward<Exception>(other))
{
}

/*************************************************************************************************/

Exception2::Exception2(const char* message) : Et::Exception<Exception2>(message)
{
	
}

} //namespace Test
