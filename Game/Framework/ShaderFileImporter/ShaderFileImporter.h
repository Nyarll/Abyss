#pragma once

// <class name		: ShaderFileImporter>
// <update date		: 2020 / 05 / 26>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef SHADERFILEIMPORTER_DEFINED
#define SHADERFILEIMPORTER_DEFINED

#include <memory>

class ShaderFileImporter
{
public:
	static ShaderFileImporter LoadFile(const wchar_t* file_name);

	ShaderFileImporter();
	ShaderFileImporter(ShaderFileImporter&& in);

	char* GetData() { return m_data.get(); }
	unsigned int GetSize() { return m_size; }

protected:
	std::unique_ptr<char[]>	m_data;
	unsigned int	m_size;
};

#endif