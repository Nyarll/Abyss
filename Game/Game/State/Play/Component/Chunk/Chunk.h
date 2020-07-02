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

public:
	Chunk(float size = 8.f);

	float GetSize();
};

#endif