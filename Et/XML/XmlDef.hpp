
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ET_XML_DLL

#ifdef _ET_XML_EXPORTS
#define ET_XMLAPI __declspec(dllexport)
#else
#define ET_XMLAPI __declspec(dllimport)
#endif

#else
#define ET_XMLAPI
#endif

/*************************************************************************************************/

#ifdef ET_XML_DISABLE_ASSERTS

#ifndef _ET_XML_ASSERT
#define _ET_XML_ASSERT(expr) ((void)0)
#endif

#else

#ifndef _ET_XML_ASSERT
#define _ET_XML_ASSERT(expr) ET_ASSERT(expr)
#endif

#endif

/*************************************************************************************************/

#ifndef _ET_XML_THROW
#define _ET_XML_THROW(e, msg) ET_THROW_EXCEPTION(e << std::remove_reference<decltype(e)>::type::MessageInfo_t(msg))
#endif

#ifndef _ET_XML_THROW2
#define _ET_XML_THROW2(e, msg, pe) ET_THROW_EXCEPTION(e << std::remove_reference<decltype(e)>::type::MessageInfo_t(msg) << pe)
#endif

/*************************************************************************************************/

#ifdef ET_XML_SUPPRESS_MSXML_HEADERS

#ifndef __msxml_h__
#define __msxml_h__
#endif

#ifndef __ISoftDistExt_INTERFACE_DEFINED__
#define __ISoftDistExt_INTERFACE_DEFINED__
#endif

#ifndef _INC_COMDEFSP
#define _INC_COMDEFSP
#endif

#endif
