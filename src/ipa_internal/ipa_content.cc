#include "ABI/ipa_internal/ipa_content.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <plist/plist.h>

namespace ABI{
	namespace ipa_internal{
		IPAContent::IPAContent(const char* app_name){
			ipa_zbuf_ = NULL;
			ipa_zlen_ = 0;
			Open(app_name);
		}
		IPAContent::~IPAContent(){
			if(ipa_zbuf_!=NULL){
				free(ipa_zbuf_);
				ipa_zbuf_ = NULL;
			}
			if(ipa_zlen_!=0){
				ipa_zlen_ = 0;
			}
		}
		bool IPAContent::Open(const char* ipa_name){
			if(ipa_name!=NULL){
				ZIPReader::Open(ipa_name);
				return true;
			}
			return false;
		}
		bool IPAContent::SetITunesMetaDataContentBuf(){
			plist_t meta_dict = NULL;
			if(ABI::zip_internal::zip_get_contents(ZIPReader::zf(), "iTunesMetadata.plist", 0, &ipa_zbuf_, &ipa_zlen_) == 0) {
				plist_t meta = plist_new_data(ipa_zbuf_,ipa_zlen_);
				if(memcmp(ipa_zbuf_, "bplist00", 8) == 0){
					plist_from_bin(ipa_zbuf_, ipa_zlen_, &meta_dict);
					free(ipa_zbuf_);
					ipa_zbuf_ = NULL;
					ipa_zlen_ = 0;
					plist_to_xml(meta_dict,&ipa_zbuf_,&ipa_zlen_);
				}
				else {
					plist_from_xml(ipa_zbuf_, ipa_zlen_, &meta_dict);
					free(ipa_zbuf_);
					ipa_zbuf_ = NULL;
					ipa_zlen_ = 0;
					plist_to_xml(meta_dict,&ipa_zbuf_,&ipa_zlen_);
				}
				if(meta_dict){
					plist_free(meta_dict);
				}
				if(meta){
					plist_free(meta);
				}
				return true;
			}
			return false;
		}
		bool IPAContent::SetInfoPlistContentBuf(){
			plist_t meta_dict = NULL;
			if(ipa_zbuf_) {
				free(ipa_zbuf_);
				ipa_zbuf_ = NULL;
				ipa_zlen_ = 0;
			}
			char filename[256] = {0};
			char* app_directory_name = NULL;
			if(ABI::zip_internal::zip_get_app_directory(ZIPReader::zf(), &app_directory_name)) {
				return false;
			}
			strcpy(filename, app_directory_name);
			free(app_directory_name);
			app_directory_name = NULL;
			strcat(filename,"Info.plist");
			if(ABI::zip_internal::zip_get_contents(ZIPReader::zf(), filename, 0, &ipa_zbuf_, &ipa_zlen_) < 0) {
				return false;
			}
			plist_t meta = plist_new_data(ipa_zbuf_, ipa_zlen_);
			if(memcmp(ipa_zbuf_, "bplist00", 8) == 0) {
				plist_from_bin(ipa_zbuf_, ipa_zlen_, &meta_dict);
				free(ipa_zbuf_);
				ipa_zbuf_ = NULL;
				ipa_zlen_ = 0;
				plist_to_xml(meta_dict,&ipa_zbuf_,&ipa_zlen_);
			}
			else{
				plist_from_xml(ipa_zbuf_, ipa_zlen_, &meta_dict);
				free(ipa_zbuf_);
				ipa_zbuf_ = NULL;
				ipa_zlen_ = 0;
				plist_to_xml(meta_dict,&ipa_zbuf_,&ipa_zlen_);
			}
			if(meta_dict){
				plist_free(meta_dict);
			}
			if(meta){
				plist_free(meta);
			}
			return true;
		}
		const char* IPAContent::ipa_buf() const{
			return ipa_zbuf_;
		}
		size_t IPAContent::ipa_len() const{
			return ipa_zlen_;
		}
	}
}