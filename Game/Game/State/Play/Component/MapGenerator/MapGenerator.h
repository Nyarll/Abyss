#pragma once

// <class name		: MapGenerator>
// <update date		: 2020 / 06 / 10>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef MAPGENERATOR_DEFINED
#define MAPGENERATOR_DEFINED

#define MapSize 50

class MapGenerator
{
private:
	entt::DefaultRegistry* registry;

	// <生成されるマップデータ>
	std::array<std::array<int, MapSize>, MapSize>			m_mapData;
	// <ワールドに存在するマップエンティティ>
	std::array<std::array<Entity, MapSize>, MapSize>		m_mapEntitys;
	// <アクティブなマップエンティティ>
	std::vector<Entity>										m_activeEntitys;

	const int roomMinWidth = 5;
	const int roomMaxWidth = 10;

	const int roomMinHeight = 5;
	const int roomMaxHeight = 10;

	const int roomCountMin = 5;
	const int roomCountMax = 10;

	const int meetPointCount = 1;

public:
};

#endif