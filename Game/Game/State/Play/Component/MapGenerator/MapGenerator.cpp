
#include "MapGenerator.h"

#include "../../../../../Framework/Framework.h"

#include "../Chunk/Chunk.h"

const int MapGenerator::MapSize = 64;

void MapGenerator::Initialize(GameContext& context, entt::DefaultRegistry* _pRegistry)
{
	registry = _pRegistry;

	const float chunk_scale = 16;
	for (int i = 0; i < (MapSize / chunk_scale); i++)
	{
		m_chunks.push_back(std::vector<Entity>());
		for (int j = 0; j < (MapSize / chunk_scale); j++)
		{
			auto entity = registry->create();
			
			registry->assign<Chunk>(entity, chunk_scale);

			float x = (chunk_scale / 2.f) + ((float)j * chunk_scale);
			float z = (chunk_scale / 2.f) + ((float)i * chunk_scale);

			auto& obj = registry->assign<GameObject>(entity, registry, entity);
			obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3(x, 0, z);
			obj.Activate();

			auto& collider = registry->assign<Collider>(entity, ColliderType::Box, chunk_scale);
			collider.SetPosition(DirectX::SimpleMath::Vector3(x, 0, z));

			auto& renderer = registry->assign<PrimitiveRenderer>(entity);
			renderer.SetModel(context.Get<PrimitiveModelList>().GetModel(PrimitiveModelList::Cube));
			renderer.SetModelOption(DirectX::Colors::Red, true);

			m_chunks[i].push_back(entity);
		}
	}

	for (int z = 0; z < MapSize; z++)
	{
		m_mapEntitys.push_back(std::vector<Entity>());
		for (int x = 0; x < MapSize; x++)
		{
			auto entity = registry->create();
			auto parent = m_chunks[z / chunk_scale][x / chunk_scale];

			auto& obj = registry->assign<GameObject>(entity, registry, entity);
			auto& parentPos = registry->get<GameObject>(parent).GetTransform()->localPosition;
			obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3((float)x - parentPos.x, -1.f, (float)z - parentPos.z);
			obj.SetParent(parent);
			obj.Deactivate();
			obj.DeactivateRendering();

			auto& renderer = registry->assign<PrimitiveRenderer>(entity);
			renderer.SetModel(context.Get<PrimitiveModelList>().GetModel(PrimitiveModelList::ID::Cube));
			renderer.SetModelOption(DirectX::Colors::White, false, context.Get<TextureManager>().GetTexture(TextureID::Floor));

			auto& chunk = registry->get<Chunk>(parent);
			chunk.RegisterChild(entity);

			m_mapEntitys[z].push_back(entity);
		}
	}
}

void MapGenerator::Generate()
{
	MapDataClear();
	MapDataFillNone();
	CreateMapData();
	ReflectMapDataToEntitys();
}

void MapGenerator::Plain()
{
	MapDataClear();
	for (int z = 0; z < MapSize; z++)
	{
		m_mapData.push_back(std::vector<int>());
		for (int x = 0; x < MapSize; x++)
		{
			m_mapData[z].push_back((int)MapState::Floor);
		}
	}
	ReflectMapDataToEntitys();
}

std::vector<std::vector<int>>& MapGenerator::GetEntitySpawnMapData()
{
	return m_entitySpawnMapPointData;
}

void MapGenerator::CreateMapData()
{
	Random random;

	int roomCount = random.Range(roomCountMin, roomCountMax);

	std::vector<int> meetPointsX;
	std::vector<int> meetPointsY;
	for (int i = 0; i < meetPointCount; i++)
	{
		meetPointsX.push_back(random.Range(MapSize / 4, MapSize * 3 / 4));
		meetPointsY.push_back(random.Range(MapSize / 4, MapSize * 3 / 4));
		m_mapData[meetPointsY[i]][meetPointsX[i]] = (int)MapState::Floor;
	}

	for (int i = 0; i < roomCount; i++)
	{
		int roomWidth = random.Range(roomMinWidth, roomMaxWidth);
		int roomHeight = random.Range(roomMinHeight, roomMaxHeight);
		int roomPointX = random.Range(2, MapSize - roomMaxWidth - 2);
		int roomPointY = random.Range(2, MapSize - roomMaxWidth - 2);

		int roadStartPointX = random.Range(roomPointX, roomPointX + roomWidth);
		int roadStartPointY = random.Range(roomPointY, roomPointY + roomHeight);

		bool isRoad = this->CreateRoomData(roomWidth, roomHeight, roomPointX, roomPointY);
		if (!isRoad)
		{
			this->CreateRoadData(roadStartPointX, roadStartPointY,
				meetPointsX[random.Range(0, meetPointsX.size() - 1)],
				meetPointsY[random.Range(0, meetPointsY.size() - 1)]
			);
		}
	}
}

