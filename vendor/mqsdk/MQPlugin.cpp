//---------------------------------------------------------------------------
//
//   MQPlugin.cpp      Copyright(C) 1999-2023, tetraface Inc.
//
//     This is an implementation code for a class based on Metasequoia 
//    SDK specification. It is necessary to add this project into the 
//    product and build it. You do not need to modify this file.
//
//    　Metasequoia SDKの仕様に基づくクラスの実装コード。特定のクラスを
//    用いる際には、このファイルをプロジェクトに加えてビルドを行う必要が
//    ある。プラグイン開発者がこのファイルの内容を変更する必要はない。
//
//---------------------------------------------------------------------------

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#if __APPLE__
#include "osx/StringUtil.h"
#include <codecvt>
#include <locale>
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFByteOrder.h>
#endif
#include "MQPlugin.h"
#include <cmath>


#if MQPLUGIN_VERSION >= 0x0240

MQXmlElement MQCXmlElement::AddChildElement(const char *name)
{
	std::string uname = MQEncoding::AnsiToUtf8(name);
	void *ptr[2];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_ADD_CHILD_ELEMENT, (void*)ptr);
	return (MQCXmlElement *)ptr[1];
}

MQXmlElement MQCXmlElement::AddChildElement(const wchar_t *name)
{
	std::string uname = MQEncoding::WideToUtf8(name);
	void *ptr[2];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_ADD_CHILD_ELEMENT, (void*)ptr);
	return (MQCXmlElement *)ptr[1];
}

BOOL MQCXmlElement::RemoveChildElement(MQXmlElement child)
{
	BOOL result = FALSE;
	void *ptr[2];
	ptr[0] = (void*)child;
	ptr[1] = &result;
	MQXmlElem_Value(this, MQXMLELEM_REMOVE_CHILD_ELEMENT, (void*)ptr);
	return result;
}

MQXmlElement MQCXmlElement::FirstChildElement(void)
{
	void *ptr[2];
	ptr[0] = NULL;
	ptr[1] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_FIRST_CHILD_ELEMENT, (void*)ptr);
	return (MQXmlElement)ptr[1];
}

MQXmlElement MQCXmlElement::FirstChildElement(const char *name)
{
	std::string uname = MQEncoding::AnsiToUtf8(name);
	void *ptr[2];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_FIRST_CHILD_ELEMENT, (void*)ptr);
	return (MQXmlElement)ptr[1];
}

MQXmlElement MQCXmlElement::FirstChildElement(const wchar_t *name)
{
	std::string uname = MQEncoding::WideToUtf8(name);
	void *ptr[2];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_FIRST_CHILD_ELEMENT, (void*)ptr);
	return (MQXmlElement)ptr[1];
}

MQXmlElement MQCXmlElement::NextChildElement(MQXmlElement child)
{
	void *ptr[3];
	ptr[0] = NULL;
	ptr[1] = child;
	ptr[2] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_NEXT_CHILD_ELEMENT, (void*)ptr);
	return (MQXmlElement)ptr[2];
}

MQXmlElement MQCXmlElement::NextChildElement(const char *name, MQXmlElement child)
{
	std::string uname = MQEncoding::AnsiToUtf8(name);
	void *ptr[3];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = child;
	ptr[2] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_NEXT_CHILD_ELEMENT, (void*)ptr);
	return (MQXmlElement)ptr[2];
}

MQXmlElement MQCXmlElement::NextChildElement(const wchar_t *name, MQXmlElement child)
{
	std::string uname = MQEncoding::WideToUtf8(name);
	void *ptr[3];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = child;
	ptr[2] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_NEXT_CHILD_ELEMENT, (void*)ptr);
	return (MQXmlElement)ptr[2];
}

MQXmlElement MQCXmlElement::GetParentElement(void)
{
	void *ptr[1];
	ptr[0] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_GET_PARENT_ELEMENT, (void*)ptr);
	return (MQXmlElement)ptr[0];
}

std::string MQCXmlElement::GetName(void)
{
	void *ptr[1];
	ptr[0] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_GET_NAME, (void*)ptr);
	return MQEncoding::Utf8ToAnsi((const char *)ptr[0]);
}

