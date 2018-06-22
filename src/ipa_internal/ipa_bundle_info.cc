#include "ABI/ipa_internal/ipa_bundle_info.h"
#include <sstream>
#include "ABI/ipa_internal/ipa_content.h"
#include "ABI/base/string/string_conv.h"
#include <plist/plist.h>

namespace ABI{
	namespace ipa_internal{
		void XmlElementArray(xmlNode* parent_node,const char* key,const char* s2_key,const char* s3_key,const char* name,std::vector<std::string>& text){
			xmlNode *child_node = NULL;
			for(child_node=parent_node;child_node;child_node=child_node->next){
				if(child_node->type==XML_ELEMENT_NODE&&!xmlStrcmp(child_node->name,(const xmlChar*)key)){
					const char* xml_text = reinterpret_cast<const char*>(xmlNodeGetContent(child_node));
					std::string attr_name = xml_text;
					free((void*)xml_text);
					if(attr_name==name){
						XmlElementArray(child_node,s2_key,s3_key,s3_key,name,text);
						break;
					}
					else{
						if(key!=NULL&&s2_key!=NULL&&s3_key!=NULL&&std::string(key)=="array"&&std::string(s2_key)==s3_key){
							XmlElementArray(child_node->children,s2_key,NULL,s3_key,name,text);
							break;
						}
						else if(key!=NULL&&s3_key!=NULL&&std::string(key)==s3_key&&s2_key==NULL){
							text.push_back(attr_name);
						}
					}
				}
				XmlElementArray(child_node->children,key,s2_key,s3_key,name,text);
			}
		}
		void XmlElementName(xmlNode* parent_node,const char* key,const char* s2_key,const char* name,std::string& text){
			xmlNode *child_node = NULL;
			for(child_node=parent_node;child_node;child_node=child_node->next){
				if(child_node->type==XML_ELEMENT_NODE&&!xmlStrcmp(child_node->name,(const xmlChar*)key)){
					const char* xml_text = reinterpret_cast<const char*>(xmlNodeGetContent(child_node));
					std::string attr_name = xml_text;
					free((void*)xml_text);
					if(attr_name==name){
						XmlElementName(child_node,s2_key,NULL,name,text);
						break;
					}
					else{
						if(std::string(key)=="string"||(std::string(key)==reinterpret_cast<const char*>(child_node->name))&&s2_key==NULL){
							text = attr_name;
							break;
						}
					}
				}
				XmlElementName(child_node->children,key,s2_key,name,text);
			}
		}
		BundleInfo::BundleInfo(){
			initialize();
		}
		BundleInfo::BundleInfo(const char* app_name){
			initialize();
			IPAContent content(app_name);
			content.SetITunesMetaDataContentBuf();
			bundle_text_ = content.ipa_buf();
			SetBundleInfo();
			content.SetInfoPlistContentBuf();
			bundle_text_ = content.ipa_buf();
			SetBundleInfoPlistInfo();
		}
		BundleInfo::~BundleInfo(){
			initialize();
		}
		void BundleInfo::iTunesMetadata_plist(const char* text){
			bundle_text_ = text;
			SetBundleInfo();
		}
		void BundleInfo::Info_plist(const char* text){
			bundle_text_ = text;
			SetBundleInfoPlistInfo();
		}
		std::string BundleInfo::cf_bundle_identifier() const{
			return cf_bundle_identifier_;
		}
		std::string BundleInfo::cf_bundle_version() const{
			return cf_bundle_version_;
		}
		std::string BundleInfo::cf_bundle_signature() const{
			return cf_bundle_signature_;
		}
		std::string BundleInfo::cf_bundle_display_name() const{
			return cf_bundle_display_name_;
		}
		std::string BundleInfo::minimum_os_version() const{
			return minimum_os_version_;
		}
		std::string BundleInfo::ui_required_device_capabilities() const{
			return ui_required_device_capabilities_;
		}
		std::vector<std::string> BundleInfo::cf_bundle_supported_platforms() const{
			return cf_bundle_supported_platforms_;
		}
		std::vector<std::string> BundleInfo::ui_device_family() const{
			// 		1	The app runs on iPhone and iPod touch devices.
			// 		2	The app runs on iPad devices.
			return ui_device_family_;
		}
		std::vector<std::string> BundleInfo::cf_bundle_icon_files() const{
			return cf_bundle_icon_files_;
		}
		std::string BundleInfo::bundle_text() const{
			return bundle_text_;
		}
		std::string BundleInfo::apple_id() const{
			return apple_id_;
		}
		std::string BundleInfo::file_extension() const{
			return file_extension_;
		}
		void BundleInfo::SetBundleInfo(){
			xmlDocPtr doc = xmlParseMemory(bundle_text_.c_str(),bundle_text_.length());
			XmlElementName(xmlDocGetRootElement(doc),"key","string","appleId",apple_id_);
			XmlElementName(xmlDocGetRootElement(doc),"key","string","fileExtension",file_extension_);
			xmlFreeDoc(doc);
		}
		void BundleInfo::SetBundleInfoPlistInfo(){
			xmlDocPtr doc = xmlParseMemory(bundle_text_.c_str(),bundle_text_.length());
			XmlElementName(xmlDocGetRootElement(doc),"key","string","CFBundleIdentifier",cf_bundle_identifier_);
			XmlElementName(xmlDocGetRootElement(doc),"key","string","CFBundleVersion",cf_bundle_version_);
			XmlElementName(xmlDocGetRootElement(doc),"key","string","CFBundleSignature",cf_bundle_signature_);
			XmlElementName(xmlDocGetRootElement(doc),"key","string","CFBundleDisplayName",cf_bundle_display_name_);
			XmlElementName(xmlDocGetRootElement(doc),"key","string","MinimumOSVersion",minimum_os_version_);
			XmlElementName(xmlDocGetRootElement(doc),"key","array","UIRequiredDeviceCapabilities",ui_required_device_capabilities_);
			XmlElementArray(xmlDocGetRootElement(doc),"key","array","string","CFBundleSupportedPlatforms",cf_bundle_supported_platforms_);
			XmlElementArray(xmlDocGetRootElement(doc),"key","array","integer","UIDeviceFamily",ui_device_family_);
			XmlElementArray(xmlDocGetRootElement(doc),"key","array","string","CFBundleIconFiles",cf_bundle_icon_files_);
			xmlFreeDoc(doc);
		}
		void BundleInfo::initialize(){
			bundle_text_.resize(0);
			cf_bundle_identifier_.resize(0);
			cf_bundle_version_.resize(0);
			cf_bundle_signature_.resize(0);
			cf_bundle_display_name_.resize(0);
			minimum_os_version_.resize(0);
			ui_required_device_capabilities_.resize(0);
			cf_bundle_supported_platforms_.resize(0);
			ui_device_family_.resize(0);
			cf_bundle_icon_files_.resize(0);
			apple_id_.resize(0);
			file_extension_.resize(0);
		}
	}
}