
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Elenian Toolkit: Exception
//  Version 1.1.0
//  Copyright © 2011-2014, Arthur Kozyrev
//  Web: https://github.com/ArthurKozyrev/Et
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Available defines:
//    ET_DISABLE_EXCEPTIONS -- disable exceptions everywhere
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <exception>

#include <Et\COM\ComPtr.hpp>
#include <Et\Conversion.hpp>
#include <Et\Detail\ExceptionDef.hpp>
#include <Et\Detail\ExceptionInfo.hpp>
#include <Et\Detail\ExceptionUtils.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {

template <typename T>
class Exception : virtual public std::exception
{
public:
	typedef Et::Detail::ExceptionInfo<T, ExceptionInfoType::Message> MessageInfo_t;
	typedef Et::Detail::ExceptionInfo<T, ExceptionInfoType::ErrorCode> ErrorCodeInfo_t;
	typedef Et::Detail::ExceptionInfo<T, ExceptionInfoType::Location> LocationInfo_t;
	typedef Et::Detail::ExceptionInfo<T, ExceptionInfoType::File> FileInfo_t;
	typedef Et::Detail::ExceptionInfo<T, ExceptionInfoType::Line> LineInfo_t;
	
public:
	Exception();
	explicit Exception(const char* message, int error_code = 0);
	Exception(const Exception& other);
	Exception(Exception&& other);
	~Exception() throw();

public:
	virtual auto GetDefaultMessage() const -> const char* const;
	auto GetExceptionInfo(ExceptionInfoType type) const -> const char*;
	auto GetExceptionInfoImpl(ExceptionInfoType type) const -> Et::COM::ComPtr<IExceptionInfo>;
	void SetExceptionInfo(ExceptionInfoType type, const char* info);
	void SetExceptionInfoImpl(ExceptionInfoType type, IExceptionInfo* ptr);

	const char* what() const override;

public:
	Exception& operator=(const Exception& other);
	Exception& operator=(Exception&& other);

protected:
	mutable Et::COM::ComPtr<IExceptionInfo> _messageInfoPtr;
	mutable Et::COM::ComPtr<IExceptionInfo> _errorCodeInfoPtr;
	mutable Et::COM::ComPtr<IExceptionInfo> _locationInfoPtr;
	mutable Et::COM::ComPtr<IExceptionInfo> _fileInfoPtr;
	mutable Et::COM::ComPtr<IExceptionInfo> _lineInfoPtr;

	template <typename E, typename T, ExceptionInfoType type>
	friend const E& operator<<(const E& e, const Et::Detail::ExceptionInfo<T, type>& info);
	template <typename E, typename T, ExceptionInfoType type>
	friend const E& operator<<(const E& e, Et::Detail::ExceptionInfo<T, type>&& info);
	template <typename E, typename T, ExceptionInfoType type>
	friend const E& operator>>(const E& e, Et::Detail::ExceptionInfo<T, type>& info);
};

/*************************************************************************************************/

namespace Detail {

static const auto kDefaulExceptionMessage = "Unknown Exception";

}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Exception<T>::Exception()
{
	_messageInfoPtr.Attach(new MessageInfo_t(Et::Detail::kDefaulExceptionMessage));
	_errorCodeInfoPtr.Attach(new ErrorCodeInfo_t());
	_locationInfoPtr.Attach(new LocationInfo_t());
	_fileInfoPtr.Attach(new FileInfo_t());
	_lineInfoPtr.Attach(new LineInfo_t());
}

template <typename T>
Exception<T>::Exception(const char* message, int error_code)
{
	_messageInfoPtr.Attach(new MessageInfo_t(message));
	_errorCodeInfoPtr.Attach(new ErrorCodeInfo_t(IntToStr<std::string>(error_code)));
	_locationInfoPtr.Attach(new LocationInfo_t());
	_fileInfoPtr.Attach(new FileInfo_t());
	_lineInfoPtr.Attach(new LineInfo_t());
}

template <typename T>
Exception<T>::Exception(const Exception& other)
{
	*this = other;
}

template <typename T>
Exception<T>::Exception(Exception&& other)
{
	*this = std::forward<Exception>(other);
}

template <typename T>
Exception<T>::~Exception() throw()
{
}

/*************************************************************************************************/

template <typename T>
auto Exception<T>::GetDefaultMessage() const -> const char* const
{
	return Et::Detail::kDefaulExceptionMessage;
}