std::wstring MQCXmlElement::GetNameW(void)
{
	void *ptr[1];
	ptr[0] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_GET_NAME, (void*)ptr);
	return MQEncoding::Utf8ToWide((const char *)ptr[0]);
}

std::string MQCXmlElement::GetText(void)
{
	void *ptr[1];
	ptr[0] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_GET_TEXT, (void*)ptr);
	if (ptr[0] == NULL)
		return std::string();
	return MQEncoding::Utf8ToAnsi((const char *)ptr[0]);
}

std::wstring MQCXmlElement::GetTextW(void)
{
	void *ptr[1];
	ptr[0] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_GET_TEXT, (void*)ptr);
	if (ptr[0] == NULL)
		return std::wstring();
	return MQEncoding::Utf8ToWide((const char *)ptr[0]);
}

BOOL MQCXmlElement::GetText(std::string& result_value)
{
	void *ptr[1];
	ptr[0] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_GET_TEXT, (void*)ptr);
	if (ptr[0] == NULL){
		result_value = std::string();
		return FALSE;
	}
	result_value = MQEncoding::Utf8ToAnsi((const char *)ptr[0]);
	return TRUE;
}

BOOL MQCXmlElement::GetText(std::wstring& result_value)
{
	void *ptr[1];
	ptr[0] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_GET_TEXT, (void*)ptr);
	if (ptr[0] == NULL){
		result_value = std::wstring();
		return FALSE;
	}		
	result_value = MQEncoding::Utf8ToWide((const char *)ptr[0]);
	return TRUE;
}

std::string MQCXmlElement::GetAttribute(const char *name)
{
	std::string result_value;
	GetAttribute(name, result_value);
	return result_value;
}

std::wstring MQCXmlElement::GetAttribute(const wchar_t *name)
{
	std::wstring result_value;
	GetAttribute(name, result_value);
	return result_value;
}

BOOL MQCXmlElement::GetAttribute(const char *name, std::string& result_value)
{
	std::string uname = MQEncoding::AnsiToUtf8(name);
	void *ptr[2];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_GET_ATTRIBUTE, (void*)ptr);
	if (ptr[1] == NULL){
		result_value = std::string();
		return FALSE;
	}
	result_value = MQEncoding::Utf8ToAnsi((const char *)ptr[1]);
	return TRUE;
}

BOOL MQCXmlElement::GetAttribute(const wchar_t *name, std::wstring& result_value)
{
	std::string uname = MQEncoding::WideToUtf8(name);
	void *ptr[2];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = NULL;
	MQXmlElem_Value(this, MQXMLELEM_GET_ATTRIBUTE, (void*)ptr);
	if (ptr[1] == NULL){
		result_value = std::wstring();
		return FALSE;
	}
	result_value = MQEncoding::Utf8ToWide((const char *)ptr[1]);
	return TRUE;
}

void MQCXmlElement::SetText(const char *text)
{
	std::string utext = MQEncoding::AnsiToUtf8(text);
	void *ptr[1];
	ptr[0] = (void*)utext.c_str();
	MQXmlElem_Value(this, MQXMLELEM_SET_TEXT, (void*)ptr);
}

void MQCXmlElement::SetText(const wchar_t *text)
{
	std::string utext = MQEncoding::WideToUtf8(text);
	void *ptr[1];
	ptr[0] = (void*)utext.c_str();
	MQXmlElem_Value(this, MQXMLELEM_SET_TEXT, (void*)ptr);
}

void MQCXmlElement::SetAttribute(const char *name, const char *value)
{
	std::string uname = MQEncoding::AnsiToUtf8(name);
	std::string uvalue = MQEncoding::AnsiToUtf8(value);
	void *ptr[2];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = (void*)uvalue.c_str();
	MQXmlElem_Value(this, MQXMLELEM_SET_ATTRIBUTE, (void*)ptr);
}

void MQCXmlElement::SetAttribute(const wchar_t *name, const wchar_t *value)
{
	std::string uname = MQEncoding::WideToUtf8(name);
	std::string uvalue = MQEncoding::WideToUtf8(value);
	void *ptr[2];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = (void*)uvalue.c_str();
	MQXmlElem_Value(this, MQXMLELEM_SET_ATTRIBUTE, (void*)ptr);
}

