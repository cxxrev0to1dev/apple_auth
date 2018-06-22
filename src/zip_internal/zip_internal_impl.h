#ifndef ABI_ZIP_INTERNAL_ZIP_INTERNAL_IMPL_H_
#define ABI_ZIP_INTERNAL_ZIP_INTERNAL_IMPL_H_
//////////////////////////////////////////////////////////////////////////
#include <libzip/zip.h>
//////////////////////////////////////////////////////////////////////////
namespace ABI{
	namespace zip_internal{
		int zip_get_contents(struct zip *zf, const char *filename, int locate_flags, char **buffer, uint32_t *len);
		int zip_get_app_directory(struct zip* zf, char** path);
	}
}
//////////////////////////////////////////////////////////////////////////
#endif