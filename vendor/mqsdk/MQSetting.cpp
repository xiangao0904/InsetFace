//---------------------------------------------------------------------------
//
//   MQSetting
//
//          Copyright(C) 1999-2023, tetraface Inc.
//
//	   A class for accessing .xml files used to save settings. 
//     This class supported .ini files in earlier versions. But .ini 
//    files are obsolete currently, and .xml files are substituting 
//    for them.
//
//    　Metasequoiaが設定を保存するためのxmlファイルにアクセスする
//    クラスです。
//      このクラスは以前のバージョンではiniファイルをアクセスしていま
//    したが、現在ではxmlファイルに置き換えられました。
//
//---------------------------------------------------------------------------

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include "MQPlugin.h"
#include "MQSetting.h"


// Constructor
// コンストラクタ
MQSetting::MQSetting(MQXmlElement root, const char *section_name)
{
	m_Root = root;
	m_Section = section_name;

	m_Elem = m_Root->FirstChildElement(section_name);
	if(m_Elem == NULL){
		m_Elem = m_Root->AddChildElement(section_name);
	}
}

// Destructor
// デストラクタ
MQSetting::~MQSetting()
{
}

void MQSetting::Load(const char *name, bool& value, bool default_value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		std::wstring str;
		child->GetText(str);
		if(!str.empty()){
			value = _wtoi(str.c_str()) != 0;
		}else{
			value = default_value;
		}
	}else{
		value = default_value;
	}
}

void MQSetting::Load(const char *name, int& value, int default_value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		std::wstring str;
		child->GetText(str);
		if(!str.empty()){
			value = _wtoi(str.c_str());
		}else{
			value = default_value;
		}
	}else{
		value = default_value;
	}
}

void MQSetting::Load(const char *name, unsigned int& value, unsigned int default_value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		std::wstring str;
		child->GetText(str);
		if(!str.empty()){
#ifdef _WIN32
			value = (unsigned int)_wtoi64(str.c_str());
#else
			try {
				value = (unsigned int)std::stoul(str);
			}catch(std::invalid_argument& err){
				value = default_value;
			}
#endif
		}else{
			value = default_value;
		}
	}else{
		value = default_value;
	}
}

void MQSetting::Load(const char *name, float& value, float default_value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		std::wstring str;
		child->GetText(str);
		if(!str.empty()){
			value = (float)_wtof(str.c_str());
		}else{
			value = default_value;
		}
	}else{
		value = default_value;
	}
}

void MQSetting::Load(const char *name, double& value, double default_value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		std::wstring str;
		child->GetText(str);
		if(!str.empty()){
			value = (float)_wtof(str.c_str());
		}else{
			value = default_value;
		}
	}else{
		value = default_value;
	}
}

void MQSetting::Load(const char *name, std::string& utf8_value, const std::string& default_value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		utf8_value = child->GetText();
	}else{
		utf8_value = default_value;
	}
}

void MQSetting::Load(const char *name, std::wstring& value, const std::wstring& default_value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		child->GetText(value);
	}else{
		value = default_value;
	}
}

void MQSetting::Save(const char *name, const bool& value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		m_Elem->RemoveChildElement(child);
	}

	child = m_Elem->AddChildElement(name);
	child->SetText(value ? L"1" : L"0");
}

void MQSetting::Save(const char *name, const int& value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		m_Elem->RemoveChildElement(child);
	}

#ifdef _WIN32
	wchar_t buf[64];
	swprintf_s(buf, L"%d", value);
#else
	char buf[64];
	sprintf(buf, "%d", value);
#endif

	child = m_Elem->AddChildElement(name);
	child->SetText(buf);
}

void MQSetting::Save(const char *name, const unsigned int& value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		m_Elem->RemoveChildElement(child);
	}

#ifdef _WIN32
	wchar_t buf[64];
	swprintf_s(buf, L"%u", value);
#else
	char buf[64];
	sprintf(buf, "%u", value);
#endif

	child = m_Elem->AddChildElement(name);
	child->SetText(buf);
}

void MQSetting::Save(const char *name, const float& value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		m_Elem->RemoveChildElement(child);
	}

#ifdef _WIN32
	wchar_t buf[64];
	swprintf_s(buf, L"%e", value);
#else
	char buf[64];
	sprintf(buf, "%e", value);
#endif

	child = m_Elem->AddChildElement(name);
	child->SetText(buf);
}

void MQSetting::Save(const char *name, const double& value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		m_Elem->RemoveChildElement(child);
	}

#ifdef _WIN32
	wchar_t buf[64];
	swprintf_s(buf, L"%e", value);
#else
	char buf[64];
	sprintf(buf, "%e", value);
#endif

	child = m_Elem->AddChildElement(name);
	child->SetText(buf);
}

void MQSetting::Save(const char *name, const char *utf8_value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		m_Elem->RemoveChildElement(child);
	}

	child = m_Elem->AddChildElement(name);
	child->SetText(utf8_value);
}

void MQSetting::Save(const char *name, const std::string& utf8_value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		m_Elem->RemoveChildElement(child);
	}

	child = m_Elem->AddChildElement(name);
	child->SetText(utf8_value.c_str());
}

void MQSetting::Save(const char *name, const std::wstring& value)
{
	MQXmlElement child = m_Elem->FirstChildElement(name);
	if(child != NULL){
		m_Elem->RemoveChildElement(child);
	}

	child = m_Elem->AddChildElement(name);
	child->SetText(value.c_str());
}

