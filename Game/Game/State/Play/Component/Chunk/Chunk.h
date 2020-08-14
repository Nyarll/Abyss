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
	std::vector<Entity>		m_childBlocks;
	std::vector<Entity>		m_childItems;

public:
	Chunk(float size = 8.f);

	float GetSize();

	const std::vector<Entity>& GetChildBlocks()
	{
		return m_childBlocks;
	}

	void RegisterChildBlocks(const Entity& entity)
	{
		m_childBlocks.push_back(entity);
	}

	const std::vector<Entity>& GetChildItems()
	{
		return m_childItems;
	}

	void RegisterChildItems(const Entity& entity)
	{
		m_childItems.push_back(entity);
	}
};

#endif