std::string MQEncoding::Utf8ToAnsi(const char *ptr)
{
	if(ptr == NULL) return std::string();

#ifdef _WIN32
	int lenw = MultiByteToWideChar(CP_UTF8,0,(const char*)ptr,-1,NULL,0);
	wchar_t *strw = (wchar_t*)malloc(sizeof(wchar_t) * (lenw+1));
	MultiByteToWideChar(CP_UTF8,0,(const char*)ptr,-1,strw,lenw);

	int lenu = WideCharToMultiByte(CP_ACP,0,strw,-1,NULL,0,NULL,NULL);
	char *stru = (char*)malloc(lenu+1);
	WideCharToMultiByte(CP_ACP,0,strw,-1,stru,lenu,NULL,NULL);

	free(strw);

	std::string str(stru);
	free(stru);
	return str;
#else
	return WideToAnsi(Utf8ToWide(ptr).c_str());
#endif
}

std::wstring MQEncoding::Utf8ToWide(const char *ptr)
{
	if(ptr == NULL) return std::wstring();

#ifdef _WIN32
	int lenw = MultiByteToWideChar(CP_UTF8,0,(const char*)ptr,-1,NULL,0);
	wchar_t *strw = (wchar_t*)malloc(sizeof(wchar_t) * (lenw+1));
	MultiByteToWideChar(CP_UTF8,0,(const char*)ptr,-1,strw,lenw);

	std::wstring str(strw);
	free(strw);
	return str;
#endif
#if __APPLE__
	//std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> conv;
	//return conv.to_bytes(std::wstring(ptr));
	CFStringRef cfstr = CFStringCreateWithCString(kCFAllocatorDefault, ptr, kCFStringEncodingUTF8);
	CFIndex len = CFStringGetLength(cfstr);
	CFStringEncoding wchar_encoding = (CFByteOrderLittleEndian == CFByteOrderGetCurrent()) ? kCFStringEncodingUTF32LE : kCFStringEncodingUTF32BE;
	size_t capacity = CFStringGetMaximumSizeForEncoding(len, wchar_encoding);
	UInt8 *buffer = (UInt8*)calloc(capacity, sizeof(wchar_t));
	CFIndex written;
	CFStringGetBytes(cfstr, CFRangeMake(0,len), wchar_encoding, 0, false, buffer, capacity, &written);
	CFRelease(cfstr);
	std::wstring ret((const wchar_t*)buffer);
	free(buffer);
	return ret;
#endif
}

std::string MQEncoding::AnsiToUtf8(const char *ptr)
{
	if(ptr == NULL) return std::string();

#ifdef _WIN32
	int lenw = MultiByteToWideChar(CP_ACP,0,(const char*)ptr,-1,NULL,0);
	wchar_t *strw = (wchar_t*)malloc(sizeof(wchar_t) * (lenw+1));
	MultiByteToWideChar(CP_ACP,0,(const char*)ptr,-1,strw,lenw);

	int lenu = WideCharToMultiByte(CP_UTF8,0,strw,-1,NULL,0,NULL,NULL);
	char *stru = (char*)malloc(lenu+1);
	WideCharToMultiByte(CP_UTF8,0,strw,-1,stru,lenu,NULL,NULL);

	free(strw);

	std::string str(stru);
	free(stru);
	return str;
#else
	return WideToUtf8(AnsiToWide(ptr).c_str());
#endif
}

std::wstring MQEncoding::AnsiToWide(const char *ptr)
{
	if(ptr == NULL) return std::wstring();

#ifdef _WIN32
	int lenw = MultiByteToWideChar(CP_ACP,0,(const char*)ptr,-1,NULL,0);
	wchar_t *strw = (wchar_t*)malloc(sizeof(wchar_t) * (lenw+1));
	MultiByteToWideChar(CP_ACP,0,(const char*)ptr,-1,strw,lenw);

	std::wstring str(strw);
	free(strw);
	return str;
#else
	return StringUtil::CodePageStringToWide(ptr, StringUtil::kCodePage_Default);
#endif
}