bool MapGenerator::CreateRoomData(int roomWidth, int roomHeight, int roomPointX, int roomPointY)
{
	bool beCreateRoad = false;
	for (int y = 0; y < roomHeight; y++)
	{
		for (int x = 0; x < roomWidth; x++)
		{
			if (!m_mapData[roomPointY + y][roomPointX + x])
			{
				m_mapData[roomPointY + y][roomPointX + x] = (int)MapState::Floor;
			}
			else
			{
				beCreateRoad = true;
			}
		}
	}
	return beCreateRoad;
}

void MapGenerator::CreateRoadData(int roadStartPointX, int roadStartPointY, int meetPointX, int meetPointY)
{
	bool isRight = false;
	if (roadStartPointX > meetPointX)
	{
		isRight = true;
	}

	bool isUnder = true;
	if (roadStartPointY > meetPointY)
	{
		isUnder = false;
	}
	Random random;
	if (random.Range(0, 2) == 0)
	{
		while (roadStartPointX != meetPointX)
		{
			m_mapData[roadStartPointY][roadStartPointX] = (int)MapState::Floor;
			if (isRight)
			{
				roadStartPointX--;
			}
			else
			{
				roadStartPointX++;
			}
		}
		while (roadStartPointY != meetPointY)
		{
			m_mapData[roadStartPointY][roadStartPointX] = (int)MapState::Floor;
			if (isUnder)
			{
				roadStartPointY++;
			}
			else
			{
				roadStartPointY--;
			}
		}
	}
	else
	{
		while (roadStartPointX != meetPointX)
		{
			m_mapData[roadStartPointY][roadStartPointX] = (int)MapState::Floor;
			if (isRight)
			{
				roadStartPointX--;
			}
			else
			{
				roadStartPointX++;
			}
		}
		while (roadStartPointY != meetPointY)
		{
			m_mapData[roadStartPointY][roadStartPointX] = (int)MapState::Floor;
			if (isUnder)
			{
				roadStartPointY++;
			}
			else
			{
				roadStartPointY--;
			}
		}
	}
}

void MapGenerator::MapDataClear()
{
	// <配列内をすべて消去>
	if (m_mapData.size() > 0)
	{
		for (auto& data : m_mapData)
		{
			data.clear();
		}
		m_mapData.clear();
	}
	// <非アクティブにしておく>
	if (m_activeMapEntitys.size() > 0)
	{
		for (auto& entity : m_activeMapEntitys)
		{
			auto& obj = registry->get<GameObject>(entity);
			obj.Deactivate();
			obj.DeactivateRendering();

			//registry->remove<Collider>(entity);
		}
		m_activeMapEntitys.clear();
	}
}

void MapGenerator::MapDataFillNone()
{
	for (int z = 0; z < MapSize; z++)
	{
		m_mapData.push_back(std::vector<int>());
		for (int x = 0; x < MapSize; x++)
		{
			m_mapData[z].push_back((int)MapState::None);
		}
	}
}

void MapGenerator::ReflectMapDataToEntitys()
{
	m_entitySpawnMapPointData = m_mapData;

	for (int z = 0; z < m_mapData.size(); z++)
	{
		for (int x = 0; x < m_mapData[z].size(); x++)
		{
			if (m_mapData[z][x] == (int)MapState::Floor)
			{
				auto entity = m_mapEntitys[z][x];
				registry->get<GameObject>(entity).Activate();
				registry->get<GameObject>(entity).ActivateRendering();
				m_activeMapEntitys.push_back(entity);
			}
		}
	}

	for (auto& entity : m_activeMapEntitys)
	{
		//auto& collider = registry->assign<Collider>(entity, ColliderType::Box, 1.f);
		//collider.SetPosition(registry->get<GameObject>(entity).GetPosition());
	}
}
