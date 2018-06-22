#ifndef ABI_IPA_INTERNAL_IPA_CONTENT_H_
#define ABI_IPA_INTERNAL_IPA_CONTENT_H_
//////////////////////////////////////////////////////////////////////////
#include "ABI/zip_internal/zip_object_reader.h"
//////////////////////////////////////////////////////////////////////////
namespace ABI{
	namespace ipa_internal{
		class IPAContent:private zip_internal::ZIPReader
		{
		public:
			explicit IPAContent(const char* app_name);
			virtual~ IPAContent();
			bool Open(const char* ipa_name);
			bool SetITunesMetaDataContentBuf();
			bool SetInfoPlistContentBuf();
			const char* ipa_buf() const;
			size_t ipa_len() const;
		private:
			char* ipa_zbuf_;
			size_t ipa_zlen_;
		};
	}
}
//////////////////////////////////////////////////////////////////////////
#endif