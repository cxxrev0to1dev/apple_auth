#ifndef ABI_ZIP_INTERNAL_ZIP_OBJECT_READERR_H_
#define ABI_ZIP_INTERNAL_ZIP_OBJECT_READERR_H_
//////////////////////////////////////////////////////////////////////////
#include "ABI/zip_internal/zip_internal_impl.h"
//////////////////////////////////////////////////////////////////////////
namespace ABI{
	namespace zip_internal{
		class ZIPReader
		{
		public:
			ZIPReader(){}
			explicit ZIPReader(const char* filename);
			virtual~ ZIPReader();
			void Open(const char* filename);
			zip* zf()const;
			void set_zf(struct zip* z);
		private:
			struct zip *zf_;
		};
	}
}
//////////////////////////////////////////////////////////////////////////
#endif