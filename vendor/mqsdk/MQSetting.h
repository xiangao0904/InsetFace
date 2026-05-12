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

#ifndef _MQSETTING_H_
#define _MQSETTING_H_

#include <string>

// Class for accessing a setting file
// 設定ファイルへのアクセス関数
class MQSetting
{
public:
	// Constructor
	// コンストラクタ
	MQSetting(MQXmlElement root, const char *section_name);

	// Destructor
	// デストラクタ
	virtual ~MQSetting();

	// Load the specified item with a name
	// 名前指定された項目の読み込み
	void Load(const char *name, bool& value, bool default_value=false);
	void Load(const char *name, int& value, int default_value=0);
	void Load(const char *name, unsigned int& value, unsigned int default_value=0);
	void Load(const char *name, float& value, float default_value=0.0f);
	void Load(const char *name, double& value, double default_value=0.0);
	void Load(const char *name, std::string& utf8_value, const std::string& default_value="");
	void Load(const char *name, std::wstring& value, const std::wstring& default_value=L"");

	// Save the specified item with a name
	// 名前指定された項目の出力
	void Save(const char *name, const bool& value);
	void Save(const char *name, const int& value);
	void Save(const char *name, const unsigned int& value);
	void Save(const char *name, const float& value);
	void Save(const char *name, const double& value);
	void Save(const char *name, const char *utf8_value);
	void Save(const char *name, const std::string& utf8_value);
	void Save(const char *name, const std::wstring& value);

private:
	MQXmlElement m_Root;
	MQXmlElement m_Elem;
	std::string m_Section;
};


#endif //_MQSETTING_H_
