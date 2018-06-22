#include "ABI/zip_internal/zip_internal_impl.h"
#include <cstdio>
#include "ABI/thirdparty/glog/logging.h"
namespace ABI{
	namespace zip_internal{
		int zip_get_contents(struct zip *zf, const char *filename, int locate_flags, char **buffer, uint32_t *len){
			struct zip_stat zs;
			struct zip_file *zfile;
			int zindex = zip_name_locate(zf, filename, locate_flags);
			*buffer = NULL;
			*len = 0;
			if (zindex < 0) {
				LOG(ERROR)<<"ERROR: could not locate "<<filename<<" in archive!"<<std::endl;
				return -1;
			}
			zip_stat_init(&zs);
			if (zip_stat_index(zf, zindex, 0, &zs) != 0) {
				LOG(ERROR)<<"ERROR: zip_stat_index '"<<filename<<"' failed!"<<std::endl;
				return -2;
			}
			if (zs.size > 1024*1024*1024) {/*MB*KB*B==GB*/
				LOG(ERROR)<<"ERROR: file '"<<filename<<"' is too large!"<<std::endl;
				return -3;
			}
			zfile = zip_fopen_index(zf, zindex, 0);
			if (!zfile) {
				LOG(ERROR)<<"ERROR: zip_fopen '"<<filename<<"' failed!"<<std::endl;
				return -4;
			}
			*buffer = (char *)malloc(zs.size);
			if (zs.size > LLONG_MAX || zip_fread(zfile, *buffer, zs.size) != (zip_int64_t)zs.size) {
				LOG(ERROR)<<"ERROR: zip_fread "<<(uint64_t)zs.size<<" bytes from '"<<filename<<"'"<<std::endl;
				free(*buffer);
				*buffer = NULL;
				zip_fclose(zfile);
				return -5;
			}
			*len = zs.size;
			zip_fclose(zfile);
			return 0;
		}
		int zip_get_app_directory(struct zip* zf, char** path){
			try{
				int i = 0;
				int c = zip_get_num_files(zf);
				int len = 0;
				const char* name = NULL;

				/* look through all filenames in the archive */
				do {
					/* get filename at current index */
					name = zip_get_name(zf, i++, 0);
					if (name != NULL) {
						/* check if we have a "Payload/.../" name */
						len = strlen(name);
						if (!strncmp(name, "Payload/", 8) && (len > 8)) {
							/* locate the second directory delimiter */
							const char* p = name + 8;
							do {
								if (*p == '/') {
									break;
								}
							} while(p++ != NULL);

							/* try next entry if not found */
							if (p == NULL)
								continue;

							len = p - name + 1;

							if (*path != NULL) {
								free(*path);
								*path = NULL;
							}

							/* allocate and copy filename */
							*path = (char*)malloc(len + 1);
							strncpy(*path, name, len);

							/* add terminating null character */
							char* t = *path + len;
							*t = '\0';
							break;
						}
					}
				} while(i < c);

				/* check if the path actually exists */
				int zindex = zip_name_locate(zf, *path, 0);
				if (zindex < 0) {
					return -1;
				}

				return 0;
			}
			catch(...){
				return -1;
			}
		}
	}
}