template <typename T>
auto Exception<T>::GetExceptionInfo(ExceptionInfoType type) const -> const char*
{
	const char* result = nullptr;

	switch (type)
	{
		case ExceptionInfoType::Message:
			result = _messageInfoPtr->GetInfo();
			break;

		case ExceptionInfoType::ErrorCode:
			result = _errorCodeInfoPtr->GetInfo();
			break;

		case ExceptionInfoType::Location:
			result = _locationInfoPtr->GetInfo();
			break;

		case ExceptionInfoType::File:
			result = _fileInfoPtr->GetInfo();
			break;

		case ExceptionInfoType::Line:
			result = _lineInfoPtr->GetInfo();
			break;

		default:
			ET_ASSERT(0);
	}

	return result;
}

template <typename T>
auto Exception<T>::GetExceptionInfoImpl(ExceptionInfoType type) const -> Et::COM::ComPtr<IExceptionInfo>
{
	Et::COM::ComPtr<IExceptionInfo> result;

	switch (type)
	{
		case ExceptionInfoType::Message:
			result = _messageInfoPtr;
			break;

		case ExceptionInfoType::ErrorCode:
			result = _errorCodeInfoPtr;
			break;

		case ExceptionInfoType::Location:
			result = _locationInfoPtr;
			break;

		case ExceptionInfoType::File:
			result = _fileInfoPtr;
			break;

		case ExceptionInfoType::Line:
			result = _lineInfoPtr;
			break;

		default:
			ET_ASSERT(0);
	}

	return result;
}

template <typename T>
void Exception<T>::SetExceptionInfo(ExceptionInfoType type, const char* info)
{
	switch (type)
	{
		case ExceptionInfoType::Message:
			_messageInfoPtr->SetInfo(info);
			break;

		case ExceptionInfoType::ErrorCode:
			_errorCodeInfoPtr->SetInfo(info);
			break;

		case ExceptionInfoType::Location:
			_locationInfoPtr->SetInfo(info);
			break;

		case ExceptionInfoType::File:
			_fileInfoPtr->SetInfo(info);
			break;

		case ExceptionInfoType::Line:
			_lineInfoPtr->SetInfo(info);
			break;

		default:
			ET_ASSERT(0);
	}
}

template <typename T>
void Exception<T>::SetExceptionInfoImpl(ExceptionInfoType type, IExceptionInfo* ptr) 
{
	switch (type)
	{
		case ExceptionInfoType::Message:
			_messageInfoPtr = ptr;
			break;

		case ExceptionInfoType::ErrorCode:
			_errorCodeInfoPtr = ptr;
			break;

		case ExceptionInfoType::Location:
			_locationInfoPtr = ptr;
			break;

		case ExceptionInfoType::File:
			_fileInfoPtr = ptr;
			break;

		case ExceptionInfoType::Line:
			_lineInfoPtr = ptr;
			break;

		default:
			ET_ASSERT(0);
	}
}



template <typename T>
const char* Exception<T>::what() const
{
	return _messageInfoPtr->GetInfo();
}

/*************************************************************************************************/

template <typename T>
Exception<T>& Exception<T>::operator=(const Exception& other)
{
	if (this != &other)
	{
		_messageInfoPtr = other._messageInfoPtr;
		_errorCodeInfoPtr = other._errorCodeInfoPtr;
		_locationInfoPtr = other._locationInfoPtr;
		_fileInfoPtr = other._fileInfoPtr;
		_lineInfoPtr = other._lineInfoPtr;
	}

	return *this;
}

template <typename T>
Exception<T>& Exception<T>::operator=(Exception&& other)
{
	if (this != &other)
	{
		_messageInfoPtr = std::move(other._messageInfoPtr);
		_errorCodeInfoPtr = std::move(other._errorCodeInfoPtr);
		_locationInfoPtr = std::move(other._locationInfoPtr);
		_fileInfoPtr = std::move(other._fileInfoPtr);
		_lineInfoPtr = std::move(other._lineInfoPtr);
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename E, typename T, ExceptionInfoType type>
const E& operator<<(const E& e, const Et::Detail::ExceptionInfo<T, type>& info)
{
	E& exception = const_cast<E&>(e);

	exception.SetExceptionInfo(type, info.GetInfo());

	return e;
}

template <typename E, typename T, ExceptionInfoType type>
const E& operator<<(const E& e, Et::Detail::ExceptionInfo<T, type>&& info)
{
	E& exception = const_cast<E&>(e);

	exception.SetExceptionInfo(type, info.GetInfo());

	return e;
}

template <typename E, typename T, ExceptionInfoType type>
const E& operator>>(const E& e, Et::Detail::ExceptionInfo<T, type>& info)
{
	info.SetInfo(e.GetExceptionInfo(type));

	return e;
}

} //namespace Et