std::wstring MQEncoding::AnsiToWideWithCodePage(const char *ptr, int codepage)
{
	if(ptr == NULL) return std::wstring();

#ifdef _WIN32
	int lenw = MultiByteToWideChar(codepage,0,(const char*)ptr,-1,NULL,0);
	wchar_t *strw = (wchar_t*)malloc(sizeof(wchar_t) * (lenw+1));
	MultiByteToWideChar(codepage,0,(const char*)ptr,-1,strw,lenw);

	std::wstring str(strw);
	free(strw);
	return str;
#else
	return StringUtil::CodePageStringToWide(ptr, codepage);
#endif
}

std::string MQEncoding::WideToAnsi(const wchar_t *ptr)
{
	if(ptr == NULL) return std::string();

#ifdef _WIN32
	int lenu = WideCharToMultiByte(CP_ACP,0,ptr,-1,NULL,0,NULL,NULL);
	char *stru = (char*)malloc(lenu+1);
	WideCharToMultiByte(CP_ACP,0,ptr,-1,stru,lenu,NULL,NULL);

	std::string str(stru);
	free(stru);
	return str;
#else
	return StringUtil::WideToCodePageString(ptr, StringUtil::kCodePage_Default);
#endif
}

std::string MQEncoding::WideToAnsiWithCodePage(const wchar_t *ptr, int codepage)
{
	if(ptr == NULL) return std::string();

#ifdef _WIN32
	int lenu = WideCharToMultiByte(codepage,0,ptr,-1,NULL,0,NULL,NULL);
	char *stru = (char*)malloc(lenu+1);
	WideCharToMultiByte(codepage,0,ptr,-1,stru,lenu,NULL,NULL);

	std::string str(stru);
	free(stru);
	return str;
#else
	return StringUtil::WideToCodePageString(ptr, codepage);
#endif
}

std::string MQEncoding::WideToUtf8(const wchar_t *ptr)
{
	if(ptr == NULL) return std::string();

#ifdef _WIN32
	int lenu = WideCharToMultiByte(CP_UTF8,0,ptr,-1,NULL,0,NULL,NULL);
	char *stru = (char*)malloc(lenu+1);
	WideCharToMultiByte(CP_UTF8,0,ptr,-1,stru,lenu,NULL,NULL);

	std::string str(stru);
	free(stru);
	return str;
#endif
#if __APPLE__
	CFStringEncoding wchar_encoding = (CFByteOrderLittleEndian == CFByteOrderGetCurrent()) ? kCFStringEncodingUTF32LE : kCFStringEncodingUTF32BE;
	CFStringRef cfstr = CFStringCreateWithBytes(kCFAllocatorDefault, (const UInt8*)ptr, wcslen(ptr) * sizeof(wchar_t), wchar_encoding, false);
	CFIndex len = CFStringGetLength(cfstr);
	size_t capacity = CFStringGetMaximumSizeForEncoding(len, kCFStringEncodingUTF8);
	UInt8 *buffer = (UInt8*)calloc(capacity, sizeof(UInt8));
	CFIndex written;
	CFStringGetBytes(cfstr, CFRangeMake(0,len), kCFStringEncodingUTF8, 0, false, buffer, capacity, &written);
	CFRelease(cfstr);
	std::string ret((const char*)buffer);
	free(buffer);
	return ret;
#endif
}

#endif //MQPLUGIN_VERSION >= 0x0240


#if MQPLUGIN_VERSION >= 0x0410

MQXmlDocument MQCXmlDocument::Create()
{
	void *ptr[1];
	ptr[0] = NULL;
	MQXmlDoc_Value(NULL, MQXMLDOC_CREATE, ptr);
	return (MQCXmlDocument *)ptr[0];
}

void MQCXmlDocument::DeleteThis()
{
	MQXmlDoc_Value(this, MQXMLDOC_DELETE, NULL);
}

