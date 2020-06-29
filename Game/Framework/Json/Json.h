#pragma once

// <class name		: Json>
// <update date		: 2020 / 06 / 29>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef JSON_DEFINED
#define JSON_DEFINED

#include <fstream>
#include <picojson.h>

// <Jsonファイルを取り扱うクラス>
class Json
{
private:
	std::ifstream m_ifs;
	picojson::value m_value;

public:
	Json();
	~Json();

	void Load(const std::string& file_name);

	template <typename Type>
	inline Type GetAs(std::string path)
	{
		return JsonImport::get_as<Type>(JsonImport::get_value(m_value, path));
	}
};

#endif