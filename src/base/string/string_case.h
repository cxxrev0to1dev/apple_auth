#ifndef ABI_BASE_STRING_CASE_H_
#define ABI_BASE_STRING_CASE_H_
//////////////////////////////////////////////////////////////////////////
#include "ABI/base/basetypes.h"
//////////////////////////////////////////////////////////////////////////
namespace ABI{
	namespace base{
		std::wstring ToUpper(const std::wstring& seque);
		std::wstring ToLower(const std::wstring& seque);
		std::string ToUpper(const std::string& seque);
		std::string ToLower(const std::string& seque);
	}
}
//////////////////////////////////////////////////////////////////////////
#endif