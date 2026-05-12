#ifndef INSETFACE_LANGUAGE_H
#define INSETFACE_LANGUAGE_H

#include <map>
#include <string>

class MLanguage
{
private:
	std::map<std::string, std::wstring> Data;
	std::wstring mLanguage;

public:
	MLanguage();
	~MLanguage();

	bool Contains() const { return !Data.empty(); }
	std::wstring GetLanguage() const { return mLanguage; }
	bool Load(const std::wstring& language, const std::wstring& filename);
	const wchar_t* Search(const char* key) const;
};

#endif
