#include "ABI/zip_internal/zip_object_reader.h"

namespace ABI{
	namespace zip_internal{
		ZIPReader::ZIPReader(const char* filename){
			set_zf(NULL);
			Open(filename);
		}
		ZIPReader::~ZIPReader(){
			if(zf()!=NULL){
				zip_unchange_all(zf());
				zip_close(zf());
				set_zf(NULL);
			}
		}
		void ZIPReader::Open(const char* filename){
			if(filename!=NULL){
				int errp = 0;
				set_zf(zip_open(filename, 0, &errp));
			}
		}
		zip* ZIPReader::zf()const{
			return zf_;
		}
		void ZIPReader::set_zf(struct zip* z){
			zf_ = z;
		}
	}
}