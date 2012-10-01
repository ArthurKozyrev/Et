
#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>

#include <memory>
#include <string>
#include <vector>

#include <comdef.h>

#include <Et\Assertion.hpp>
#include <Et\Exception.hpp>
#include <Et\COM\ComPtr.hpp>
#include <Et\COM\Deleter.hpp>

///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma comment(lib, "shlwapi.lib")

#import <msxml6.dll> rename_namespace("MSXML6"), no_smart_pointers, raw_interfaces_only
