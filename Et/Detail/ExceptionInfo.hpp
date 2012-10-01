
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <string>

#include <Et\IExceptionInfo.hpp>
#include <Et\Conversion.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace Detail {

template <typename T, ExceptionInfoType type>
class ExceptionInfo : public IExceptionInfo
{
private:
	typedef ExceptionInfo<T, type> _My_t;

public:
	ExceptionInfo();
	explicit ExceptionInfo(const char* info);
	explicit ExceptionInfo(const std::string& info);
	ExceptionInfo(const _My_t& other);
	ExceptionInfo(_My_t&& other);
	~ExceptionInfo();

public:
	HRESULT WINAPI QueryInterface(const IID& iid, void** output);
	ULONG WINAPI AddRef() override;
	ULONG WINAPI Release() override;

	IExceptionInfo* Clone() const override;

	ExceptionInfoType GetType() const override;
	const char* const GetInfo() const override;
	void SetInfo(const char* info) override;

public:
	_My_t& operator=(const _My_t& other);
	_My_t& operator=(_My_t&& other);

protected:
	volatile unsigned long _refCount;
	ExceptionInfoType _type;
	mutable char* _info;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, ExceptionInfoType type>
inline ExceptionInfo<T, type>::ExceptionInfo() : _refCount(1), _type(type), _info(nullptr)
{
}

template <typename T, ExceptionInfoType type>
inline ExceptionInfo<T, type>::ExceptionInfo(const char* info) : _refCount(1), _type(type), _info(_strdup(info))
{
}

template <typename T, ExceptionInfoType type>
inline ExceptionInfo<T, type>::ExceptionInfo(const std::string& info) : _refCount(1), _type(type), _info(_strdup(info.c_str()))
{
}

template <typename T, ExceptionInfoType type>
inline ExceptionInfo<T, type>::ExceptionInfo(const _My_t& other) : _refCount(1), _type(type), _info(_strdup(other._info))
{
}

template <typename T, ExceptionInfoType type>
inline ExceptionInfo<T, type>::ExceptionInfo(_My_t&& other) : _refCount(1), _type(type), _info(nullptr)
{
	std::swap(_info, other._info);
}

template <typename T, ExceptionInfoType type>
inline ExceptionInfo<T, type>::~ExceptionInfo()
{
	free(_info);
}

/*************************************************************************************************/

template <typename T, ExceptionInfoType type>
inline HRESULT ExceptionInfo<T, type>::QueryInterface(const IID& iid, void** output)
{
	HRESULT result = E_NOINTERFACE;

	if (!output)
		return E_INVALIDARG;

	if (iid == __uuidof(IUnknown))
	{
		AddRef();
		*output = static_cast<IUnknown*>(this);

		result = S_OK;
	}
	else if (iid == __uuidof(IExceptionInfo))
	{
		AddRef();
		*output = static_cast<IExceptionInfo*>(this);

		result = S_OK;
	}
	
	return result;
}

template <typename T, ExceptionInfoType type>
inline ULONG ExceptionInfo<T, type>::AddRef()
{
	return InterlockedIncrement(&_refCount);
}

template <typename T, ExceptionInfoType type>
inline ULONG ExceptionInfo<T, type>::Release()
{
	const auto result = InterlockedDecrement(&_refCount);

	if (!result)
		delete this;

	return result;
}

template <typename T, ExceptionInfoType type>
inline auto ExceptionInfo<T, type>::Clone() const -> IExceptionInfo*
{
	return static_cast<IExceptionInfo*>(new _My_t(*this));
}



template <typename T, ExceptionInfoType type>
inline auto ExceptionInfo<T, type>::GetType() const -> ExceptionInfoType
{
	return _type;
}

template <typename T, ExceptionInfoType type>
inline auto ExceptionInfo<T, type>::GetInfo() const -> const char* const
{
	return _info;
}

template <typename T, ExceptionInfoType type>
inline void ExceptionInfo<T, type>::SetInfo(const char* info)
{
	free(_info);
	_info = _strdup(info);
}

/*************************************************************************************************/

template <typename T, ExceptionInfoType type>
inline auto ExceptionInfo<T, type>::operator=(const _My_t& other) -> _My_t&
{
	if (this != &other)
	{
		free(_info);
		_info = _strdup(other._info);
	}

	return *this;
}

template <typename T, ExceptionInfoType type>
inline auto ExceptionInfo<T, type>::operator=(_My_t&& other) -> _My_t&
{
	if (this != &other)
	{
		free(_info);
		_info = nullptr;
		std::swap(_info, other._info);
	}

	return *this;
}

} //namespace Detail
} //namespace Et
