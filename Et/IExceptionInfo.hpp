
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <unknwn.h>

///////////////////////////////////////////////////////////////////////////////////////////////////

namespace Et {

enum class ExceptionInfoType : unsigned int
{
	Message,
	ErrorCode,
	Location,
	File,
	Line,
};

/*************************************************************************************************/

[uuid("82D95C21-6A56-46B0-B3A4-7BAE95C09346")]
class IExceptionInfo : public IUnknown
{
public:
	virtual IExceptionInfo* Clone() const = 0;

	virtual ExceptionInfoType GetType() const = 0;
	virtual const char* const GetInfo() const = 0;
	virtual void SetInfo(const char* info) = 0;
};


} //namespace Et
