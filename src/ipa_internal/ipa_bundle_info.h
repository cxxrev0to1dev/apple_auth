#ifndef ABI_IPA_INTERNAL_IPA_BUNDLE_INFO_H_
#define ABI_IPA_INTERNAL_IPA_BUNDLE_INFO_H_
//////////////////////////////////////////////////////////////////////////
#include <string>
#include <vector>
#include <libxml/parser.h>
#include <libxml/tree.h>
//////////////////////////////////////////////////////////////////////////
namespace ABI{
	namespace ipa_internal{
		void XmlElementArray(xmlNode* parent_node,const char* key,const char* s2_key,const char* s3_key,const char* name,std::vector<std::string>& text);
		void XmlElementName(xmlNode* parent_node,const char* key,const char* s2_key,const char* name,std::string& text);
		class BundleInfo{
		public:
			BundleInfo();
			explicit BundleInfo(const char* app_name);
			virtual ~BundleInfo();
			void iTunesMetadata_plist(const char* text);
			void Info_plist(const char* text);
			std::string cf_bundle_identifier() const;
			std::string cf_bundle_version() const;
			std::string cf_bundle_signature() const;
			std::string cf_bundle_display_name() const;
			std::string minimum_os_version() const;
			std::string ui_required_device_capabilities() const;
			std::vector<std::string> cf_bundle_supported_platforms() const;
			std::vector<std::string> ui_device_family() const;
			std::vector<std::string> cf_bundle_icon_files() const;
			std::string bundle_text() const;
			std::string apple_id() const;
			std::string file_extension() const;
		private:
			void SetBundleInfo();
			void SetBundleInfoPlistInfo();
			void initialize();
			std::string bundle_text_;
			std::string cf_bundle_identifier_;
			std::string cf_bundle_version_;
			std::string cf_bundle_signature_;
			std::string cf_bundle_display_name_;
			std::string minimum_os_version_;
			std::string ui_required_device_capabilities_;
			std::vector<std::string> cf_bundle_supported_platforms_;
			std::vector<std::string> ui_device_family_;
			std::vector<std::string> cf_bundle_icon_files_;
			std::string apple_id_;
			std::string file_extension_;
		};
	}
}
//////////////////////////////////////////////////////////////////////////
#endif