MQXmlElement MQCXmlDocument::CreateRootElement(const char *name)
{
	std::string uname = MQEncoding::AnsiToUtf8(name);
	void *ptr[2];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = NULL;
	MQXmlDoc_Value(this, MQXMLDOC_CREATE_ROOT_ELEMENT, (void*)ptr);
	return (MQXmlElement)ptr[1];
}

MQXmlElement MQCXmlDocument::CreateRootElement(const wchar_t *name)
{
	std::string uname = MQEncoding::WideToUtf8(name);
	void *ptr[2];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = NULL;
	MQXmlDoc_Value(this, MQXMLDOC_CREATE_ROOT_ELEMENT, (void*)ptr);
	return (MQXmlElement)ptr[1];
}

MQXmlElement MQCXmlDocument::GetRootElement()
{
	void *ptr[1];
	ptr[0] = NULL;
	MQXmlDoc_Value(this, MQXMLDOC_GET_ROOT_ELEMENT, ptr);
	return (MQCXmlElement *)ptr[0];
}

BOOL MQCXmlDocument::LoadFile(const char *filename)
{
	std::wstring uname = MQEncoding::AnsiToWide(filename);
	BOOL result = FALSE;
	void *ptr[2];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = &result;
	MQXmlDoc_Value(this, MQXMLDOC_LOAD, ptr);
	return result;
}

BOOL MQCXmlDocument::LoadFile(const wchar_t *filename)
{
	BOOL result = FALSE;
	void *ptr[2];
	ptr[0] = (void*)filename;
	ptr[1] = &result;
	MQXmlDoc_Value(this, MQXMLDOC_LOAD, ptr);
	return result;
}

BOOL MQCXmlDocument::SaveFile(const char *filename)
{
	std::wstring uname = MQEncoding::AnsiToWide(filename);
	BOOL result = FALSE;
	void *ptr[2];
	ptr[0] = (void*)uname.c_str();
	ptr[1] = &result;
	MQXmlDoc_Value(this, MQXMLDOC_SAVE, ptr);
	return result;
}

BOOL MQCXmlDocument::SaveFile(const wchar_t *filename)
{
	BOOL result = FALSE;
	void *ptr[2];
	ptr[0] = (void*)filename;
	ptr[1] = &result;
	MQXmlDoc_Value(this, MQXMLDOC_SAVE, ptr);
	return result;
}


#endif


#define A(_a,_b) tmp_mtx.d[_a][_b]
#define B(_a,_b) inv_mtx.d[_a][_b]

bool MQMatrix::Inverse(MQMatrix& inv_mtx) const
{
	int i,j=0,k;
	MQMatrix tmp_mtx;

	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			tmp_mtx(i,j) = d[i][j];
			inv_mtx(i,j) = (i == j) ? 1.0f : 0.0f;
		}
	}

	float det = 1.0f;
	for(i=0; i<4; i++){
		float maxval = -1.0f;
		for(k=i; k<4; k++){
			if(fabs(tmp_mtx(k,i)) > maxval){
				maxval = fabs(tmp_mtx(k,i));
				j = k;
			}
		}
		if(maxval <= 0.0f)
			return false;
		if(j != i){
			for(k=i; k<4; k++)
				std::swap(tmp_mtx(i,k), tmp_mtx(j,k));
			for(k=0; k<4; k++)
				std::swap(inv_mtx(i,k), inv_mtx(j,k));
			det = -det;
		}
		float pivot = tmp_mtx(i,i);
		det *= pivot;
		for(k=i+1; k<4; k++)
			tmp_mtx(i,k) /= pivot;
		for(k=0; k<4; k++)
			inv_mtx(i,k) /= pivot;

		for(j=i+1; j<4; j++) {
			float t = tmp_mtx(j,i);
			for(k=i+1; k<4; k++)
				tmp_mtx(j,k) -= tmp_mtx(i,k)*t;
			for(k=0; k<4; k++)
				inv_mtx(j,k) -= inv_mtx(i,k)*t;
		}
	}

	for(i=3; i>0; i--){
		for(j=0; j<i; j++) {
			float t = tmp_mtx(j,i);
			for (k=0; k<4; k++)
				inv_mtx(j,k) -= inv_mtx(i,k)*t;
		}
	}

	return (det != 0);
}

