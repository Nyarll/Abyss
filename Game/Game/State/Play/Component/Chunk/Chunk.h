#pragma once

// <class name		: Chunk>
// <update date		: 2020 / 07 / 02>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef CHUNK_DEFINED
#define CHUNK_DEFINED

class Chunk
{
private:
	float m_size;
	std::vector<Entity>		m_child;

public:
	Chunk(float size = 8.f);

	float GetSize();

	const std::vector<Entity>& GetChild()
	{
		return m_child;
	}

	void RegisterChild(const Entity& entity)
	{
		m_child.push_back(entity);
	}
};

#endif