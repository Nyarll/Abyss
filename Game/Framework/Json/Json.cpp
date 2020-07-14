#include "Json.h"
#include "JsonImport.h"

Json::Json()
{
}

Json::~Json()
{
	m_ifs.close();
}

void Json::Load(const std::string & file_name)
{
	m_ifs = std::ifstream(file_name);
	assert(m_ifs && "null !");

	m_ifs >> m_value;
}
