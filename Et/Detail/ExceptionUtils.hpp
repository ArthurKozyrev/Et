
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

#include <Et\Conversion.hpp>
#include <Et\Detail\ExceptionDef.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {

template <typename E>
E MakeException(const char* message = nullptr, int error_code = 0, const char* location = nullptr, const char* file = nullptr, int line = 0)
{
	E exception;

	if (message) exception.SetExceptionInfo(ExceptionInfoType::Message, message);
	if (error_code) exception.SetExceptionInfo(ExceptionInfoType::ErrorCode, IntToStr<std::string>(error_code).c_str());
	if (location) exception.SetExceptionInfo(ExceptionInfoType::Location, locaiton);
	if (file) exception.SetExceptionInfo(ExceptionInfoType::File, file);
	if (line) exception.SetExceptionInfo(ExceptionInfoType::Line, line);

	return exception;
}

template <typename E>
void ThrowException(const E& exception, const char* message = nullptr, int error_code = 0, const char* location = nullptr, const char* file = nullptr, int line = 0)
{
	if (message) exception << E::MessageInfo_t(message);
	if (error_code) exception << E::ErrorCodeInfo_t(IntToStr<std::string>(error_code).c_str());
	if (location) exception << E::LocationInfo_t(location);
	if (file) exception << E::FileInfo_t(file);
	if (line) exception << E::LineInfo_t(IntToStr<std::string>(line).c_str());

	ET_THROW(exception);
}

} //namespace Et
