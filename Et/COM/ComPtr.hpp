
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Elenian Toolkit: COM smart pointer
//  Version 1.0.3
//  Copyright © 2011-2013, Arthur Kozyrev
//  Web: https://github.com/ArthurKozyrev/Et
//  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <exception>

#include <unknwn.h>

#include <Et\Assertion.hpp>
#include <Et\Detail\ExceptionDef.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {
namespace COM {
	
template <typename T>
class ComPtr sealed
{
public:
	typedef T Element_t;

public:
	ComPtr();
	ComPtr(T* ptr);
	template <typename U>
	ComPtr(U* ptr);
	template <typename U>
	ComPtr(const ComPtr<U>& other);
	ComPtr(const ComPtr<T>& other);
	ComPtr(ComPtr<T>&& other);
	~ComPtr();

public:
	void Attach(T* ptr);
	T* Detach();

	bool IsEqual(T* ptr) const;
	bool IsEqual(const ComPtr<T>& other) const;
	bool IsEqualObject(IUnknown* ptr) const;

	void Reset();

	template <typename U>
	ComPtr<U> QueryInterface() const;
	
public:
	T* operator=(T* ptr);
	template <typename U>
	T* operator=(U* ptr);
	template <typename U>
	T* operator=(const ComPtr<U>& other);
	T* operator=(const ComPtr<T>& other);
	T* operator=(ComPtr<T>&& other);
	operator T*() const;
	bool operator!() const;
	T& operator*() const throw(...);
	T* operator->() const throw(...);
	T** operator&() throw(...);
	bool operator<(T* ptr) const;
	bool operator<(const ComPtr<T>& other) const;
	bool operator>(T* ptr) const;
	bool operator>(const ComPtr<T>& other) const;
	bool operator==(T* ptr) const;
	bool operator==(const ComPtr<T>& other) const;
	bool operator!=(T* ptr) const;
	bool operator!=(const ComPtr<T>& other) const;

protected:
	void _AddRef();
	void _Release();
	void _QueryInterface(IUnknown* ptr);
	void _AssignNewPointer(T* ptr);

private:
	template <typename U>
	bool IsEqual(U* ptr) const;
	template <typename U>
	bool IsEqual(const ComPtr<U>& other) const;

private:
	template <typename U>
	bool operator<(U* ptr) const;
	template <typename U>
	bool operator<(const ComPtr<U>& other) const;
	template <typename U>
	bool operator>(U* ptr) const;
	template <typename U>
	bool operator>(const ComPtr<U>& other) const;
	template <typename U>
	bool operator==(U* ptr) const;
	template <typename U>
	bool operator==(const ComPtr<U>& other) const;
	template <typename U>
	bool operator!=(U* ptr) const;
	template <typename U>
	bool operator!=(const ComPtr<U>& other) const;

protected:
	T* _ptr;
};

///////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
ComPtr<T>::ComPtr() : _ptr(nullptr)
{
}

template <typename T>
ComPtr<T>::ComPtr(T* ptr)  : _ptr(ptr)
{
	_AddRef();
}

template <typename T> template <typename U>
ComPtr<T>::ComPtr(U* ptr) : _ptr(nullptr)
{
	_QueryInterface(ptr);
}

template <typename T> template <typename U>
ComPtr<T>::ComPtr(const ComPtr<U>& other) : _ptr(nullptr)
{
	_QueryInterface(static_cast<U*>(other));
}

template <typename T>
ComPtr<T>::ComPtr(const ComPtr<T>& other) : _ptr(other._ptr)
{
	_AddRef();
}

template <typename T>
ComPtr<T>::ComPtr(ComPtr<T>&& other) : _ptr(nullptr)
{
	std::swap(_ptr, other._ptr);
}

template <typename T>
ComPtr<T>::~ComPtr()
{
	_Release();
}

/*************************************************************************************************/

template <typename T>
void ComPtr<T>::Attach(T* ptr)
{
	_Release();
	_ptr = ptr;
}

template <typename T>
T* ComPtr<T>::Detach()
{
	T* result = _ptr;

	_ptr = nullptr;

	return result;
}



template <typename T>
bool ComPtr<T>::IsEqual(T* ptr) const
{
	return (*this == ptr);
}

template <typename T>
bool ComPtr<T>::IsEqual(const ComPtr<T>& other) const
{
	return (*this == other);
}

template <typename T>
bool ComPtr<T>::IsEqualObject(IUnknown* ptr) const
{
	if (!ptr && !_ptr)
		return true;

	if (!ptr || !_ptr)
		return false;

	ComPtr<IUnknown> unknown1, unknown2;

	_ptr->QueryInterface<IUnknown>(&unknown1);
	ptr->QueryInterface<IUnknown>(&unknown2);

	return (unknown1 == unknown2);
}



template <typename T>
void ComPtr<T>::Reset()
{
	_Release();
}



template <typename T> template <typename U>
ComPtr<U> ComPtr<T>::QueryInterface() const
{
	ComPtr<U> result;

	if (_ptr)
		_ptr->QueryInterface<U>(&result);

	return result;
}

/*************************************************************************************************/

template <typename T>
T* ComPtr<T>::operator=(T* ptr)
{
	if (*this != ptr)
		_AssignNewPointer(ptr);

	return _ptr;
}

template <typename T> template <typename U>
T* ComPtr<T>::operator=(U* ptr)
{
	if (!IsEqualObject(ptr))
	{
		_Release();
		_QueryInterface(ptr);
	}

	return _ptr;
}

template <typename T> template <typename U>
T* ComPtr<T>::operator=(const ComPtr<U>& other)
{
	return operator=(static_cast<U*>(other));
}

template <typename T>
T* ComPtr<T>::operator=(const ComPtr<T>& other)
{
	return operator=(static_cast<T*>(other));
}

template <typename T>
T* ComPtr<T>::operator=(ComPtr<T>&& other)
{
	if (*this != other)
	{
		_Release();
		std::swap(_ptr, other._ptr);
	}

	return _ptr;
}

template <typename T>
ComPtr<T>::operator T*() const
{
	return _ptr;
}

template <typename T>
bool ComPtr<T>::operator!() const
{
	return !_ptr;
}

template <typename T>
T& ComPtr<T>::operator*() const throw(...)
{
	ET_ASSERT(_ptr != nullptr);
	if (!_ptr)
		ET_THROW(std::exception("COM pointer is null"));

	return *_ptr;
}

template <typename T>
T* ComPtr<T>::operator->() const throw(...)
{
	ET_ASSERT(_ptr != nullptr);
	if (!_ptr)
		ET_THROW(std::exception("COM pointer is null"));

	return _ptr;
}

template <typename T>
T** ComPtr<T>::operator&() throw(...)
{
	ET_ASSERT(_ptr == nullptr);
	if (_ptr)
		ET_THROW(std::exception("COM pointer is not null"));

	return &_ptr;
}

template <typename T>
bool ComPtr<T>::operator<(T* ptr) const
{
	return (_ptr < ptr);
}

template <typename T>
bool ComPtr<T>::operator<(const ComPtr<T>& other) const
{
	return operator<(static_cast<T*>(other));
}

template <typename T>
bool ComPtr<T>::operator>(T* ptr) const
{
	return !(operator<(ptr));
}

template <typename T>
bool ComPtr<T>::operator>(const ComPtr<T>& other) const
{
	return !(operator<(other));
}

template <typename T>
bool ComPtr<T>::operator==(T* ptr) const
{
	return (_ptr == ptr);
}

template <typename T>
bool ComPtr<T>::operator==(const ComPtr<T>& other) const
{
	return operator==(static_cast<T*>(other));
}

template <typename T>
bool ComPtr<T>::operator!=(T* ptr) const
{
	return !(operator==(ptr));
}

template <typename T>
bool ComPtr<T>::operator!=(const ComPtr<T>& other) const
{
	return !(operator==(other));
}

/*************************************************************************************************/

template <typename T>
void ComPtr<T>::_AddRef()
{
	if (_ptr)
		_ptr->AddRef();
}

template <typename T>
void ComPtr<T>::_Release()
{
	if (_ptr)
	{
		_ptr->Release();
		_ptr = nullptr;
	}
}

template <typename T>
void ComPtr<T>::_QueryInterface(IUnknown* ptr)
{
	if (ptr)
		ptr->QueryInterface<T>(&_ptr);
}

template <typename T>
void ComPtr<T>::_AssignNewPointer(T* ptr)
{
	if (ptr)
		ptr->AddRef();
	if (_ptr)
		_ptr->Release();

	_ptr = ptr;
}

/*************************************************************************************************/

template <typename T> template <typename U>
bool ComPtr<T>::IsEqual(U* ptr) const
{
	return IsEqualObject(ptr);
}

template <typename T> template <typename U>
bool ComPtr<T>::IsEqual(const ComPtr<U>& other) const
{
	return IsEqualObject(other);
}

/*************************************************************************************************/

template <typename T> template <typename U>
bool ComPtr<T>::operator<(U* ptr) const
{
	return (_ptr < ptr);
}

template <typename T> template <typename U>
bool ComPtr<T>::operator<(const ComPtr<U>& other) const
{
	return operator<(static_cast<U*>(other));
}

template <typename T> template <typename U>
bool ComPtr<T>::operator>(U* ptr) const
{
	return !(operator<(ptr));
}

template <typename T> template <typename U>
bool ComPtr<T>::operator>(const ComPtr<U>& other) const
{
	return !(operator<(other));
}

template <typename T> template <typename U>
bool ComPtr<T>::operator==(U* ptr) const
{
	return IsEqualObject(ptr);
}

template <typename T> template <typename U>
bool ComPtr<T>::operator==(const ComPtr<U>& other) const
{
	return operator==(static_cast<U*>(other));
}

template <typename T> template <typename U>
bool ComPtr<T>::operator!=(U* ptr) const
{
	return !(operator==(ptr));
}

template <typename T> template <typename U>
bool ComPtr<T>::operator!=(const ComPtr<U>& other) const
{
	return !(operator==(static_cast<U*>(other)));
}

} //namespace COM
} //namespace Et
