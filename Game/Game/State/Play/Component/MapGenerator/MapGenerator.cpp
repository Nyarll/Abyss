
#include "MapGenerator.h"

#include "../../../../../Framework/Framework.h"

#include "../Chunk/Chunk.h"
#include "../Item/Item.h"

const int MapGenerator::kMapSize = 64;

const int MapGenerator::kRoomMinWidth = 8;
const int MapGenerator::kRoomMaxWidth = 10;
const int MapGenerator::kRoomMinHeight = 8;
const int MapGenerator::kRoomMaxHeight = 10;
const int MapGenerator::kRoomCountMin = 5;
const int MapGenerator::kRoomCountMax = 10;
const int MapGenerator::kMeetPointCount = 1;

void MapGenerator::Initialize(GameContext& context, entt::DefaultRegistry* _pRegistry)
{
	registry = _pRegistry;

	const float chunk_scale = 4;

	InitializeChunks(context, chunk_scale);
	InitializeFloors(context, chunk_scale);
	InitializeItems(context, chunk_scale);
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
	for (int z = 0; z < kMapSize; z++)
	{
		m_mapData.push_back(std::vector<int>());
		for (int x = 0; x < kMapSize; x++)
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

void MapGenerator::InitializeChunks(GameContext & context, float scale)
{
	for (int i = 0; i < (kMapSize / scale); i++)
	{
		m_chunks.push_back(std::vector<Entity>());
		for (int j = 0; j < (kMapSize / scale); j++)
		{
			auto entity = registry->create();

			registry->assign<Chunk>(entity, scale);

			float x = (scale / 2.f) + ((float)j * scale);
			float z = (scale / 2.f) + ((float)i * scale);

			auto& obj = registry->assign<GameObject>(entity, registry, entity);
			obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3(x, 0, z);
			obj.Activate();

			auto& collider = registry->assign<Collider>(entity, ColliderType::Box, scale / 2);
			collider.SetPosition(DirectX::SimpleMath::Vector3(x, 0, z));

			m_chunks[i].push_back(entity);
		}
	}
}

void MapGenerator::InitializeFloors(GameContext & context, float scale)
{
	for (int z = 0; z < kMapSize; z++)
	{
		m_mapEntitys.push_back(std::vector<Entity>());
		for (int x = 0; x < kMapSize; x++)
		{
			auto entity = registry->create();
			auto parent = m_chunks[z / scale][x / scale];

			auto& obj = registry->assign<GameObject>(entity, registry, entity);
			auto& parentPos = registry->get<GameObject>(parent).GetTransform()->localPosition;
			obj.GetTransform()->localPosition = DirectX::SimpleMath::Vector3((float)x - parentPos.x, -1.f, (float)z - parentPos.z);
			obj.SetParent(parent);
			obj.Deactivate();
			obj.DeactivateRendering();

			obj.SetTag(GameObject::Tag::Floor);

			auto& collider = registry->assign<Collider>(entity, ColliderType::Box, .75f);
			collider.SetPosition(DirectX::SimpleMath::Vector3((float)x - .2f, -1.f, (float)z - .2f));

			auto& renderer = registry->assign<PrimitiveRenderer>(entity);
			renderer.SetModel(context.Get<PrimitiveModelList>().GetModel(PrimitiveModelList::ID::Cube));
			renderer.SetModelOption(DirectX::Colors::White, false, context.Get<TextureManager>().GetTexture(TextureID::Floor));

			auto& chunk = registry->get<Chunk>(parent);
			chunk.RegisterChildBlocks(entity);

			m_mapEntitys[z].push_back(entity);
		}
	}
}

void MapGenerator::InitializeItems(GameContext & context, float scale)
{
	for (int z = 0; z < kMapSize; z++)
	{
		m_mapItems.push_back(std::vector<Entity>());
		for (int x = 0; x < kMapSize; x++)
		{
			auto entity = registry->create();
			auto parent = m_chunks[z / scale][x / scale];

			auto& obj = registry->assign<GameObject>(entity, registry, entity);
			auto& parentPos = registry->get<GameObject>(parent).GetPosition();
			obj.SetPosition(DirectX::SimpleMath::Vector3((float)x - parentPos.x, 0.f, (float)z - parentPos.z));
			obj.SetScale(DirectX::SimpleMath::Vector3(.25f, .25f, .25f));
			obj.SetParent(parent);
			obj.Deactivate();
			obj.DeactivateRendering();

			obj.SetTag(GameObject::Tag::Item);

			auto& collider = registry->assign<Collider>(entity, ColliderType::Box, .5f);
			collider.SetPosition(DirectX::SimpleMath::Vector3((float)x - .2f, 0.f, (float)z - .2f));

			auto& renderer = registry->assign<PrimitiveRenderer>(entity);
			renderer.SetModel(context.Get<PrimitiveModelList>().GetModel(PrimitiveModelList::ID::Octahedron));
			renderer.SetModelOption(DirectX::Colors::YellowGreen, false);

			auto& chunk = registry->get<Chunk>(parent);
			chunk.RegisterChildItems(entity);

			auto& item = registry->assign<Item>(entity);
			item.SetEntity(entity);
			item.SetRegistry(registry);

			m_mapItems[z].push_back(entity);
		}
	}
}

void MapGenerator::CreateMapData()
{
	Random random;

	int roomCount = random.Range(kRoomCountMin, kRoomCountMax);

	std::vector<int> meetPointsX;
	std::vector<int> meetPointsY;
	for (int i = 0; i < kMeetPointCount; i++)
	{
		meetPointsX.push_back(random.Range(kMapSize / 4, kMapSize * 3 / 4));
		meetPointsY.push_back(random.Range(kMapSize / 4, kMapSize * 3 / 4));
		m_mapData[meetPointsY[i]][meetPointsX[i]] = (int)MapState::Floor;
	}

	for (int i = 0; i < roomCount; i++)
	{
		int roomWidth = random.Range(kRoomMinWidth, kRoomMaxWidth);
		int roomHeight = random.Range(kRoomMinHeight, kRoomMaxHeight);
		int roomPointX = random.Range(2, kMapSize - kRoomMaxWidth - 2);
		int roomPointY = random.Range(2, kMapSize - kRoomMaxWidth - 2);

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

	if (m_activeItems.size() > 0)
	{
		for (auto& entity : m_activeItems)
		{
			auto& obj = registry->get<GameObject>(entity);
			obj.Deactivate();
			obj.DeactivateRendering();
		}
		m_activeItems.clear();
	}
}

void MapGenerator::MapDataFillNone()
{
	for (int z = 0; z < kMapSize; z++)
	{
		m_mapData.push_back(std::vector<int>());
		for (int x = 0; x < kMapSize; x++)
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
				{
					auto entity = m_mapEntitys[z][x];
					registry->get<GameObject>(entity).Activate();
					registry->get<GameObject>(entity).ActivateRendering();
					m_activeMapEntitys.push_back(entity);
				}

				if(m_mapItems.size() > 0)
				{
					//if (z % 2 == 0 && x % 2 == 0)
					{
						auto entity = m_mapItems[z][x];
						registry->get<GameObject>(entity).Activate();
						registry->get<GameObject>(entity).ActivateRendering();
						m_activeItems.push_back(entity);
					}
				}
			}
		}
	}
}
