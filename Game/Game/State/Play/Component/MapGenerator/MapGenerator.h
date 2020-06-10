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

	// <���������}�b�v�f�[�^>
	std::vector<std::vector<int>>			m_mapData;
	// <���[���h�ɑ��݂���}�b�v�G���e�B�e�B>
	std::vector<std::vector<Entity>>		m_mapEntitys;
	// <�A�N�e�B�u�ȃ}�b�v�G���e�B�e�B>
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

	// <������>
	void Initialize(GameContext& context, entt::DefaultRegistry* _pRegistry);

	// <�}�b�v����>
	void Generate();

private:
	// <�}�b�v�f�[�^�𐶐�>
	void CreateSpaceData();
	// <�����𐶐�>
	bool CreateRoomData(int roomWidth, int roomHeight, int roomPointX, int roomPointY);
	// <�ʘH�𐶐�>
	void CreateRoadData(int roadStartPointX, int roadStartPointY, int meetPointX, int meetPointY);
	// <�}�b�v���N���A>
	void Clear();
	// <�ǂŖ��߂�>
	void Fill();
	// <�������ꂽ�f�[�^�����ɃG���e�B�e�B���A�N�e�B�u�ɂ���>
	void Activate();
};

#endif