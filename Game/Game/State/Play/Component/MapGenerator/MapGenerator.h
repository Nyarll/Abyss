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
public:
	enum MapState
	{
		None = 0,
		Floor,



		EntityPlaced
	};

private:
	entt::DefaultRegistry* registry;

	static const int kMapSize;

	std::vector<std::vector<int>>			m_mapData;
	std::vector<std::vector<Entity>>		m_mapEntitys;

	std::vector<std::vector<Entity>>		m_mapItems;

	std::vector<Entity>						m_activeMapEntitys;
	std::vector<Entity>						m_activeItems;

	std::vector<std::vector<int>>			m_entitySpawnMapPointData;

	std::vector<std::vector<Entity>>		m_chunks;

	// <部屋の最小・最大サイズ>
	// <横幅>
	static const int kRoomMinWidth;
	static const int kRoomMaxWidth;
	// <縦幅>
	static const int kRoomMinHeight;
	static const int kRoomMaxHeight;

	// <部屋の最小・最大数>
	static const int kRoomCountMin;
	static const int kRoomCountMax;

	// <道の交差点の数>
	static const int kMeetPointCount;

public:
	MapGenerator() :registry(nullptr) {}
	~MapGenerator() = default;

	void Initialize(GameContext& context, entt::DefaultRegistry* _pRegistry);

	void Generate();

	// <平らなマップ>
	void Plain();

	std::vector<std::vector<int>>& GetEntitySpawnMapData();

private:

	void InitializeChunks(GameContext& context, float scale);
	void InitializeFloors(GameContext& context, float scale);
	void InitializeItems(GameContext& context, float scale);

	void CreateMapData();
	bool CreateRoomData(int roomWidth, int roomHeight, int roomPointX, int roomPointY);
	void CreateRoadData(int roadStartPointX, int roadStartPointY, int meetPointX, int meetPointY);

	void MapDataClear();
	void MapDataFillNone();
	void ReflectMapDataToEntitys();
};

#endif