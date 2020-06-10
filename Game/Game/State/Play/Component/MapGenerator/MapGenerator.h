#pragma once

// <class name		: MapGenerator>
// <update date		: 2020 / 06 / 10>
// <author			: Nyarll>
// <GitHub			: https://github.com/Nyarll >

#ifndef MAPGENERATOR_DEFINED
#define MAPGENERATOR_DEFINED

class GameContext;

class MapGenerator
{
private:
	enum MapState
	{
		None = 0,
		Floor,
	};

private:
	entt::DefaultRegistry* registry;

	int MapSize = 50;

	// <生成されるマップデータ>
	std::vector<std::vector<int>>			m_mapData;
	// <ワールドに存在するマップエンティティ>
	std::vector<std::vector<Entity>>		m_mapEntitys;
	// <アクティブなマップエンティティ>
	std::vector<Entity>						m_activeEntitys;

	int roomMinWidth = 5;
	int roomMaxWidth = 10;

	int roomMinHeight = 5;
	int roomMaxHeight = 10;

	int roomCountMin = 5;
	int roomCountMax = 10;

	int meetPointCount = 1;

public:
	MapGenerator() :registry(nullptr) {}
	~MapGenerator() = default;

	// <初期化>
	void Initialize(GameContext& context, entt::DefaultRegistry* _pRegistry);

	// <マップ生成>
	void Generate();

private:
	// <マップデータを生成>
	void CreateSpaceData();
	// <部屋を生成>
	bool CreateRoomData(int roomWidth, int roomHeight, int roomPointX, int roomPointY);
	// <通路を生成>
	void CreateRoadData(int roadStartPointX, int roadStartPointY, int meetPointX, int meetPointY);
	// <マップをクリア>
	void Clear();
	// <壁で埋める>
	void Fill();
	// <生成されたデータを元にエンティティをアクティブにする>
	void Activate();
};

#endif