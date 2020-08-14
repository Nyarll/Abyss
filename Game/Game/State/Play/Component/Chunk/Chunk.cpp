#include "Chunk.h"

Chunk::Chunk(float size)
{
	m_size = size;
}

float Chunk::GetSize()
{
	return m_size;
}
