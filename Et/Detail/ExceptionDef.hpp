
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ET_DISABLE_EXCEPTIONS

#ifndef ET_THROW
#define ET_THROW(e) ((void)0)
#endif

#ifndef ET_THROW_EXCEPTION
#define ET_THROW_EXCEPTION(e) ((void)0)
#endif

#else

#ifndef ET_THROW
#define ET_THROW(e) throw (e)
#endif

#ifndef ET_THROW_EXCEPTION
#define ET_THROW_EXCEPTION(e) Et::ThrowException(e, nullptr, 0, __FUNCSIG__, __FILE__, __LINE__)
#endif

#endif
